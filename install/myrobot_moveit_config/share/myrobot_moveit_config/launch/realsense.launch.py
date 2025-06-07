from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='realsense2_camera',
            executable='realsense2_camera_node',
            name='realsense2_camera',
            parameters=[{
                'align_depth.enable': True,  # Align depth to color frame
                'pointcloud.enable': True,   # Enable point cloud
                'depth_module.profile': '640x480x30',  # Set resolution/FPS
                'enable_color': True,
                'enable_depth': True,
                'enable_accel': False,  # Disable accelerometer
                'enable_gyro': False,   # Disable gyroscope
                'enable_depth': True,
                'enable_color': True,
                'align_depth.enable': True,
                'pointcloud.enable': True
            }],
            output='screen'
        )
    ])