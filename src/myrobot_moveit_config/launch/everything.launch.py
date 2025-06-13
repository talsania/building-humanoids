from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    pkg_moveit = FindPackageShare("myrobot_moveit_config")

    # 1. Launch hardware control and robot state (includes RViz for visualization)
    planning_and_control = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([pkg_moveit, "launch", "planning_and_control.launch.py"])
        )
    )

    # 2. Launch RealSense camera (with fixed remapping)
    realsense_launch = TimerAction(
        period=3.0,
        actions=[
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    PathJoinSubstitution([pkg_moveit, "launch", "realsense.launch.py"])
                )
            )
        ]
    )

    # 3. Launch OctoMap server
    octomap_launch = TimerAction(
        period=6.0,
        actions=[
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    PathJoinSubstitution([pkg_moveit, "launch", "octomap_server.launch.py"])
                )
            )
        ]
    )

    # 4. Launch MoveGroup with 3D perception (fixed)
    move_group = TimerAction(
        period=9.0,
        actions=[
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    PathJoinSubstitution([pkg_moveit, "launch", "move_group.launch.py"])
                )
            )
        ]
    )

    return LaunchDescription([
        planning_and_control,
        realsense_launch,
        octomap_launch,
        move_group,
    ])