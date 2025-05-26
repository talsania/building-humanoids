from launch import LaunchDescription
from launch_ros.actions import Node, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    return LaunchDescription([
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([
                get_package_share_directory('myrobot_moveit_config'), '/launch/realsense.launch.py'
            ]),
            launch_arguments={'pointcloud.enable': 'true'}.items(),
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([
                get_package_share_directory('myrobot_moveit_config'), '/launch/move_group.launch.py'
            ])
        ),
        Node(
            package='rviz2',
            executable='rviz2',
            arguments=['-d', get_package_share_directory('myrobot_moveit_config') + '/launch/moveit_rviz.launch.py'],
            output='screen'
        )
    ])
