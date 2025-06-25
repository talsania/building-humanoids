from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='octomap_server',
            executable='octomap_server_node',
            name='octomap_server',
            output='screen',
            parameters=[{
                'frame_id': 'camera_link',
                'resolution': 0.05
            }],
            remappings=[
                ('cloud_in', '/camera/realsense2_camera/depth/color/points')
            ]
        )
    ])
