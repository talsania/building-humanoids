# from launch import LaunchDescription
# from launch.actions import IncludeLaunchDescription, TimerAction
# from launch.launch_description_sources import PythonLaunchDescriptionSource
# from launch.substitutions import PathJoinSubstitution
# from launch_ros.substitutions import FindPackageShare
# from launch_ros.actions import Node

# def generate_launch_description():
#     pkg_moveit = FindPackageShare("myrobot_moveit_config")
#     pkg_gripper = FindPackageShare("gripper_control")  # your gripper package

#     # 1. Launch gripper_control_node immediately
#     gripper_node = Node(
#         package="gripper_control",
#         executable="gripper_control_node",
#         name="gripper_control_node",
#         output="screen"
#     )

#     # 2. Delay MoveGroup by 5 seconds
#     move_group = TimerAction(
#         period=5.0,
#         actions=[
#             IncludeLaunchDescription(
#                 PythonLaunchDescriptionSource(
#                     PathJoinSubstitution([pkg_moveit, "launch", "move_group.launch.py"])
#                 )
#             )
#         ]
#     )

#     # 3. Delay planning_and_control by 5 seconds
#     planning_and_control = TimerAction(
#         period=5.0,
#         actions=[
#             IncludeLaunchDescription(
#                 PythonLaunchDescriptionSource(
#                     PathJoinSubstitution([pkg_moveit, "launch", "planning_and_control.launch.py"])
#                 )
#             )
#         ]
#     )

#     return LaunchDescription([
#         gripper_node,
#         move_group,
#         planning_and_control
#     ])

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    pkg_moveit = FindPackageShare("myrobot_moveit_config")

    # Launch MoveGroup
    move_group = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([pkg_moveit, "launch", "move_group.launch.py"])
        )
    )

    # Launch planning and control
    planning_and_control = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([pkg_moveit, "launch", "planning_and_control.launch.py"])
        )
    )

    return LaunchDescription([
        move_group,
        planning_and_control,
    ])
