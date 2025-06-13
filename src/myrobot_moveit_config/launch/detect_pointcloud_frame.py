#!/usr/bin/env python3
"""
Quick script to detect what frame your RealSense point cloud is using
"""

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2

class FrameDetector(Node):
    def __init__(self):
        super().__init__('frame_detector')
        
        self.subscription = self.create_subscription(
            PointCloud2,
            '/camera/realsense2_camera/depth/color/points',
            self.pointcloud_callback,
            10
        )
        
        self.frame_detected = False
        self.get_logger().info("Listening for point cloud to detect frame...")
    
    def pointcloud_callback(self, msg):
        if not self.frame_detected:
            self.get_logger().info(f"Point cloud frame detected: {msg.header.frame_id}")
            self.get_logger().info(f"Point cloud size: {msg.width}x{msg.height} = {msg.width * msg.height} points")
            self.get_logger().info(f"Timestamp: {msg.header.stamp.sec}.{msg.header.stamp.nanosec}")
            self.frame_detected = True

def main():
    rclpy.init()
    detector = FrameDetector()
    
    # Spin for a few seconds to detect frame
    try:
        rclpy.spin_once(detector, timeout_sec=10.0)
        if not detector.frame_detected:
            detector.get_logger().error("No point cloud received! Is RealSense running?")
    except KeyboardInterrupt:
        pass
    finally:
        detector.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()