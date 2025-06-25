from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    pkg_moveit = FindPackageShare("kris_moveit_config")

    # Launch MoveGroup
    move_group = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([pkg_moveit, "launch", "move_group.launch.py"])
        )
    )

    # Launch planning and control
    planning = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([pkg_moveit, "launch", "planning.launch.py"])
        )
    )

    return LaunchDescription([
        move_group,
        planning,
    ])