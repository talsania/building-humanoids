#!/usr/bin/env python3
"""
ROS2 Control Multi-File Configuration Validator

This script validates the consistency across multiple ros2_control configuration files
for humanoid robots with Dynamixel servos, including MoveIt configuration files.

Usage: python3 validate_ros2_control_multi.py <config_directory>
"""

import sys
import os
import xml.etree.ElementTree as ET
import yaml
import re
from typing import Dict, List, Set, Tuple, Optional, Any
from collections import defaultdict
from pathlib import Path

class ROS2ControlMultiValidator:
    def __init__(self, config_dir: str):
        self.config_dir = Path(config_dir)
        self.errors = []
        self.warnings = []
        self.config_data = {}
        
        # Expected joint names for humanoid robot
        self.expected_joints = {
            'j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17',  # Right arm
            'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27',  # Left arm
            'j31', 'j32',  # Head
            'f18', 'f19', 'f28', 'f29'  # Grippers
        }
        
    def validate(self) -> bool:
        """Main validation function. Returns True if all checks pass."""
        try:
            # Load all configuration files
            self._load_config_files()
            
            # Run validation checks
            self._validate_joint_consistency()
            self._validate_joint_limits_consistency()
            self._validate_controller_consistency()
            self._validate_initial_positions()
            self._validate_kinematics_groups()
            self._validate_ros2_control_config()
            
            # Print results
            self._print_results()
            
            return len(self.errors) == 0
            
        except Exception as e:
            self.errors.append(f"Failed to validate configuration: {str(e)}")
            return False
    
    def _load_config_files(self):
        """Load all relevant configuration files."""
        config_files = {
            'initial_positions': 'initial_positions.yaml',
            'joint_limits': 'joint_limits.yaml',
            'kinematics': 'kinematics.yaml',
            'moveit_controllers': 'moveit_controllers.yaml',
            'ros2_controllers': 'ros2_controllers.yaml',
            'ros2_control_xacro': 'v2.ros2_control.xacro'
        }
        
        for config_type, filename in config_files.items():
            file_path = self.config_dir / filename
            if file_path.exists():
                try:
                    if filename.endswith('.yaml'):
                        with open(file_path, 'r') as f:
                            self.config_data[config_type] = yaml.safe_load(f)
                    elif filename.endswith('.xacro'):
                        self.config_data[config_type] = self._parse_xacro_file(file_path)
                    print(f"✓ Loaded {filename}")
                except Exception as e:
                    self.errors.append(f"Failed to load {filename}: {str(e)}")
            else:
                self.warnings.append(f"Configuration file not found: {filename}")
    
    def _parse_xacro_file(self, file_path: Path) -> Dict:
        """Parse xacro file and extract ros2_control configuration."""
        try:
            tree = ET.parse(file_path)
            root = tree.getroot()
            
            # Find ros2_control block
            ros2_control = self._find_ros2_control_block(root)
            if not ros2_control:
                return {}
            
            # Extract configuration data
            return self._extract_xacro_config_data(ros2_control)
            
        except Exception as e:
            self.errors.append(f"Failed to parse {file_path}: {str(e)}")
            return {}
    
    def _find_ros2_control_block(self, root) -> Optional[ET.Element]:
        """Find the ros2_control block in the XML tree."""
        for elem in root.iter():
            if elem.tag.endswith('ros2_control') or elem.tag == 'ros2_control':
                return elem
        return None
    
    def _extract_xacro_config_data(self, ros2_control: ET.Element) -> Dict:
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
    
    def _validate_joint_consistency(self):
        """Validate joint consistency across all configuration files."""
        joint_sets = {}
        
        # Collect joints from each configuration
        if 'initial_positions' in self.config_data:
            initial_pos = self.config_data['initial_positions']
            if 'initial_positions' in initial_pos:
                joint_sets['initial_positions'] = set(initial_pos['initial_positions'].keys())
        
        if 'joint_limits' in self.config_data:
            joint_limits = self.config_data['joint_limits']
            if 'joint_limits' in joint_limits:
                joint_sets['joint_limits'] = set(joint_limits['joint_limits'].keys())
        
        if 'ros2_control_xacro' in self.config_data:
            ros2_control = self.config_data['ros2_control_xacro']
            if 'joints' in ros2_control:
                joint_sets['ros2_control'] = set(ros2_control['joints'])
        
        # Collect joints from controllers
        if 'ros2_controllers' in self.config_data:
            controller_joints = set()
            controllers = self.config_data['ros2_controllers']
            
            for controller_name, controller_config in controllers.items():
                if isinstance(controller_config, dict) and 'ros__parameters' in controller_config:
                    params = controller_config['ros__parameters']
                    if 'joints' in params:
                        controller_joints.update(params['joints'])
            
            if controller_joints:
                joint_sets['ros2_controllers'] = controller_joints
        
        if 'moveit_controllers' in self.config_data:
            moveit_joints = set()
            moveit_config = self.config_data['moveit_controllers']
            
            if 'move_group' in moveit_config and 'ros__parameters' in moveit_config['move_group']:
                simple_controller = moveit_config['move_group']['ros__parameters'].get('moveit_simple_controller_manager', {})
                for controller_name, controller_config in simple_controller.items():
                    if isinstance(controller_config, dict) and 'joints' in controller_config:
                        moveit_joints.update(controller_config['joints'])
            
            if moveit_joints:
                joint_sets['moveit_controllers'] = moveit_joints
        
        # Check consistency
        if len(joint_sets) < 2:
            self.warnings.append("Not enough configuration files to check joint consistency")
            return
        
        # Find the reference set (largest set)
        reference_name = max(joint_sets.keys(), key=lambda k: len(joint_sets[k]))
        reference_joints = joint_sets[reference_name]
        
        # Check against expected joints
        missing_expected = self.expected_joints - reference_joints
        extra_joints = reference_joints - self.expected_joints
        
        if missing_expected:
            self.warnings.append(f"Missing expected joints in {reference_name}: {sorted(missing_expected)}")
        
        if extra_joints:
            self.warnings.append(f"Unexpected joints in {reference_name}: {sorted(extra_joints)}")
        
        # Check consistency between files
        for config_name, joints in joint_sets.items():
            if config_name == reference_name:
                continue
            
            missing = reference_joints - joints
            extra = joints - reference_joints
            
            if missing:
                self.errors.append(f"Joints missing in {config_name} compared to {reference_name}: {sorted(missing)}")
            
            if extra:
                self.errors.append(f"Extra joints in {config_name} compared to {reference_name}: {sorted(extra)}")
    
    def _validate_joint_limits_consistency(self):
        """Validate joint limits are consistent and reasonable."""
        if 'joint_limits' not in self.config_data:
            return
        
        joint_limits = self.config_data['joint_limits'].get('joint_limits', {})
        
        for joint_name, limits in joint_limits.items():
            if not isinstance(limits, dict):
                continue
            
            # Check required fields
            if not limits.get('has_position_limits', False):
                self.warnings.append(f"Joint {joint_name} has no position limits")
                continue
            
            min_pos = limits.get('min_position')
            max_pos = limits.get('max_position')
            
            if min_pos is None or max_pos is None:
                self.errors.append(f"Joint {joint_name} missing min/max position limits")
                continue
            
            # Check logical consistency
            if min_pos >= max_pos:
                self.errors.append(f"Joint {joint_name} min_position ({min_pos}) >= max_position ({max_pos})")
            
            # Check reasonable ranges
            range_size = max_pos - min_pos
            if range_size > 2 * 3.14159:  # More than 2*pi radians
                self.warnings.append(f"Joint {joint_name} has very large range: {range_size:.3f} radians")
            
            # Check for symmetric limits (common for many joints)
            if abs(abs(min_pos) - abs(max_pos)) < 0.01 and joint_name not in ['j12', 'j22']:  # j12/j22 are asymmetric
                if abs(min_pos + max_pos) > 0.01:
                    self.warnings.append(f"Joint {joint_name} has asymmetric limits: [{min_pos}, {max_pos}]")
    
    def _validate_controller_consistency(self):
        """Validate controller configuration consistency."""
        if 'ros2_controllers' not in self.config_data or 'moveit_controllers' not in self.config_data:
            return
        
        # Get ROS2 controllers
        ros2_controllers = self.config_data['ros2_controllers']
        ros2_controller_names = set()
        
        for controller_name, config in ros2_controllers.items():
            if controller_name == 'controller_manager':
                continue
            if isinstance(config, dict) and 'ros__parameters' in config:
                ros2_controller_names.add(controller_name)
        
        # Get MoveIt controllers
        moveit_controllers = self.config_data['moveit_controllers']
        moveit_controller_names = set()
        
        if 'move_group' in moveit_controllers and 'ros__parameters' in moveit_controllers['move_group']:
            simple_controller = moveit_controllers['move_group']['ros__parameters'].get('moveit_simple_controller_manager', {})
            controller_names = simple_controller.get('controller_names', [])
            moveit_controller_names.update(controller_names)
        
        # Check consistency
        missing_in_ros2 = moveit_controller_names - ros2_controller_names
        missing_in_moveit = ros2_controller_names - moveit_controller_names
        
        if missing_in_ros2:
            self.errors.append(f"Controllers defined in MoveIt but not in ROS2 controllers: {sorted(missing_in_ros2)}")
        
        if missing_in_moveit:
            self.errors.append(f"Controllers defined in ROS2 but not in MoveIt controllers: {sorted(missing_in_moveit)}")
    
    def _validate_initial_positions(self):
        """Validate initial positions are within joint limits."""
        if 'initial_positions' not in self.config_data or 'joint_limits' not in self.config_data:
            return
        
        initial_pos = self.config_data['initial_positions'].get('initial_positions', {})
        joint_limits = self.config_data['joint_limits'].get('joint_limits', {})
        
        for joint_name, initial_value in initial_pos.items():
            if joint_name not in joint_limits:
                self.warnings.append(f"Initial position defined for joint {joint_name} but no limits found")
                continue
            
            limits = joint_limits[joint_name]
            if not limits.get('has_position_limits', False):
                continue
            
            min_pos = limits.get('min_position')
            max_pos = limits.get('max_position')
            
            if min_pos is not None and max_pos is not None:
                if not (min_pos <= initial_value <= max_pos):
                    self.errors.append(
                        f"Initial position for joint {joint_name} ({initial_value}) is outside limits [{min_pos}, {max_pos}]"
                    )
    
    def _validate_kinematics_groups(self):
        """Validate kinematics group configuration."""
        if 'kinematics' not in self.config_data:
            return
        
        kinematics = self.config_data['kinematics']
        expected_groups = ['dual_arm', 'left_arm', 'right_arm', 'head']
        
        for group in expected_groups:
            if group not in kinematics:
                self.warnings.append(f"Kinematics group '{group}' not found")
                continue
            
            group_config = kinematics[group]
            required_params = ['kinematics_solver', 'kinematics_solver_search_resolution', 'kinematics_solver_timeout']
            
            for param in required_params:
                if param not in group_config:
                    self.errors.append(f"Kinematics group '{group}' missing parameter: {param}")
            
            # Check solver type
            solver = group_config.get('kinematics_solver', '')
            if 'kdl_kinematics_plugin' not in solver and 'lma_kinematics_plugin' not in solver:
                self.warnings.append(f"Kinematics group '{group}' uses unusual solver: {solver}")
    
    def _validate_ros2_control_config(self):
        """Validate ros2_control xacro configuration."""
        if 'ros2_control_xacro' not in self.config_data:
            return
        
        config = self.config_data['ros2_control_xacro']
        
        # Check basic parameters
        params = config.get('parameters', {})
        required_params = ['number_of_joints', 'number_of_transmissions']
        
        for param in required_params:
            if param not in params:
                self.errors.append(f"Missing required parameter in ros2_control: {param}")
        
        # Check GPIO blocks (Dynamixel servos)
        gpio_blocks = config.get('gpio_blocks', [])
        if not gpio_blocks:
            self.errors.append("No GPIO blocks (Dynamixel servos) found in ros2_control")
            return
        
        # Check for duplicate IDs
        ids = []
        for gpio in gpio_blocks:
            try:
                servo_id = int(gpio.get('ID', 0))
                if servo_id in ids:
                    self.errors.append(f"Duplicate Dynamixel ID {servo_id} in ros2_control")
                else:
                    ids.append(servo_id)
            except ValueError:
                self.errors.append(f"Invalid Dynamixel ID in GPIO block: {gpio.get('ID')}")
        
        # Check ID ranges
        for servo_id in ids:
            if not (1 <= servo_id <= 253):
                self.warnings.append(f"Dynamixel ID {servo_id} outside standard range (1-253)")
    
    def _print_results(self):
        """Print validation results."""
        print(f"\n=== ROS2 Control Multi-File Configuration Validation Results ===")
        print(f"Directory: {self.config_dir}")
        print(f"Files checked: {len(self.config_data)}")
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
            print(f"\n✅ All configurations are consistent!")
        elif not self.errors:
            print(f"\n✅ Configurations are consistent (with warnings)")
        else:
            print(f"\n❌ Configuration inconsistencies found that need to be fixed!")
        
        # Summary of loaded files
        print(f"\n📄 Configuration Files Loaded:")
        for config_type, data in self.config_data.items():
            if data:
                print(f"  ✓ {config_type}")
            else:
                print(f"  ✗ {config_type} (empty or failed to load)")


def main():
    if len(sys.argv) != 2:
        print("Usage: python3 validate_ros2_control_multi.py <config_directory>")
        print("Example: python3 validate_ros2_control_multi.py src/kris_moveit_config/config/")
        sys.exit(1)
    
    config_dir = sys.argv[1]
    
    if not os.path.isdir(config_dir):
        print(f"Error: Directory '{config_dir}' not found")
        sys.exit(1)
    
    try:
        validator = ROS2ControlMultiValidator(config_dir)
        is_valid = validator.validate()
        
        sys.exit(0 if is_valid else 1)
        
    except Exception as e:
        print(f"Error: {str(e)}")
        sys.exit(1)


if __name__ == "__main__":
    main()