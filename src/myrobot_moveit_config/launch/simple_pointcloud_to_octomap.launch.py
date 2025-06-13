from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    
    # Declare arguments for octomap configuration
    resolution = DeclareLaunchArgument('resolution', default_value='0.05', 
                                     description='Octomap resolution in meters')
    frame_id = DeclareLaunchArgument('frame_id', default_value='map',
                                   description='Base frame for octomap')
    max_range = DeclareLaunchArgument('max_range', default_value='3.0',
                                    description='Maximum sensor range in meters')
    
    return LaunchDescription([
        resolution,
        frame_id,
        max_range,
        
        # First, let's find out what frame the point cloud is actually using
        # Check with: ros2 topic echo /camera/realsense2_camera/depth/color/points --field header.frame_id
        
        # Create TF chain: map -> camera_depth_optical_frame (common RealSense frame)
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='map_to_camera_tf',
            arguments=['0', '0', '0', '0', '0', '0', 'map', 'camera_depth_optical_frame'],
            output='screen'
        ),
        
        # Octomap server node
        Node(
            package='octomap_server',
            executable='octomap_server_node',
            name='octomap_server',
            output='screen',
            parameters=[{
                # Basic octomap parameters
                'resolution': LaunchConfiguration('resolution'),
                'frame_id': LaunchConfiguration('frame_id'),
                'max_range': LaunchConfiguration('max_range'),
                
                # Sensor model parameters
                'sensor_model.max_range': LaunchConfiguration('max_range'),
                'sensor_model.min_range': 0.1,
                'sensor_model.hit_prob': 0.7,
                'sensor_model.miss_prob': 0.4,
                
                # Publishing parameters
                'latch': True,
                'publish_free_space': True,
                'compress_map': True,
                
                # Filtering parameters
                'filter_ground': False,
                'filter_speckles': True,
                
                # Map boundaries (adjust based on your needs)
                'pointcloud_min_x': -3.0,
                'pointcloud_max_x': 3.0,
                'pointcloud_min_y': -3.0,
                'pointcloud_max_y': 3.0,
                'pointcloud_min_z': -1.0,
                'pointcloud_max_z': 2.0,
                
                # Occupancy map boundaries
                'occupancy_min_z': -1.0,
                'occupancy_max_z': 2.0,
                
                # Update frequency
                'incremental_2D_projection': False,
            }],
            remappings=[
                # Map your actual RealSense topic to octomap input
                ('cloud_in', '/camera/realsense2_camera/depth/color/points')
            ]
        )
    ])