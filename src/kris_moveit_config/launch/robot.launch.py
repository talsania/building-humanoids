import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch_ros.parameter_descriptions import ParameterValue
from launch.actions import DeclareLaunchArgument, TimerAction
from launch.substitutions import LaunchConfiguration
from moveit_configs_utils import MoveItConfigsBuilder
import yaml

def generate_launch_description():
    # Define hardware parameters for your specific setup
    port_name = "/dev/ttyUSB0"  # Your USB port
    baud_rate = "4000000"       # Your baud rate (4M)
    
    pkg = FindPackageShare("kris_moveit_config")
    moveit_config_pkg_path = get_package_share_directory('kris_moveit_config')

    # 1) Build robot_description for REAL hardware
    robot_description = ParameterValue(
        Command([
            "xacro ",
            PathJoinSubstitution([pkg, "config", "v2.urdf.xacro"]),
            " name:=v2",
            " port_name:=", port_name,
            " baud_rate:=", baud_rate,
            " use_fake_hardware:=false",  # REAL HARDWARE
            " fake_sensor_commands:=false",  # REAL SENSORS
            " initial_positions_file:=",
            PathJoinSubstitution([pkg, "config", "initial_positions.yaml"]),
        ]),
        value_type=str,
    )

    # 2) Build MoveIt configuration
    robot_definition_builder = MoveItConfigsBuilder(
        robot_name="v2", 
        package_name="kris_moveit_config"
    )
    robot_definition_builder.robot_description(file_path="config/v2.urdf.xacro")
    robot_definition_builder.robot_description_semantic(file_path="config/v2.srdf")
    robot_definition_builder.robot_description_kinematics(file_path="config/kinematics.yaml")
    robot_definition_builder.joint_limits(file_path="config/joint_limits.yaml")
    
    base_moveit_params = robot_definition_builder.to_moveit_configs().to_dict()

    # Remove CHOMP configurations
    if 'chomp' in base_moveit_params:
        print("INFO: Removing 'chomp' dictionary from base_moveit_params.")
        del base_moveit_params['chomp']
    
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
    except Exception as e:
        print(f"Error loading OMPL planner config file: {e}")

    # Build final MoveIt parameters
    final_move_group_params = {}
    final_move_group_params.update(base_moveit_params)

    # Override robot_description to use the same one as other nodes
    final_move_group_params['robot_description'] = robot_description

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

    # Configure Pilz
    if 'pilz_industrial_motion_planner' not in final_move_group_params:
        final_move_group_params['pilz_industrial_motion_planner'] = {}
    final_move_group_params['pilz_industrial_motion_planner']['request_adapters'] = ""

    # Global parameters - adjusted for real hardware
    final_move_group_params.update({
        "planning_pipelines": ["ompl"],
        "default_planning_pipeline": "ompl",
        "request_adapters": [
            "default_planner_request_adapters/AddTimeOptimalParameterization", 
            "default_planner_request_adapters/FixWorkspaceBounds",
            "default_planner_request_adapters/FixStartStateBounds",
            "default_planner_request_adapters/FixStartStateCollision",
            "default_planner_request_adapters/FixStartStatePathConstraints",
        ],
        "default_planner_request_adapters/FixStartStateBounds.start_state_max_bounds_error": 0.1,
        
        # Critical parameters for real hardware joint control
        "moveit_controller_manager": "moveit_simple_controller_manager/MoveItSimpleControllerManager",
        "planning_scene_monitor.publish_planning_scene": True,
        "planning_scene_monitor.publish_geometry_updates": True,
        "planning_scene_monitor.publish_state_updates": True,
        "planning_scene_monitor.publish_transforms_updates": True,
        "move_group.jiggle_fraction": 0.02,  # Reduced for real hardware safety
        "move_group.max_safe_path_cost": 1.0,
        
        # Real hardware specific parameters
        "trajectory_execution.allowed_execution_duration_scaling": 2.0,  # Allow more time for real hardware
        "trajectory_execution.allowed_goal_duration_margin": 2.0,
        "trajectory_execution.allowed_start_tolerance": 0.05,  # Tighter tolerance for real hardware
    })

    # ros2_control configuration
    ros2_ctrl_yaml = PathJoinSubstitution([pkg, "config", "ros2_controllers.yaml"])
    
    # MoveIt controller configuration
    moveit_controllers = PathJoinSubstitution([pkg, "config", "moveit_controllers_for_launch.yaml"])

    return LaunchDescription([
        # —— robot_state_publisher ——
        Node(
            package="robot_state_publisher",
            executable="robot_state_publisher",
            parameters=[{"robot_description": robot_description}],
            output="screen"
        ),

        # —— ros2_control_node for REAL hardware with enhanced debugging ——
        Node(
            package="controller_manager",
            executable="ros2_control_node",
            parameters=[
                {"robot_description": robot_description},
                ros2_ctrl_yaml,
                {"use_sim_time": False},  # Explicitly set for real hardware
            ],
            output="screen",
            arguments=[
                '--ros-args',
                '--log-level', 'DEBUG',  # Enable debug logging
                '--log-level', 'controller_manager:=DEBUG',
                '--log-level', 'resource_manager:=DEBUG',
            ],
            emulate_tty=True,  # Better terminal output
        ),

        # —— spawn controllers with delays for hardware initialization ——
        TimerAction(
            period=5.0,  # Wait 5 seconds for hardware to initialize
            actions=[
                Node(
                    package="controller_manager",
                    executable="spawner",
                    arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
                    output="screen",
                ),
            ]
        ),
        
        TimerAction(
            period=8.0,  # Wait 8 seconds before spawning joint controllers
            actions=[
                Node(
                    package="controller_manager",
                    executable="spawner",
                    arguments=[
                        "dual_arm_controller", 
                        "--controller-manager", "/controller_manager"
                    ],
                    output="screen",
                ),
            ]
        ),
        
        TimerAction(
            period=10.0,  # Wait 10 seconds before spawning head controller
            actions=[
                Node(
                    package="controller_manager",
                    executable="spawner",
                    arguments=[
                        "head_controller", 
                        "--controller-manager", "/controller_manager"
                    ],
                    output="screen",
                ),
            ]
        ),

        # —— MoveIt! move_group ——
        Node(
            package="moveit_ros_move_group",
            executable="move_group",
            name="move_group",
            output="screen",
            parameters=[
                final_move_group_params,
                moveit_controllers,
            ],
            arguments=[
                '--ros-args',
                '--log-level', 'INFO', 
                '--log-level', 'moveit_ros_move_group:=INFO',
                '--log-level', 'moveit_ros_planning_pipeline:=INFO', 
                '--log-level', 'moveit_planners_ompl:=INFO',      
            ]
        ),

        # —— RViz ——
        Node(
            package="rviz2",
            executable="rviz2",
            name="rviz2",
            output="screen",
            parameters=[
                {"robot_description": robot_description},
                final_move_group_params,
            ],
            arguments=["-d", PathJoinSubstitution([pkg, "config", "moveit.rviz"])],
        ),
    ])