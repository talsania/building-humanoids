from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.parameter_descriptions import ParameterValue
from launch.substitutions import Command, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare



import os

def generate_launch_description():
    # Path substitutions
    description_pkg = FindPackageShare("myrobot_moveit_config")
    
    # Declare robot_description using Xacro
    robot_description_content = ParameterValue(
        Command([
            'xacro ',
            PathJoinSubstitution([
                description_pkg,
                'config',
                'myrobot_description.urdf.xacro'
            ]),
            ' ',
            'use_fake_hardware:=false ',  # important: disable fake hardware
            'initial_positions_file:=',
            PathJoinSubstitution([
                description_pkg,
                'config',
                'initial_positions.yaml'
            ])
        ]),
        value_type=str
    )
    
    controller_config = PathJoinSubstitution([
        FindPackageShare("myrobot_moveit_config"),
        "config",
        "ros2_controllers.yaml"
    ])

    return LaunchDescription([
        Node(
            package="controller_manager",
            executable="ros2_control_node",
            parameters=[
                {"robot_description": robot_description_content},
                controller_config
            ],
            output="screen"
        ),
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
            output="screen"
        ),
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["dual_arm_controller", "--controller-manager", "/controller_manager"],
            output="screen"
        ),
        # Node(
        #     package="controller_manager",
        #     executable="spawner",
        #     arguments=["head_controller", "--controller-manager", "/controller_manager"],
        #     output="screen"
        # ),


        # Uncomment the below two if you ever enable hand controllers
        # Node(
        #     package="controller_manager",
        #     executable="spawner",
        #     arguments=["left_hand_controller", "--controller-manager", "/controller_manager"],
        #     output="screen"
        # ),
        # Node(
        #     package="controller_manager",
        #     executable="spawner",
        #     arguments=["right_hand_controller", "--controller-manager", "/controller_manager"],
        #     output="screen"
        # ),
    ])
