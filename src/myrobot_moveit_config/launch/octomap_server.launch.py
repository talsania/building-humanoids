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
                'resolution': 0.02,
                'frame_id': 'base_link',
                'base_frame_id': 'base_link',
                'height_map': False,
                'color_factor': 0.8,
                'filter_ground': False,
                'compress_map': True,
                'incremental_2D_projection': False,
                'sensor_model/max_range': 2.0,
                'sensor_model/hit': 0.7,
                'sensor_model/miss': 0.4,
                'sensor_model/min': 0.12,
                'sensor_model/max': 0.97,
                'occupancy_min_z': -0.1,
                'occupancy_max_z': 2.0,
                'pointcloud_min_z': -0.1,
                'pointcloud_max_z': 2.0,
            }],
            remappings=[
                ('cloud_in', '/camera/depth_registered/points'),
                ('projected_map', '/map'),
            ]
        )
    ])
