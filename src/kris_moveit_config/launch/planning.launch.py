#!/usr/bin/env python3
import os

from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    pkg = FindPackageShare("kris_moveit_config")

    # 1) robot_description → URDF + ros2_control (real hardware)
    robot_description = ParameterValue(
        Command([
            "xacro ",
            PathJoinSubstitution([pkg, "config", "v2.urdf.xacro"]),
            " name:=v2",
            " port_name:=/dev/ttyUSB0",
            " baud_rate:=4000000",
            " use_fake_hardware:=false",
            " fake_sensor_commands:=false",
            " initial_positions_file:=",
            PathJoinSubstitution([pkg, "config", "initial_positions.yaml"]),
        ]),
        value_type=str,
    )

    # 2) semantic SRDF
    robot_description_semantic = ParameterValue(
        Command([
            "cat ",
            PathJoinSubstitution([pkg, "config", "v2.srdf"])
        ]),
        value_type=str,
    )

    # 3) ros2_control definitions
    ros2_ctrl_yaml = PathJoinSubstitution([pkg, "config", "ros2_controllers.yaml"])

    return LaunchDescription([

        # —— robot_state_publisher ——
        Node(
            package="robot_state_publisher",
            executable="robot_state_publisher",
            parameters=[{"robot_description": robot_description}],
            output="screen"
        ),

        # —— joint_state_publisher ——
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
            arguments=["dual_arm_controller",      "--controller-manager", "/controller_manager"],
            output="screen",
        ),
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["head_controller",          "--controller-manager", "/controller_manager"],
            output="screen",
        ),

        # —— publish planning scene ——
        Node(
            package="moveit_ros_planning",
            executable="moveit_publish_scene_from_text",
            name="publish_planning_scene",
            parameters=[
                {"robot_description": robot_description},
                {"robot_description_semantic": robot_description_semantic},
            ],
            output="screen"
        ),

        # —— RViz ——
        Node(
            package="rviz2",
            executable="rviz2",
            name="rviz2",
            parameters=[
                {"robot_description": robot_description},
                {"robot_description_semantic": robot_description_semantic}
            ],
            arguments=["-d", PathJoinSubstitution([pkg, "config", "moveit.rviz"])],
            output="screen"
        ),
    ])
