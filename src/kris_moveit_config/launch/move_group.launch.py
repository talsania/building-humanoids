import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from moveit_configs_utils import MoveItConfigsBuilder
import yaml

def generate_launch_description():
    moveit_config_pkg_path = get_package_share_directory('kris_moveit_config')

    robot_definition_builder = MoveItConfigsBuilder(
        robot_name="myrobot_description", 
        package_name="kris_moveit_config"
    )
    robot_definition_builder.robot_description(file_path="config/v2.urdf.xacro")
    robot_definition_builder.robot_description_semantic(file_path="config/v2.srdf")
    robot_definition_builder.robot_description_kinematics(file_path="config/kinematics.yaml")
    robot_definition_builder.joint_limits(file_path="config/joint_limits.yaml")
    
    base_moveit_params = robot_definition_builder.to_moveit_configs().to_dict()

    # Remove CHOMP configurations if they exist
    if 'chomp' in base_moveit_params:
        print("INFO: Removing 'chomp' dictionary from base_moveit_params.")
        del base_moveit_params['chomp']
    
    # Clean OMPL request_adapters if set by MoveItConfigsBuilder
    if 'ompl' in base_moveit_params and 'request_adapters' in base_moveit_params['ompl']:
        print("INFO: Deleting 'ompl.request_adapters' from base_moveit_params.")
        del base_moveit_params['ompl']['request_adapters']

    # Load OMPL configuration
    ompl_specific_planner_config_file_path = os.path.join(moveit_config_pkg_path, 'config', 'ompl_planning.yaml')
    ompl_config_from_file = {}
    try:
        with open(ompl_specific_planner_config_file_path, 'r') as f:
            loaded_yaml = yaml.safe_load(f)
            if 'ompl' in loaded_yaml and isinstance(loaded_yaml['ompl'], dict):
                ompl_config_from_file = loaded_yaml['ompl'] 
            else:
                print(f"WARNING: {ompl_specific_planner_config_file_path} is not structured with 'ompl:' as the root key.")
    except Exception as e:
        print(f"Error loading OMPL planner config file '{ompl_specific_planner_config_file_path}': {e}")

    # Load MoveIt controllers configuration - THIS WAS MISSING!
    moveit_controllers_file = os.path.join(moveit_config_pkg_path, 'config', 'moveit_controllers.yaml')
    moveit_controllers = {}
    try:
        with open(moveit_controllers_file, 'r') as f:
            moveit_controllers = yaml.safe_load(f) or {}
            print(f"INFO: Loaded MoveIt controllers configuration from {moveit_controllers_file}")
    except Exception as e:
        print(f"Error loading MoveIt controllers file '{moveit_controllers_file}': {e}")

    # Load additional configuration files (optional)
    planning_scene_file = os.path.join(moveit_config_pkg_path, 'config', 'planning_scene_monitor_params.yaml')
    planning_scene_params = {}
    try:
        with open(planning_scene_file, 'r') as f:
            planning_scene_params = yaml.safe_load(f) or {}
            print(f"INFO: Loaded planning scene monitor params from {planning_scene_file}")
    except Exception as e:
        print(f"Warning: Could not load planning scene params from '{planning_scene_file}': {e}")
        print("INFO: Using default planning scene monitor parameters")

    final_move_group_params = {}
    final_move_group_params.update(base_moveit_params)

    # Configure OMPL
    if 'ompl' not in final_move_group_params:
        final_move_group_params['ompl'] = {}
    final_move_group_params['ompl'].update(ompl_config_from_file) 
    final_move_group_params['ompl']['planning_plugin'] = "ompl_interface/OMPLPlanner"
    final_move_group_params['ompl']['request_adapters'] = (
        "default_planner_request_adapters/FixWorkspaceBounds "
        "default_planner_request_adapters/FixStartStateBounds "
        "default_planner_request_adapters/FixStartStateCollision "
        "default_planner_request_adapters/FixStartStatePathConstraints "
        "default_planner_request_adapters/AddTimeOptimalParameterization"
    )

    # Configure Pilz (disable request adapters)
    if 'pilz_industrial_motion_planner' not in final_move_group_params:
        final_move_group_params['pilz_industrial_motion_planner'] = {}
    final_move_group_params['pilz_industrial_motion_planner']['request_adapters'] = ""

    # Add controller configuration - THIS IS CRITICAL
    final_move_group_params.update(moveit_controllers)
    
    # Add planning scene monitor parameters
    final_move_group_params.update(planning_scene_params)
    
    # Ensure moveit_controller_manager is set (critical to prevent segfault)
    if 'moveit_controller_manager' not in final_move_group_params:
        final_move_group_params['moveit_controller_manager'] = 'moveit_simple_controller_manager/MoveItSimpleControllerManager'

    # Configure planning pipelines and execution
    final_move_group_params.update({
        "planning_pipelines": ["ompl"],
        "default_planning_pipeline": "ompl",
        
        # Request adapters configuration
        "request_adapters": [
            "default_planner_request_adapters/FixWorkspaceBounds",
            "default_planner_request_adapters/FixStartStateBounds",
            "default_planner_request_adapters/FixStartStateCollision",
            "default_planner_request_adapters/FixStartStatePathConstraints",
            "default_planner_request_adapters/AddTimeOptimalParameterization",
        ],
        
        # Planning configuration
        "default_planner_request_adapters/FixStartStateBounds.start_state_max_bounds_error": 0.1,
        "planning_scene_monitor.publish_planning_scene": True,
        "planning_scene_monitor.publish_geometry_updates": True,
        "planning_scene_monitor.publish_state_updates": True,
        "planning_scene_monitor.publish_transforms_updates": True,
        
        # Trajectory execution settings
        "trajectory_execution.allowed_execution_duration_scaling": 2.0,
        "trajectory_execution.allowed_goal_duration_margin": 1.0,
        "trajectory_execution.allowed_start_tolerance": 0.05,
        "trajectory_execution.execution_duration_monitoring": False,
        
        # Enable trajectory execution
        "allow_trajectory_execution": True,
        "execution_type": "InterpolationRaw",
        
        # Planning configuration to help with constraint issues
        "move_group.jiggle_fraction": 0.05,
        "move_group.max_safe_path_cost": 1.0,
        "move_group.planning_time": 10.0,  # Increase planning time
        "move_group.max_planning_attempts": 10,  # More attempts
        
        # OMPL specific settings to help with sampling
        "ompl.default_num_sampling_attempts": 100,
        "ompl.goal_bias": 0.05,
        "ompl.range": 0.0,  # Use full range
    })

    # Debug: Print some key parameters
    print("DEBUG: Final parameters include:")
    print(f"  - moveit_controller_manager: {final_move_group_params.get('moveit_controller_manager', 'NOT SET')}")
    print(f"  - planning_pipelines: {final_move_group_params.get('planning_pipelines', 'NOT SET')}")
    print(f"  - Controller manager keys: {[k for k in final_move_group_params.keys() if 'controller' in k.lower()]}")

    move_group_node = Node(
        package="moveit_ros_move_group",
        executable="move_group",
        output="screen",
        parameters=[final_move_group_params],
        arguments=[
            '--ros-args',
            '--log-level', 'INFO', 
            '--log-level', 'moveit_ros_move_group:=INFO',
            '--log-level', 'moveit_ros_planning_pipeline:=INFO', 
            '--log-level', 'moveit_planners_ompl:=WARN',
            '--log-level', 'pluginlib:=WARN', 
        ]
    )

    return LaunchDescription([move_group_node])