from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition

def generate_launch_description():
    """
    This launch file automatically uses the frame from the point cloud data
    and creates minimal TF setup for octomap generation.
    """
    
    # Arguments
    resolution = DeclareLaunchArgument('resolution', default_value='0.05')
    max_range = DeclareLaunchArgument('max_range', default_value='4.0')
    use_rviz = DeclareLaunchArgument('use_rviz', default_value='false')
    
    return LaunchDescription([
        resolution,
        max_range,
        use_rviz,
        
        # Create a world/map frame as root
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='world_frame_tf',
            arguments=['0', '0', '0', '0', '0', '0', 'world', 'map'],
            output='screen'
        ),
        
        # Connect map to the actual camera frame from RealSense
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='map_to_camera_depth_tf',
            arguments=['0', '0', '0', '0', '0', '0', 'map', 'camera_depth_optical_frame'],
            output='screen'
        ),
        
        # Octomap server with automatic frame handling
        Node(
            package='octomap_server',
            executable='octomap_server_node',
            name='octomap_server',
            output='screen',
            parameters=[{
                'resolution': LaunchConfiguration('resolution'),
                'frame_id': 'map',  # Use map as the fixed frame
                'max_range': LaunchConfiguration('max_range'),
                'sensor_model.max_range': LaunchConfiguration('max_range'),
                'sensor_model.min_range': 0.2,
                'sensor_model.hit_prob': 0.7,
                'sensor_model.miss_prob': 0.4,
                'latch': True,
                'publish_free_space': True,
                'filter_ground': False,
                'filter_speckles': True,
                'compress_map': True,
                
                # Generous boundaries for testing
                'pointcloud_min_x': -5.0,
                'pointcloud_max_x': 5.0,
                'pointcloud_min_y': -5.0,
                'pointcloud_max_y': 5.0,
                'pointcloud_min_z': -2.0,
                'pointcloud_max_z': 3.0,
                'occupancy_min_z': -2.0,
                'occupancy_max_z': 3.0,
                
                # Transform tolerance for TF lookups
                'transform_tolerance': 0.5,
            }],
            remappings=[
                ('cloud_in', '/camera/realsense2_camera/depth/color/points')
            ]
        ),
        
        # Optional: RViz for visualization
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2_octomap',
            output='screen',
            condition=IfCondition(LaunchConfiguration('use_rviz'))
        )
    ])