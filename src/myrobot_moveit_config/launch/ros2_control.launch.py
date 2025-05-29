# ros2_control.launch.py
import os
from launch import LaunchDescription
from launch.substitutions import Command
from launch_ros.actions import Node
from launch_ros.descriptions import ParameterValue
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    pkg_share = get_package_share_directory("myrobot_moveit_config")

    xacro_file = os.path.join(pkg_share, "config", "myrobot_description.ros2_control.xacro")
    init_pos     = os.path.join(pkg_share, "config", "initial_positions.yaml")
    controller_y = os.path.join(pkg_share, "config", "ros2_controllers.yaml")

    # robot_description from xacro, with real hardware on /dev/ttyUSB0 @ 4 Mbps
    robot_description = ParameterValue(
        Command([
            "xacro", " ",
            xacro_file,
            " use_fake_hardware:=false",
            " port_name:=/dev/ttyUSB0",
            " baud_rate:=4000000",
            " initial_positions_file:=" + init_pos
        ]),
        value_type=str
    )

    return LaunchDescription([
        # 1) Start the hardware + controller_manager
        Node(
            package="controller_manager",
            executable="ros2_control_node",
            parameters=[
                {"robot_description": robot_description},
                controller_y
            ],
            output="screen"
        ),

        # 2) Spawn the JointStateBroadcaster
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
            output="screen"
        ),

        # 3) Spawn all three trajectory controllers
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["dual_arm_controller", "--controller-manager", "/controller_manager"],
            output="screen"
        ),
        # Node(
        #     package="controller_manager",
        #     executable="spawner",
        #     arguments=["left_arm_controller", "--controller-manager", "/controller_manager"],
        #     output="screen"
        # ),
        # Node(
        #     package="controller_manager",
        #     executable="spawner",
        #     arguments=["right_arm_controller", "--controller-manager", "/controller_manager"],
        #     output="screen"
        # ),
    ])
