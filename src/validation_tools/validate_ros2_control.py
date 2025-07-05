#!/usr/bin/env python3
"""
ROS2 Control Configuration Validator

This script validates the consistency of ros2_control configuration files
for humanoid robots with Dynamixel servos.

Usage: python3 validate_ros2_control.py <config_file.xacro>
"""

import sys
import xml.etree.ElementTree as ET
import re
from typing import Dict, List, Set, Tuple
from collections import defaultdict

class ROS2ControlValidator:
    def __init__(self, config_file: str):
        self.config_file = config_file
        self.errors = []
        self.warnings = []
        
    def validate(self) -> bool:
        """Main validation function. Returns True if all checks pass."""
        try:
            # Parse the XML file
            tree = ET.parse(self.config_file)
            root = tree.getroot()
            
            # Find ros2_control block
            ros2_control = self._find_ros2_control_block(root)
            if not ros2_control:
                self.errors.append("No ros2_control block found in configuration")
                return False
            
            # Extract configuration data
            config_data = self._extract_config_data(ros2_control)
            
            # Run all validation checks
            self._validate_basic_parameters(config_data)
            self._validate_joints(config_data)
            self._validate_dynamixel_servos(config_data)
            self._validate_transmission_matrices(config_data)
            self._validate_joint_servo_mapping(config_data)
            self._validate_id_uniqueness(config_data)
            self._validate_servo_parameters(config_data)
            
            # Print results
            self._print_results()
            
            return len(self.errors) == 0
            
        except Exception as e:
            self.errors.append(f"Failed to parse configuration file: {str(e)}")
            return False
    
    def _find_ros2_control_block(self, root) -> ET.Element:
        """Find the ros2_control block in the XML tree."""
        # Handle xacro namespace
        for elem in root.iter():
            if elem.tag.endswith('ros2_control') or elem.tag == 'ros2_control':
                return elem
        return None
    
    def _extract_config_data(self, ros2_control: ET.Element) -> Dict:
        """Extract all relevant configuration data from ros2_control block."""
        config = {
            'joints': [],
            'gpio_blocks': [],
            'parameters': {}
        }
        
        # Extract hardware parameters
        hardware = ros2_control.find('.//hardware')
        if hardware:
            for param in hardware.findall('param'):
                name = param.get('name')
                value = param.get('value', param.text)
                config['parameters'][name] = value
        
        # Extract joint definitions
        for joint in ros2_control.findall('.//joint'):
            joint_name = joint.get('name')
            if joint_name:
                config['joints'].append(joint_name)
        
        # Extract GPIO blocks (Dynamixel servos)
        for gpio in ros2_control.findall('.//gpio'):
            gpio_name = gpio.get('name')
            gpio_config = {'name': gpio_name}
            
            for param in gpio.findall('param'):
                param_name = param.get('name')
                param_value = param.get('value', param.text)
                gpio_config[param_name] = param_value
            
            config['gpio_blocks'].append(gpio_config)
        
        return config
    
    def _validate_basic_parameters(self, config: Dict):
        """Validate basic hardware parameters."""
        params = config['parameters']
        
        # Check required parameters
        required_params = [
            'number_of_joints',
            'number_of_transmissions',
            'transmission_to_joint_matrix',
            'joint_to_transmission_matrix'
        ]
        
        for param in required_params:
            if param not in params:
                self.errors.append(f"Missing required parameter: {param}")
        
        # Validate numeric parameters
        try:
            num_joints = int(params.get('number_of_joints', 0))
            num_transmissions = int(params.get('number_of_transmissions', 0))
            
            if num_joints != len(config['joints']):
                self.errors.append(
                    f"number_of_joints ({num_joints}) doesn't match actual joint count ({len(config['joints'])})"
                )
            
            if num_transmissions != len(config['gpio_blocks']):
                self.errors.append(
                    f"number_of_transmissions ({num_transmissions}) doesn't match GPIO block count ({len(config['gpio_blocks'])})"
                )
            
            if num_joints != num_transmissions:
                self.errors.append(
                    f"number_of_joints ({num_joints}) should equal number_of_transmissions ({num_transmissions})"
                )
                
        except ValueError as e:
            self.errors.append(f"Invalid numeric parameter: {str(e)}")
    
    def _validate_joints(self, config: Dict):
        """Validate joint definitions."""
        joints = config['joints']
        
        if not joints:
            self.errors.append("No joints defined")
            return
        
        # Check for duplicate joint names
        joint_counts = defaultdict(int)
        for joint in joints:
            joint_counts[joint] += 1
        
        duplicates = [joint for joint, count in joint_counts.items() if count > 1]
        if duplicates:
            self.errors.append(f"Duplicate joint names found: {duplicates}")
        
        # Validate joint naming convention
        expected_joints = [
            'j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17',  # Right arm
            'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27',  # Left arm
            'j31', 'j32',  # Head
            'f18', 'f28'    # Grippers
        ]
        
        missing_joints = set(expected_joints) - set(joints)
        extra_joints = set(joints) - set(expected_joints)
        
        if missing_joints:
            self.warnings.append(f"Missing expected joints: {sorted(missing_joints)}")
        
        if extra_joints:
            self.warnings.append(f"Unexpected joints found: {sorted(extra_joints)}")
    
    def _validate_dynamixel_servos(self, config: Dict):
        """Validate Dynamixel servo configurations."""
        gpio_blocks = config['gpio_blocks']
        
        if not gpio_blocks:
            self.errors.append("No GPIO blocks (Dynamixel servos) defined")
            return
        
        # Check for required parameters in each GPIO block
        required_gpio_params = ['type', 'ID', 'Operating Mode']
        
        for gpio in gpio_blocks:
            gpio_name = gpio.get('name', 'unknown')
            
            for param in required_gpio_params:
                if param not in gpio:
                    self.errors.append(f"GPIO block '{gpio_name}' missing required parameter: {param}")
            
            # Validate GPIO type
            if gpio.get('type') != 'dxl':
                self.errors.append(f"GPIO block '{gpio_name}' has invalid type: {gpio.get('type')}")
            
            # Validate Operating Mode
            try:
                op_mode = int(gpio.get('Operating Mode', 0))
                if op_mode not in [3, 4]:  # Common position control modes
                    self.warnings.append(f"GPIO block '{gpio_name}' has unusual Operating Mode: {op_mode}")
            except ValueError:
                self.errors.append(f"GPIO block '{gpio_name}' has invalid Operating Mode value")
    
    def _validate_transmission_matrices(self, config: Dict):
        """Validate transmission matrices dimensions and format."""
        params = config['parameters']
        num_joints = int(params.get('number_of_joints', 0))
        num_transmissions = int(params.get('number_of_transmissions', 0))
        
        # Check transmission_to_joint_matrix
        t2j_matrix = params.get('transmission_to_joint_matrix', '')
        if t2j_matrix:
            t2j_values = self._parse_matrix_values(t2j_matrix)
            expected_size = num_joints * num_transmissions
            
            if len(t2j_values) != expected_size:
                self.errors.append(
                    f"transmission_to_joint_matrix has {len(t2j_values)} values, "
                    f"expected {expected_size} ({num_joints}x{num_transmissions})"
                )
            
            # Check matrix structure (should be mostly zeros with specific non-zero values)
            non_zero_count = sum(1 for v in t2j_values if abs(v) > 1e-6)
            if non_zero_count != num_joints:
                self.warnings.append(
                    f"transmission_to_joint_matrix has {non_zero_count} non-zero values, "
                    f"expected {num_joints} (one per joint)"
                )
        
        # Check joint_to_transmission_matrix
        j2t_matrix = params.get('joint_to_transmission_matrix', '')
        if j2t_matrix:
            j2t_values = self._parse_matrix_values(j2t_matrix)
            expected_size = num_joints * num_transmissions
            
            if len(j2t_values) != expected_size:
                self.errors.append(
                    f"joint_to_transmission_matrix has {len(j2t_values)} values, "
                    f"expected {expected_size} ({num_joints}x{num_transmissions})"
                )
        
        # Check if matrices are inverse of each other (approximately)
        if t2j_matrix and j2t_matrix:
            self._validate_matrix_inverse_relationship(t2j_values, j2t_values, num_joints)
    
    def _parse_matrix_values(self, matrix_string: str) -> List[float]:
        """Parse comma-separated matrix values."""
        values = []
        for value in matrix_string.split(','):
            try:
                values.append(float(value.strip()))
            except ValueError:
                self.errors.append(f"Invalid matrix value: {value.strip()}")
        return values
    
    def _validate_matrix_inverse_relationship(self, t2j_values: List[float], j2t_values: List[float], size: int):
        """Check if the two matrices are approximately inverse of each other."""
        # This is a simplified check - in practice, you might want to use numpy for proper matrix operations
        # For now, we'll just check that corresponding non-zero values are reciprocals
        
        tolerance = 1e-6
        for i in range(len(t2j_values)):
            if abs(t2j_values[i]) > tolerance and abs(j2t_values[i]) > tolerance:
                product = t2j_values[i] * j2t_values[i]
                if abs(product - 1.0) > tolerance and abs(product + 1.0) > tolerance:
                    self.warnings.append(
                        f"Matrix values at position {i} may not be proper inverses: "
                        f"{t2j_values[i]} * {j2t_values[i]} = {product}"
                    )
    
    def _validate_joint_servo_mapping(self, config: Dict):
        """Validate that each joint has a corresponding servo and vice versa."""
        joints = set(config['joints'])
        gpio_blocks = config['gpio_blocks']
        
        # This is a simplified check - in practice, you might need more sophisticated mapping
        if len(joints) != len(gpio_blocks):
            self.errors.append(
                f"Number of joints ({len(joints)}) doesn't match number of GPIO blocks ({len(gpio_blocks)})"
            )
    
    def _validate_id_uniqueness(self, config: Dict):
        """Validate that all Dynamixel IDs are unique."""
        ids = []
        id_to_gpio = {}
        
        for gpio in config['gpio_blocks']:
            gpio_name = gpio.get('name', 'unknown')
            try:
                servo_id = int(gpio.get('ID', 0))
                if servo_id in ids:
                    self.errors.append(
                        f"Duplicate Dynamixel ID {servo_id} found in GPIO blocks "
                        f"'{id_to_gpio[servo_id]}' and '{gpio_name}'"
                    )
                else:
                    ids.append(servo_id)
                    id_to_gpio[servo_id] = gpio_name
            except ValueError:
                self.errors.append(f"Invalid Dynamixel ID in GPIO block '{gpio_name}': {gpio.get('ID')}")
        
        # Check ID ranges (common Dynamixel ID conventions)
        valid_id_ranges = [(1, 253)]  # Standard Dynamixel ID range
        
        for servo_id in ids:
            if not any(start <= servo_id <= end for start, end in valid_id_ranges):
                self.warnings.append(f"Dynamixel ID {servo_id} is outside common range (1-253)")
    
    def _validate_servo_parameters(self, config: Dict):
        """Validate servo-specific parameters."""
        for gpio in config['gpio_blocks']:
            gpio_name = gpio.get('name', 'unknown')
            
            # Check Current Limit (if present)
            if 'Current Limit' in gpio:
                try:
                    current_limit = int(gpio['Current Limit'])
                    if current_limit < 0 or current_limit > 2047:  # Common range for Dynamixel
                        self.warnings.append(
                            f"GPIO block '{gpio_name}' has unusual Current Limit: {current_limit}"
                        )
                except ValueError:
                    self.errors.append(f"GPIO block '{gpio_name}' has invalid Current Limit value")
            
            # Check Profile Velocity (if present)
            if 'Profile Velocity' in gpio:
                try:
                    profile_vel = int(gpio['Profile Velocity'])
                    if profile_vel < 0:
                        self.errors.append(
                            f"GPIO block '{gpio_name}' has negative Profile Velocity: {profile_vel}"
                        )
                except ValueError:
                    self.errors.append(f"GPIO block '{gpio_name}' has invalid Profile Velocity value")
            
            # Check Profile Acceleration (if present)
            if 'Profile Acceleration' in gpio:
                try:
                    profile_acc = int(gpio['Profile Acceleration'])
                    if profile_acc < 0:
                        self.errors.append(
                            f"GPIO block '{gpio_name}' has negative Profile Acceleration: {profile_acc}"
                        )
                except ValueError:
                    self.errors.append(f"GPIO block '{gpio_name}' has invalid Profile Acceleration value")
    
    def _print_results(self):
        """Print validation results."""
        print(f"\n=== ROS2 Control Configuration Validation Results ===")
        print(f"File: {self.config_file}")
        print(f"Errors: {len(self.errors)}")
        print(f"Warnings: {len(self.warnings)}")
        
        if self.errors:
            print(f"\n❌ ERRORS:")
            for i, error in enumerate(self.errors, 1):
                print(f"  {i}. {error}")
        
        if self.warnings:
            print(f"\n⚠️  WARNINGS:")
            for i, warning in enumerate(self.warnings, 1):
                print(f"  {i}. {warning}")
        
        if not self.errors and not self.warnings:
            print(f"\n✅ Configuration is valid!")
        elif not self.errors:
            print(f"\n✅ Configuration is valid (with warnings)")
        else:
            print(f"\n❌ Configuration has errors that need to be fixed!")


def main():
    if len(sys.argv) != 2:
        print("Usage: python3 validate_ros2_control.py <config_file.xacro>")
        sys.exit(1)
    
    config_file = sys.argv[1]
    
    try:
        validator = ROS2ControlValidator(config_file)
        is_valid = validator.validate()
        
        sys.exit(0 if is_valid else 1)
        
    except FileNotFoundError:
        print(f"Error: Configuration file '{config_file}' not found")
        sys.exit(1)
    except Exception as e:
        print(f"Error: {str(e)}")
        sys.exit(1)


if __name__ == "__main__":
    main()