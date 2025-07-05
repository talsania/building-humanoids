#!/usr/bin/env python3
"""
MoveIt Configuration Validator

This script validates the consistency of MoveIt configuration files
for humanoid robots with ROS2 Humble and MoveIt2.

Usage: python3 validate_moveit_config.py <config_directory>
"""

import sys
import os
import yaml
import xml.etree.ElementTree as ET
from pathlib import Path
from typing import Dict, List, Set, Any, Optional, Tuple
from collections import defaultdict
import re

class MoveItConfigValidator:
    def __init__(self, config_dir: str):
        self.config_dir = Path(config_dir)
        self.errors = []
        self.warnings = []
        self.config_data = {}
        
        # Expected configuration files
        self.expected_files = {
            'initial_positions.yaml': 'initial_positions',
            'joint_limits.yaml': 'joint_limits',
            'kinematics.yaml': 'kinematics',
            'moveit_controllers.yaml': 'moveit_controllers',
            'moveit_controllers_for_launch.yaml': 'moveit_controllers_launch',
            'ros2_controllers.yaml': 'ros2_controllers',
            'ompl_planning.yaml': 'ompl_planning',
            'pilz_cartesian_limits.yaml': 'pilz_limits',
            'planning_scene_monitor_params.yaml': 'planning_scene',
            'sensors_3d.yaml': 'sensors',
            'v2.srdf': 'srdf',
            'v2.urdf.xacro': 'urdf',
            'v2.ros2_control.xacro': 'ros2_control'
        }
        
    def validate(self) -> bool:
        """Main validation function. Returns True if all checks pass."""
        print(f"Validating MoveIt configuration in: {self.config_dir}")
        
        # Check if config directory exists
        if not self.config_dir.exists():
            self.errors.append(f"Configuration directory does not exist: {self.config_dir}")
            return False
        
        # Load all configuration files
        self._load_config_files()
        
        # Run validation checks
        self._validate_file_presence()
        self._validate_initial_positions()
        self._validate_joint_limits()
        self._validate_kinematics()
        self._validate_moveit_controllers()
        self._validate_ros2_controllers()
        self._validate_ompl_planning()
        self._validate_pilz_limits()
        self._validate_planning_scene()
        self._validate_sensors()
        self._validate_srdf()
        self._validate_urdf()
        self._validate_ros2_control()
        
        # Cross-validation between files
        self._validate_joint_consistency()
        self._validate_controller_consistency()
        self._validate_planning_group_consistency()
        
        # Print results
        self._print_results()
        
        return len(self.errors) == 0
    
    def _load_config_files(self):
        """Load all configuration files."""
        config_path = self.config_dir / 'config'
        
        for filename, key in self.expected_files.items():
            file_path = config_path / filename
            
            if not file_path.exists():
                self.warnings.append(f"Configuration file not found: {filename}")
                continue
            
            try:
                if filename.endswith('.yaml'):
                    with open(file_path, 'r') as f:
                        self.config_data[key] = yaml.safe_load(f)
                elif filename.endswith('.xacro') or filename.endswith('.srdf'):
                    tree = ET.parse(file_path)
                    self.config_data[key] = tree.getroot()
                else:
                    # For other file types, store the path
                    self.config_data[key] = file_path
                    
            except Exception as e:
                self.errors.append(f"Failed to load {filename}: {str(e)}")
    
    def _validate_file_presence(self):
        """Validate that all expected files are present."""
        config_path = self.config_dir / 'config'
        
        for filename in self.expected_files.keys():
            file_path = config_path / filename
            if not file_path.exists():
                if filename in ['v2.srdf', 'v2.urdf.xacro', 'v2.ros2_control.xacro']:
                    self.errors.append(f"Critical configuration file missing: {filename}")
                else:
                    self.warnings.append(f"Optional configuration file missing: {filename}")
    
    def _validate_initial_positions(self):
        """Validate initial positions configuration."""
        if 'initial_positions' not in self.config_data:
            return
        
        config = self.config_data['initial_positions']
        
        # Check for required structure
        if not isinstance(config, dict):
            self.errors.append("initial_positions.yaml: Invalid structure, expected dictionary")
            return
        
        # Common expected joints for humanoid
        expected_joints = [
            'j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17',  # Right arm
            'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27',  # Left arm
            'j31', 'j32',  # Head
            'f18', 'f28'    # Grippers
        ]
        
        # Extract joints from config
        joints_in_config = set()
        for key, value in config.items():
            if isinstance(value, dict) and 'position' in value:
                joints_in_config.add(key)
            elif isinstance(value, (int, float)):
                joints_in_config.add(key)
        
        # Check for missing joints
        missing_joints = set(expected_joints) - joints_in_config
        if missing_joints:
            self.warnings.append(f"initial_positions.yaml: Missing joints: {sorted(missing_joints)}")
        
        # Validate joint position values
        for joint, value in config.items():
            if isinstance(value, dict) and 'position' in value:
                pos = value['position']
            elif isinstance(value, (int, float)):
                pos = value
            else:
                self.errors.append(f"initial_positions.yaml: Invalid value for joint '{joint}': {value}")
                continue
            
            # Check position range (typical servo range)
            if not isinstance(pos, (int, float)):
                self.errors.append(f"initial_positions.yaml: Non-numeric position for joint '{joint}': {pos}")
            elif abs(pos) > 6.28:  # ~2π radians
                self.warnings.append(f"initial_positions.yaml: Large position value for joint '{joint}': {pos}")
    
    def _validate_joint_limits(self):
        """Validate joint limits configuration."""
        if 'joint_limits' not in self.config_data:
            return
        
        config = self.config_data['joint_limits']
        
        if 'joint_limits' not in config:
            self.errors.append("joint_limits.yaml: Missing 'joint_limits' section")
            return
        
        joint_limits = config['joint_limits']
        
        for joint_name, limits in joint_limits.items():
            if not isinstance(limits, dict):
                self.errors.append(f"joint_limits.yaml: Invalid limits for joint '{joint_name}'")
                continue
            
            # Check required limit parameters
            required_params = ['has_position_limits', 'min_position', 'max_position']
            for param in required_params:
                if param not in limits:
                    self.errors.append(f"joint_limits.yaml: Missing '{param}' for joint '{joint_name}'")
            
            # Validate position limits
            if 'min_position' in limits and 'max_position' in limits:
                try:
                    min_pos = float(limits['min_position'])
                    max_pos = float(limits['max_position'])
                    
                    if min_pos >= max_pos:
                        self.errors.append(f"joint_limits.yaml: Invalid range for joint '{joint_name}': min >= max")
                    
                    # Check for reasonable ranges
                    if max_pos - min_pos > 12.56:  # > 4π radians
                        self.warnings.append(f"joint_limits.yaml: Very large range for joint '{joint_name}': {max_pos - min_pos}")
                        
                except ValueError:
                    self.errors.append(f"joint_limits.yaml: Non-numeric position limits for joint '{joint_name}'")
            
            # Validate velocity limits
            if 'has_velocity_limits' in limits and limits['has_velocity_limits']:
                if 'max_velocity' not in limits:
                    self.errors.append(f"joint_limits.yaml: Missing 'max_velocity' for joint '{joint_name}'")
                else:
                    try:
                        max_vel = float(limits['max_velocity'])
                        if max_vel <= 0:
                            self.errors.append(f"joint_limits.yaml: Invalid max_velocity for joint '{joint_name}': {max_vel}")
                    except ValueError:
                        self.errors.append(f"joint_limits.yaml: Non-numeric max_velocity for joint '{joint_name}'")
    
    def _validate_kinematics(self):
        """Validate kinematics configuration."""
        if 'kinematics' not in self.config_data:
            return
        
        config = self.config_data['kinematics']
        
        # Expected planning groups for humanoid
        expected_groups = ['right_arm', 'left_arm', 'head', 'right_gripper', 'left_gripper']
        
        for group in expected_groups:
            if group not in config:
                self.warnings.append(f"kinematics.yaml: Missing planning group '{group}'")
                continue
            
            group_config = config[group]
            
            # Check required parameters
            required_params = ['kinematics_solver', 'kinematics_solver_search_resolution']
            for param in required_params:
                if param not in group_config:
                    self.errors.append(f"kinematics.yaml: Missing '{param}' for group '{group}'")
            
            # Validate solver type
            if 'kinematics_solver' in group_config:
                solver = group_config['kinematics_solver']
                valid_solvers = ['kdl_kinematics_plugin/KDLKinematicsPlugin', 'trac_ik_kinematics_plugin/TRAC_IKKinematicsPlugin']
                if solver not in valid_solvers:
                    self.warnings.append(f"kinematics.yaml: Uncommon solver for group '{group}': {solver}")
            
            # Validate search resolution
            if 'kinematics_solver_search_resolution' in group_config:
                try:
                    resolution = float(group_config['kinematics_solver_search_resolution'])
                    if resolution <= 0 or resolution > 1:
                        self.warnings.append(f"kinematics.yaml: Unusual search resolution for group '{group}': {resolution}")
                except ValueError:
                    self.errors.append(f"kinematics.yaml: Non-numeric search resolution for group '{group}'")
    
    def _validate_moveit_controllers(self):
        """Validate MoveIt controllers configuration."""
        if 'moveit_controllers' not in self.config_data:
            return
        
        config = self.config_data['moveit_controllers']
        
        if 'moveit_simple_controller_manager' not in config:
            self.errors.append("moveit_controllers.yaml: Missing 'moveit_simple_controller_manager' section")
            return
        
        manager_config = config['moveit_simple_controller_manager']
        
        if 'controller_names' not in manager_config:
            self.errors.append("moveit_controllers.yaml: Missing 'controller_names' list")
            return
        
        controller_names = manager_config['controller_names']
        
        for controller_name in controller_names:
            controller_key = f"{controller_name}_controller"
            
            if controller_key not in manager_config:
                self.errors.append(f"moveit_controllers.yaml: Missing configuration for controller '{controller_name}'")
                continue
            
            controller_config = manager_config[controller_key]
            
            # Check required parameters
            required_params = ['action_ns', 'type', 'joints']
            for param in required_params:
                if param not in controller_config:
                    self.errors.append(f"moveit_controllers.yaml: Missing '{param}' for controller '{controller_name}'")
            
            # Validate controller type
            if 'type' in controller_config:
                controller_type = controller_config['type']
                valid_types = ['FollowJointTrajectory', 'GripperCommand']
                if controller_type not in valid_types:
                    self.warnings.append(f"moveit_controllers.yaml: Uncommon controller type '{controller_type}' for '{controller_name}'")
            
            # Validate joints list
            if 'joints' in controller_config:
                joints = controller_config['joints']
                if not isinstance(joints, list):
                    self.errors.append(f"moveit_controllers.yaml: 'joints' should be a list for controller '{controller_name}'")
                elif len(joints) == 0:
                    self.errors.append(f"moveit_controllers.yaml: Empty joints list for controller '{controller_name}'")
    
    def _validate_ros2_controllers(self):
        """Validate ROS2 controllers configuration."""
        if 'ros2_controllers' not in self.config_data:
            return
        
        config = self.config_data['ros2_controllers']
        
        if 'controller_manager' not in config:
            self.errors.append("ros2_controllers.yaml: Missing 'controller_manager' section")
            return
        
        controller_manager = config['controller_manager']
        
        if 'ros__parameters' not in controller_manager:
            self.errors.append("ros2_controllers.yaml: Missing 'ros__parameters' section")
            return
        
        params = controller_manager['ros__parameters']
        
        # Check update rate
        if 'update_rate' not in params:
            self.warnings.append("ros2_controllers.yaml: Missing 'update_rate' parameter")
        else:
            try:
                update_rate = int(params['update_rate'])
                if update_rate <= 0:
                    self.errors.append(f"ros2_controllers.yaml: Invalid update_rate: {update_rate}")
                elif update_rate > 1000:
                    self.warnings.append(f"ros2_controllers.yaml: Very high update_rate: {update_rate}")
            except ValueError:
                self.errors.append("ros2_controllers.yaml: Non-numeric update_rate")
        
        # Validate individual controller configurations
        for key, value in config.items():
            if key != 'controller_manager' and isinstance(value, dict):
                self._validate_individual_ros2_controller(key, value)
    
    def _validate_individual_ros2_controller(self, controller_name: str, controller_config: Dict):
        """Validate individual ROS2 controller configuration."""
        if 'ros__parameters' not in controller_config:
            self.errors.append(f"ros2_controllers.yaml: Missing 'ros__parameters' for controller '{controller_name}'")
            return
        
        params = controller_config['ros__parameters']
        
        # Check controller type
        if 'type' not in params:
            self.errors.append(f"ros2_controllers.yaml: Missing 'type' for controller '{controller_name}'")
        else:
            controller_type = params['type']
            valid_types = [
                'joint_trajectory_controller/JointTrajectoryController',
                'position_controllers/GripperActionController',
                'joint_state_broadcaster/JointStateBroadcaster'
            ]
            if controller_type not in valid_types:
                self.warnings.append(f"ros2_controllers.yaml: Uncommon controller type '{controller_type}' for '{controller_name}'")
        
        # Check joints
        if 'joints' in params:
            joints = params['joints']
            if not isinstance(joints, list):
                self.errors.append(f"ros2_controllers.yaml: 'joints' should be a list for controller '{controller_name}'")
            elif len(joints) == 0:
                self.errors.append(f"ros2_controllers.yaml: Empty joints list for controller '{controller_name}'")
    
    def _validate_ompl_planning(self):
        """Validate OMPL planning configuration."""
        if 'ompl_planning' not in self.config_data:
            return
        
        config = self.config_data['ompl_planning']
        
        # Check for planning adapters
        if 'planning_plugin' not in config:
            self.warnings.append("ompl_planning.yaml: Missing 'planning_plugin' configuration")
        
        if 'request_adapters' not in config:
            self.warnings.append("ompl_planning.yaml: Missing 'request_adapters' configuration")
        
        if 'response_adapters' not in config:
            self.warnings.append("ompl_planning.yaml: Missing 'response_adapters' configuration")
        
        # Check planner configurations
        if 'planner_configs' in config:
            planner_configs = config['planner_configs']
            common_planners = ['RRTConnect', 'RRT', 'RRTstar', 'TRRT', 'PRM', 'PRMstar']
            
            configured_planners = set(planner_configs.keys())
            missing_common = set(common_planners) - configured_planners
            
            if missing_common:
                self.warnings.append(f"ompl_planning.yaml: Missing common planners: {sorted(missing_common)}")
    
    def _validate_pilz_limits(self):
        """Validate Pilz cartesian limits configuration."""
        if 'pilz_limits' not in self.config_data:
            return
        
        config = self.config_data['pilz_limits']
        
        if 'cartesian_limits' not in config:
            self.errors.append("pilz_cartesian_limits.yaml: Missing 'cartesian_limits' section")
            return
        
        cartesian_limits = config['cartesian_limits']
        
        # Check required parameters
        required_params = ['max_trans_vel', 'max_trans_acc', 'max_rot_vel', 'max_rot_acc']
        for param in required_params:
            if param not in cartesian_limits:
                self.errors.append(f"pilz_cartesian_limits.yaml: Missing '{param}' parameter")
            else:
                try:
                    value = float(cartesian_limits[param])
                    if value <= 0:
                        self.errors.append(f"pilz_cartesian_limits.yaml: Invalid value for '{param}': {value}")
                except ValueError:
                    self.errors.append(f"pilz_cartesian_limits.yaml: Non-numeric value for '{param}'")
    
    def _validate_planning_scene(self):
        """Validate planning scene monitor parameters."""
        if 'planning_scene' not in self.config_data:
            return
        
        config = self.config_data['planning_scene']
        
        # Check for planning scene monitor configuration
        if 'planning_scene_monitor_options' not in config:
            self.warnings.append("planning_scene_monitor_params.yaml: Missing 'planning_scene_monitor_options' section")
        
        # Check for move_group configuration
        if 'move_group' not in config:
            self.warnings.append("planning_scene_monitor_params.yaml: Missing 'move_group' section")
    
    def _validate_sensors(self):
        """Validate sensors configuration."""
        if 'sensors' not in self.config_data:
            return
        
        config = self.config_data['sensors']
        
        if 'sensors' not in config:
            self.warnings.append("sensors_3d.yaml: Missing 'sensors' section")
            return
        
        sensors = config['sensors']
        
        for sensor_config in sensors:
            if 'sensor_plugin' not in sensor_config:
                self.errors.append("sensors_3d.yaml: Missing 'sensor_plugin' for sensor")
            
            if 'point_cloud_topic' not in sensor_config:
                self.errors.append("sensors_3d.yaml: Missing 'point_cloud_topic' for sensor")
            
            if 'max_range' not in sensor_config:
                self.warnings.append("sensors_3d.yaml: Missing 'max_range' for sensor")
            else:
                try:
                    max_range = float(sensor_config['max_range'])
                    if max_range <= 0:
                        self.errors.append(f"sensors_3d.yaml: Invalid max_range: {max_range}")
                except ValueError:
                    self.errors.append("sensors_3d.yaml: Non-numeric max_range")
    
    def _validate_srdf(self):
        """Validate SRDF configuration."""
        if 'srdf' not in self.config_data:
            return
        
        root = self.config_data['srdf']
        
        # Check for planning groups
        groups = root.findall('.//group')
        if not groups:
            self.errors.append("v2.srdf: No planning groups defined")
        
        group_names = set()
        for group in groups:
            group_name = group.get('name')
            if not group_name:
                self.errors.append("v2.srdf: Planning group without name")
                continue
            
            if group_name in group_names:
                self.errors.append(f"v2.srdf: Duplicate planning group name: {group_name}")
            group_names.add(group_name)
            
            # Check if group has joints or subgroups
            joints = group.findall('joint')
            chains = group.findall('chain')
            subgroups = group.findall('group')
            
            if not joints and not chains and not subgroups:
                self.errors.append(f"v2.srdf: Planning group '{group_name}' has no joints, chains, or subgroups")
        
        # Check for end effectors
        end_effectors = root.findall('.//end_effector')
        if not end_effectors:
            self.warnings.append("v2.srdf: No end effectors defined")
        
        # Check for virtual joints
        virtual_joints = root.findall('.//virtual_joint')
        if not virtual_joints:
            self.warnings.append("v2.srdf: No virtual joints defined")
        
        # Check for disable collisions
        disable_collisions = root.findall('.//disable_collisions')
        if not disable_collisions:
            self.warnings.append("v2.srdf: No collision pairs disabled")
    
    def _validate_urdf(self):
        """Validate URDF configuration."""
        if 'urdf' not in self.config_data:
            return
        
        root = self.config_data['urdf']
        
        # Check for robot element
        if root.tag != 'robot':
            self.errors.append("v2.urdf.xacro: Root element should be 'robot'")
        
        # Check for robot name
        robot_name = root.get('name')
        if not robot_name:
            self.errors.append("v2.urdf.xacro: Robot element missing 'name' attribute")
        
        # Check for xacro includes
        includes = root.findall('.//{http://www.ros.org/wiki/xacro}include')
        if not includes:
            self.warnings.append("v2.urdf.xacro: No xacro includes found")
    
    def _validate_ros2_control(self):
        """Validate ROS2 control configuration."""
        if 'ros2_control' not in self.config_data:
            return
        
        root = self.config_data['ros2_control']
        
        # Find ros2_control block
        ros2_control_elem = None
        for elem in root.iter():
            if elem.tag.endswith('ros2_control') or elem.tag == 'ros2_control':
                ros2_control_elem = elem
                break
        
        if ros2_control_elem is None:
            self.errors.append("v2.ros2_control.xacro: No ros2_control block found")
            return
        
        # Check for hardware element
        hardware = ros2_control_elem.find('.//hardware')
        if hardware is None:
            self.errors.append("v2.ros2_control.xacro: No hardware element found")
        
        # Check for joint elements
        joints = ros2_control_elem.findall('.//joint')
        if not joints:
            self.errors.append("v2.ros2_control.xacro: No joint elements found")
        
        # Check for GPIO elements (Dynamixel servos)
        gpios = ros2_control_elem.findall('.//gpio')
        if not gpios:
            self.errors.append("v2.ros2_control.xacro: No GPIO elements found")
    
    def _validate_joint_consistency(self):
        """Validate joint consistency across all configuration files."""
        # Collect joints from different files
        joints_from_files = {}
        
        # From initial positions
        if 'initial_positions' in self.config_data:
            joints_from_files['initial_positions'] = set(self.config_data['initial_positions'].keys())
        
        # From joint limits
        if 'joint_limits' in self.config_data and 'joint_limits' in self.config_data['joint_limits']:
            joints_from_files['joint_limits'] = set(self.config_data['joint_limits']['joint_limits'].keys())
        
        # From SRDF
        if 'srdf' in self.config_data:
            srdf_joints = set()
            for group in self.config_data['srdf'].findall('.//group'):
                for joint in group.findall('joint'):
                    joint_name = joint.get('name')
                    if joint_name:
                        srdf_joints.add(joint_name)
            joints_from_files['srdf'] = srdf_joints
        
        # From ROS2 control
        if 'ros2_control' in self.config_data:
            ros2_control_joints = set()
            for joint in self.config_data['ros2_control'].findall('.//joint'):
                joint_name = joint.get('name')
                if joint_name:
                    ros2_control_joints.add(joint_name)
            joints_from_files['ros2_control'] = ros2_control_joints
        
        # Compare joint sets
        if len(joints_from_files) > 1:
            all_joints = set()
            for joints in joints_from_files.values():
                all_joints.update(joints)
            
            for file_name, joints in joints_from_files.items():
                missing = all_joints - joints
                if missing:
                    self.warnings.append(f"Joint consistency: {file_name} missing joints: {sorted(missing)}")
    
    def _validate_controller_consistency(self):
        """Validate controller consistency between MoveIt and ROS2 controllers."""
        moveit_controllers = set()
        ros2_controllers = set()
        
        # Get MoveIt controllers
        if 'moveit_controllers' in self.config_data:
            config = self.config_data['moveit_controllers']
            if 'moveit_simple_controller_manager' in config:
                manager = config['moveit_simple_controller_manager']
                if 'controller_names' in manager:
                    moveit_controllers = set(manager['controller_names'])
        
        # Get ROS2 controllers
        if 'ros2_controllers' in self.config_data:
            config = self.config_data['ros2_controllers']
            for key in config.keys():
                if key != 'controller_manager':
                    ros2_controllers.add(key)
        
        # Compare controllers
        if moveit_controllers and ros2_controllers:
            missing_in_ros2 = moveit_controllers - ros2_controllers
            missing_in_moveit = ros2_controllers - moveit_controllers
            
            if missing_in_ros2:
                self.warnings.append(f"Controller consistency: MoveIt controllers not found in ROS2 config: {sorted(missing_in_ros2)}")
            
            if missing_in_moveit:
                self.warnings.append(f"Controller consistency: ROS2 controllers not found in MoveIt config: {sorted(missing_in_moveit)}")
    
    def _validate_planning_group_consistency(self):
        """Validate planning group consistency between SRDF and kinematics."""
        srdf_groups = set()
        kinematics_groups = set()
        
        # Get SRDF groups
        if 'srdf' in self.config_data:
            for group in self.config_data['srdf'].findall('.//group'):
                group_name = group.get('name')
                if group_name:
                    srdf_groups.add(group_name)
        
        # Get kinematics groups
        if 'kinematics' in self.config_data:
            kinematics_groups = set(self.config_data['kinematics'].keys())
        
        # Compare groups
        if srdf_groups and kinematics_groups:
            missing_in_kinematics = srdf_groups - kinematics_groups
            missing_in_srdf = kinematics_groups - srdf_groups
            
            if missing_in_kinematics:
                self.warnings.append(f"Planning group consistency: SRDF groups not found in kinematics config: {sorted(missing_in_kinematics)}")
            
            if missing_in_srdf:
                self.warnings.append(f"Planning group consistency: Kinematics groups not found in SRDF: {sorted(missing_in_srdf)}")
    
    def _print_results(self):
        """Print validation results."""
        print(f"\n{'='*60}")
        print(f"MoveIt Configuration Validation Results")
        print(f"{'='*60}")
        print(f"Configuration Directory: {self.config_dir}")
        print(f"Files Validated: {len(self.config_data)}")
        print(f"Errors: {len(self.errors)}")
        print(f"Warnings: {len(self.warnings)}")
        
        if self.errors:
            print(f"\n❌ ERRORS:")
            for i, error in enumerate(self.errors, 1):
                print(f"  {i:2d}. {error}")
        
        if self.warnings:
            print(f"\n⚠️  WARNINGS:")
            for i, warning in enumerate(self.warnings, 1):
                print(f"  {i:2d}. {warning}")
        
        if not self.errors and not self.warnings:
            print(f"\n✅ All configurations are valid!")
        elif not self.errors:
            print(f"\n✅ Configurations are valid (with warnings)")
        else:
            print(f"\n❌ Configuration has errors that need to be fixed!")
        
        print(f"{'='*60}")


def main():
    if len(sys.argv) != 2:
        print("Usage: python3 validate_moveit_config.py <config_directory>")
        print("Example: python3 validate_moveit_config.py src/kris_moveit_config")
        sys.exit(1)
    
    config_dir = sys.argv[1]
    
    try:
        validator = MoveItConfigValidator(config_dir)
        is_valid = validator.validate()
        
        sys.exit(0 if is_valid else 1)
        
    except Exception as e:
        print(f"Error: {str(e)}")
        sys.exit(1)


if __name__ == "__main__":
    main()