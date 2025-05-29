from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch_ros.parameter_descriptions import ParameterValue
import os

def generate_launch_description():
    pkg = FindPackageShare("myrobot_moveit_config")

    # 1) robot_description (xacro → URDF + ros2_control)
    robot_description = ParameterValue(
        Command([
            "xacro ",
            PathJoinSubstitution([pkg, "config", "myrobot_description.urdf.xacro"]),
            " name:=myrobot",
            " port_name:=/dev/ttyUSB0",
            " use_fake_hardware:=false",
            " fake_sensor_commands:=false",
            " initial_positions_file:=",
            PathJoinSubstitution([pkg, "config", "initial_positions.yaml"]),
        ]),
        value_type=str,
    )

    # 2) SRDF - Fixed to use proper file reading
    robot_description_semantic = ParameterValue(
        Command([
            "cat ",
            PathJoinSubstitution([pkg, "config", "myrobot_description.srdf"])
        ]),
        value_type=str,
    )

    # 3) MoveIt config files
    moveit_controllers   = PathJoinSubstitution([pkg, "config", "moveit_controllers_for_launch.yaml"])
    kinematics_yaml      = PathJoinSubstitution([pkg, "config", "kinematics.yaml"])
    joint_limits_yaml    = PathJoinSubstitution([pkg, "config", "joint_limits.yaml"])
    planning_scene_yaml  = PathJoinSubstitution([pkg, "config", "planning_scene_monitor_params.yaml"])
    ompl_planning_yaml   = PathJoinSubstitution([pkg, "config", "ompl_planning.yaml"])

    # 4) ros2_control definitions
    ros2_ctrl_yaml       = PathJoinSubstitution([pkg, "config", "ros2_controllers.yaml"])

    return LaunchDescription([

        # —— robot_state_publisher ——
        Node(
            package="robot_state_publisher",
            executable="robot_state_publisher",
            parameters=[{"robot_description": robot_description}],
            output="screen"
        ),

        # —— joint_state_publisher (for any un‐driven joints) ——
        Node(
            package="joint_state_publisher",
            executable="joint_state_publisher",
            name="missing_joint_state_publisher",
            parameters=[{
                "source_list": ["joint_states"],
                "use_gui": False,
                "rate": 50.0,
                "zeros": {}
            }],
            output="screen"
        ),

        # —— ros2_control_node ——
        Node(
            package="controller_manager",
            executable="ros2_control_node",
            parameters=[
                {"robot_description": robot_description},
                ros2_ctrl_yaml
            ],
            output="screen"
        ),

        # —— spawn controllers ——
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
            output="screen",
        ),
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["dual_arm_controller", "--controller-manager", "/controller_manager"],
            output="screen",
        ),
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["left_arm_controller", "--controller-manager", "/controller_manager"],
            output="screen",
        ),
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["right_arm_controller", "--controller-manager", "/controller_manager"],
            output="screen",
        ),

        # —— publish planning scene ——
        Node(
            package="moveit_ros_planning",
            executable="moveit_publish_scene_from_text",
            name="publish_planning_scene",
            output="screen",
            parameters=[
                {"robot_description": robot_description},
                {"robot_description_semantic": robot_description_semantic},
            ],
        ),

        # —— MoveIt! move_group ——
        Node(
            package="moveit_ros_move_group",
            executable="move_group",
            name="move_group",
            output="screen",
            parameters=[
                {"robot_description": robot_description},
                {"robot_description_semantic": robot_description_semantic},
                moveit_controllers,
                kinematics_yaml,
                joint_limits_yaml,
                planning_scene_yaml,
                ompl_planning_yaml,
                {
                    "moveit_controller_manager": "moveit_simple_controller_manager/MoveItSimpleControllerManager",
                    "planning_scene_monitor.publish_planning_scene": True,
                    "planning_scene_monitor.publish_geometry_updates": True,
                    "planning_scene_monitor.publish_state_updates": True,
                    "planning_scene_monitor.publish_transforms_updates": True,
                    "move_group.jiggle_fraction": 0.05,
                    "move_group.max_safe_path_cost": 1.0,
                }
            ],
        ),

        # —— RViz ——
        Node(
            package="rviz2",
            executable="rviz2",
            name="rviz2",
            output="screen",
            parameters=[
                {"robot_description": robot_description},
                {"robot_description_semantic": robot_description_semantic}
            ],
            arguments=["-d", PathJoinSubstitution([pkg, "config", "moveit.rviz"])],
        ),
    ])