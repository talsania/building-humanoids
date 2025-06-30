#!/usr/bin/env python3
"""
Debug script to check point cloud data
"""

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2
import sensor_msgs_py.point_cloud2 as pc2
import numpy as np

class PointCloudDebugger(Node):
    def __init__(self):
        super().__init__('pointcloud_debugger')
        
        self.subscription = self.create_subscription(
            PointCloud2,
            '/camera/realsense2_camera/depth/color/points',
            self.pointcloud_callback,
            10
        )
        
        self.count = 0
        self.get_logger().info("Debugging point cloud data...")
    
    def pointcloud_callback(self, msg):
        self.count += 1
        
        if self.count % 10 == 1:  # Every 10th message
            # Basic info
            self.get_logger().info(f"=== Point Cloud #{self.count} ===")
            self.get_logger().info(f"Frame: {msg.header.frame_id}")
            self.get_logger().info(f"Timestamp: {msg.header.stamp.sec}.{msg.header.stamp.nanosec}")
            self.get_logger().info(f"Dimensions: {msg.width}x{msg.height} = {msg.width * msg.height} points")
            self.get_logger().info(f"Point step: {msg.point_step}, Row step: {msg.row_step}")
            self.get_logger().info(f"Is dense: {msg.is_dense}")
            self.get_logger().info(f"Data size: {len(msg.data)} bytes")
            
            # Check if we have actual point data
            if len(msg.data) > 0:
                try:
                    # Convert to numpy array to check values
                    points = list(pc2.read_points(msg, field_names=("x", "y", "z"), skip_nans=True))
                    
                    if len(points) > 0:
                        # Sample first few points
                        sample_size = min(5, len(points))
                        self.get_logger().info(f"Total valid points: {len(points)}")
                        self.get_logger().info(f"Sample points (first {sample_size}):")
                        for i, point in enumerate(points[:sample_size]):
                            self.get_logger().info(f"  Point {i}: x={point[0]:.3f}, y={point[1]:.3f}, z={point[2]:.3f}")
                        
                        # Check ranges
                        points_array = np.array(points)
                        x_range = (np.min(points_array[:, 0]), np.max(points_array[:, 0]))
                        y_range = (np.min(points_array[:, 1]), np.max(points_array[:, 1]))
                        z_range = (np.min(points_array[:, 2]), np.max(points_array[:, 2]))
                        
                        self.get_logger().info(f"X range: {x_range[0]:.3f} to {x_range[1]:.3f}")
                        self.get_logger().info(f"Y range: {y_range[0]:.3f} to {y_range[1]:.3f}")
                        self.get_logger().info(f"Z range: {z_range[0]:.3f} to {z_range[1]:.3f}")
                    else:
                        self.get_logger().warn("No valid points found (all NaN)")
                        
                except Exception as e:
                    self.get_logger().error(f"Error processing point cloud: {e}")
            else:
                self.get_logger().warn("Point cloud data is empty")
            
            self.get_logger().info("=" * 40)

def main():
    rclpy.init()
    debugger = PointCloudDebugger()
    
    try:
        rclpy.spin(debugger)
    except KeyboardInterrupt:
        pass
    finally:
        debugger.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()