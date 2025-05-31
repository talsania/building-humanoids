import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from moveit_configs_utils import MoveItConfigsBuilder
import yaml

def generate_launch_description():
    moveit_config_pkg_path = get_package_share_directory('myrobot_moveit_config')

    robot_definition_builder = MoveItConfigsBuilder(
        robot_name="myrobot_description", 
        package_name="myrobot_moveit_config"
    )
    robot_definition_builder.robot_description(file_path="config/myrobot_description.urdf.xacro")
    robot_definition_builder.robot_description_semantic(file_path="config/myrobot_description.srdf")
    robot_definition_builder.robot_description_kinematics(file_path="config/kinematics.yaml")
    robot_definition_builder.joint_limits(file_path="config/joint_limits.yaml")
    
    base_moveit_params = robot_definition_builder.to_moveit_configs().to_dict()

    # Attempt to remove CHOMP configurations if they exist from MoveItConfigsBuilder
    if 'chomp' in base_moveit_params:
        print("INFO: Removing 'chomp' dictionary from base_moveit_params.")
        del base_moveit_params['chomp']
    
    # Ensure OMPL's request_adapters is clean if set by MoveItConfigsBuilder (less likely for OMPL)
    if 'ompl' in base_moveit_params and 'request_adapters' in base_moveit_params['ompl']:
        print("INFO: Deleting 'ompl.request_adapters' from base_moveit_params.")
        del base_moveit_params['ompl']['request_adapters']

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

    final_move_group_params = {}
    final_move_group_params.update(base_moveit_params) # base_moveit_params should no longer contain 'chomp'

    # Configure OMPL
    if 'ompl' not in final_move_group_params:
        final_move_group_params['ompl'] = {}
    final_move_group_params['ompl'].update(ompl_config_from_file) 
    final_move_group_params['ompl']['planning_plugin'] = "ompl_interface/OMPLPlanner"
    final_move_group_params['ompl']['request_adapters'] = (
    "default_planner_request_adapters/AddTimeOptimalParameterization "
    "default_planner_request_adapters/FixWorkspaceBounds "
    "default_planner_request_adapters/FixStartStateBounds "
    "default_planner_request_adapters/FixStartStateCollision "
    "default_planner_request_adapters/FixStartStatePathConstraints"
    )

    # Pilz might still be loaded by default by MoveItConfigsBuilder, ensure its adapters are also empty
    if 'pilz_industrial_motion_planner' not in final_move_group_params:
        final_move_group_params['pilz_industrial_motion_planner'] = {}
    final_move_group_params['pilz_industrial_motion_planner']['request_adapters'] = ""


    # Define global request_adapters and other root parameters
    final_move_group_params.update({
        "planning_pipelines": ["ompl"], # Only OMPL
        "default_planning_pipeline": "ompl",
        "request_adapters": [
            "default_planner_request_adapters/AddTimeOptimalParameterization", 
            "default_planner_request_adapters/FixWorkspaceBounds",
            "default_planner_request_adapters/FixStartStateBounds",
            "default_planner_request_adapters/FixStartStateCollision",
            "default_planner_request_adapters/FixStartStatePathConstraints",
        ],
        "default_planner_request_adapters/FixStartStateBounds.start_state_max_bounds_error": 0.1,
    })

    move_group_node = Node(
        package="moveit_ros_move_group",
        executable="move_group",
        output="screen",
        parameters=[final_move_group_params],
        arguments=[
            '--ros-args',
            '--log-level', 'INFO', 
            '--log-level', 'moveit_ros_move_group:=DEBUG',
            '--log-level', 'moveit_ros_planning_pipeline:=DEBUG', 
            '--log-level', 'moveit_planners_ompl:=DEBUG',      
            '--log-level', 'pluginlib:=DEBUG', 
            '--log-level', 'default_planner_request_adapters.add_time_optimal_parameterization:=DEBUG',
        ]
    )

    return LaunchDescription([move_group_node])