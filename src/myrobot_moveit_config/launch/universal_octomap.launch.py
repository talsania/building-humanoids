from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    """
    Universal octomap launch that works with any point cloud frame.
    It creates transforms for the most common RealSense frame names.
    """
    
    # Arguments
    resolution = DeclareLaunchArgument('resolution', default_value='0.05')
    max_range = DeclareLaunchArgument('max_range', default_value='3.0')
    
    return LaunchDescription([
        resolution,
        max_range,
        
        # Create base transforms for common RealSense frame names
        # This covers most possible frame configurations
        
        # Root transform
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='world_to_map_tf',
            arguments=['0', '0', '0', '0', '0', '0', 'world', 'map'],
            output='screen'
        ),
        
        # Common RealSense frame variants
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='map_to_camera_depth_optical_frame_tf',
            arguments=['0', '0', '0', '0', '0', '0', 'map', 'camera_depth_optical_frame'],
            output='screen'
        ),
        
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='map_to_camera_color_optical_frame_tf',
            arguments=['0', '0', '0', '0', '0', '0', 'map', 'camera_color_optical_frame'],
            output='screen'
        ),
        
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='map_to_camera_link_tf',
            arguments=['0', '0', '0', '0', '0', '0', 'map', 'camera_link'],
            output='screen'
        ),
        
        # Octomap server with relaxed settings
        Node(
            package='octomap_server',
            executable='octomap_server_node',
            name='octomap_server',
            output='screen',
            parameters=[{
                'resolution': LaunchConfiguration('resolution'),
                'frame_id': 'map',
                'max_range': LaunchConfiguration('max_range'),
                'sensor_model.max_range': LaunchConfiguration('max_range'),
                'sensor_model.min_range': 0.1,
                'sensor_model.hit_prob': 0.7,
                'sensor_model.miss_prob': 0.4,
                'latch': True,
                'publish_free_space': True,
                'filter_ground': False,
                'filter_speckles': True,
                'compress_map': True,
                
                # Very generous boundaries for testing
                'pointcloud_min_x': -10.0,
                'pointcloud_max_x': 10.0,
                'pointcloud_min_y': -10.0,
                'pointcloud_max_y': 10.0,
                'pointcloud_min_z': -5.0,
                'pointcloud_max_z': 5.0,
                'occupancy_min_z': -5.0,
                'occupancy_max_z': 5.0,
                
                # Relaxed transform tolerance
                'transform_tolerance': 1.0,
            }],
            remappings=[
                ('cloud_in', '/camera/realsense2_camera/depth/color/points')
            ]
        )
    ])