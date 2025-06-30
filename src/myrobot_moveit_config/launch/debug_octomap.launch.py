from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    """
    Extreme debug version - very permissive settings to catch any valid points
    """
    
    return LaunchDescription([
        
        # Keep the working TF transform
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='map_to_camera_depth_optical_frame_tf',
            arguments=['0', '0', '0', '0', '0', '0', 'map', 'camera_depth_optical_frame'],
            output='screen'
        ),
        
        # Octomap server with EXTREME debug settings
        Node(
            package='octomap_server',
            executable='octomap_server_node',
            name='octomap_server',
            output='screen',
            parameters=[{
                # Very large resolution to catch any points
                'resolution': 0.2,  
                'frame_id': 'map',
                
                # Accept everything as valid
                'sensor_model.max_range': 100.0,  # Very large range
                'sensor_model.min_range': 0.01,   # Very small minimum
                'sensor_model.hit_prob': 0.95,
                'sensor_model.miss_prob': 0.05,
                
                # Publishing settings
                'latch': False,  # Don't latch for debugging
                'publish_free_space': True,
                'compress_map': False,
                
                # NO filtering - accept everything
                'filter_ground': False,
                'filter_speckles': False,
                
                # Huge boundaries to catch any coordinate system
                'pointcloud_min_x': -1000.0,
                'pointcloud_max_x': 1000.0,
                'pointcloud_min_y': -1000.0,
                'pointcloud_max_y': 1000.0,
                'pointcloud_min_z': -1000.0,
                'pointcloud_max_z': 1000.0,
                'occupancy_min_z': -1000.0,
                'occupancy_max_z': 1000.0,
                
                # Very generous transform tolerance
                'transform_tolerance': 10.0,
                
                # Force updates
                'incremental_2D_projection': False,
            }],
            remappings=[
                ('cloud_in', '/camera/realsense2_camera/depth/color/points')
            ]
        )
    ])