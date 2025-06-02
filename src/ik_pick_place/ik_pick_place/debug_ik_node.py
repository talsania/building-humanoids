#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from moveit_msgs.srv import GetPositionFK
from sensor_msgs.msg import JointState
from geometry_msgs.msg import Pose
import time

class DebugIKNode(Node):
    def __init__(self):
        super().__init__('debug_ik_node')
        
        # Service client for Forward Kinematics
        self.fk_client = self.create_client(
            GetPositionFK,
            '/compute_fk'
        )
        
        # Subscriber for current joint states
        self.joint_state_subscriber = self.create_subscription(
            JointState,
            '/joint_states',
            self.joint_state_callback,
            10
        )
        
        self.current_joint_state = None
        
        # Wait for services
        self.get_logger().info('Waiting for FK service...')
        if not self.fk_client.wait_for_service(timeout_sec=10.0):
            self.get_logger().error('FK service not available!')
        else:
            self.get_logger().info('FK service connected!')
        
        # Robot configuration
        self.left_arm_joints = ["j21", "j22", "j23", "j24", "j25", "j26", "j27"]
        self.right_arm_joints = ["j11", "j12", "j13", "j14", "j15", "j16", "j17"]
        
        self.get_logger().info('Debug IK Node initialized!')
        self.get_logger().info('Waiting for joint states...')

    def joint_state_callback(self, msg):
        """Store current joint state"""
        if self.current_joint_state is None:
            self.current_joint_state = msg
            self.get_logger().info('Received first joint state, analyzing...')
            time.sleep(1.0)  # Give it a moment
            self.analyze_current_pose()

    def analyze_current_pose(self):
        """Analyze current robot pose using Forward Kinematics"""
        try:
            if self.current_joint_state is None:
                self.get_logger().error('No joint state available')
                return
            
            self.get_logger().info('Starting pose analysis...')
            
            # Get current left wrist position
            left_pose = self.get_current_pose("left_arm", "left_wrist_2", self.left_arm_joints)
            if left_pose:
                self.get_logger().info(f"Current LEFT wrist pose:")
                self.get_logger().info(f"  Position: ({left_pose.position.x:.3f}, {left_pose.position.y:.3f}, {left_pose.position.z:.3f})")
                self.get_logger().info(f"  Orientation: ({left_pose.orientation.x:.3f}, {left_pose.orientation.y:.3f}, {left_pose.orientation.z:.3f}, {left_pose.orientation.w:.3f})")
            else:
                self.get_logger().error("Failed to get left wrist pose")
                return
            
            # Get current right wrist position  
            right_pose = self.get_current_pose("right_arm", "right_wrist_2", self.right_arm_joints)
            if right_pose:
                self.get_logger().info(f"Current RIGHT wrist pose:")
                self.get_logger().info(f"  Position: ({right_pose.position.x:.3f}, {right_pose.position.y:.3f}, {right_pose.position.z:.3f})")
                self.get_logger().info(f"  Orientation: ({right_pose.orientation.x:.3f}, {right_pose.orientation.y:.3f}, {right_pose.orientation.z:.3f}, {right_pose.orientation.w:.3f})")
            else:
                self.get_logger().error("Failed to get right wrist pose")
            
            # Test simple movements from current position
            if left_pose:
                self.test_nearby_poses(left_pose, "left")
            
            if right_pose:
                self.test_nearby_poses(right_pose, "right")
            
            self.get_logger().info('Pose analysis complete!')
            
        except Exception as e:
            self.get_logger().error(f"Error in analyze_current_pose: {str(e)}")
            import traceback
            self.get_logger().error(f"Traceback: {traceback.format_exc()}")

    def get_current_pose(self, planning_group, link_name, joint_names):
        """Get current pose of a link using Forward Kinematics"""
        try:
            fk_request = GetPositionFK.Request()
            fk_request.header.frame_id = "base_link"
            fk_request.fk_link_names = [link_name]
            
            # Set current joint state for this arm
            fk_request.robot_state.joint_state = JointState()
            fk_request.robot_state.joint_state.header.frame_id = ""
            
            self.get_logger().info(f"Setting up FK request for {link_name}")
            self.get_logger().info(f"Looking for joints: {joint_names}")
            self.get_logger().info(f"Available joints: {self.current_joint_state.name}")
            
            for joint_name in joint_names:
                if joint_name in self.current_joint_state.name:
                    idx = self.current_joint_state.name.index(joint_name)
                    position = self.current_joint_state.position[idx]
                    fk_request.robot_state.joint_state.name.append(joint_name)
                    fk_request.robot_state.joint_state.position.append(position)
                    self.get_logger().info(f"  Added joint {joint_name}: {position:.4f}")
                else:
                    self.get_logger().warning(f"  Joint {joint_name} not found in current state!")
            
            self.get_logger().info(f"Calling FK service for {link_name}...")
            future = self.fk_client.call_async(fk_request)
            rclpy.spin_until_future_complete(self, future, timeout_sec=10.0)
            
            if not future.done():
                self.get_logger().error("FK service call timed out")
                return None
            
            response = future.result()
            self.get_logger().info(f"FK response error code: {response.error_code.val}")
            
            if response.error_code.val == 1:  # SUCCESS
                pose = response.pose_stamped[0].pose
                self.get_logger().info(f"FK SUCCESS for {link_name}")
                return pose
            else:
                self.get_logger().error(f"FK failed for {link_name} with error: {response.error_code.val}")
                return None
            
        except Exception as e:
            self.get_logger().error(f"Error in get_current_pose: {str(e)}")
            import traceback
            self.get_logger().error(f"Traceback: {traceback.format_exc()}")
            return None

    def test_nearby_poses(self, current_pose, arm_name):
        """Suggest test poses near current position"""
        self.get_logger().info(f"\n=== SUGGESTED TEST POSES FOR {arm_name.upper()} ARM ===")
        
        # Current position
        x, y, z = current_pose.position.x, current_pose.position.y, current_pose.position.z
        
        # Suggest poses very close to current
        test_poses = [
            (x, y, z, "Current position"),
            (x, y, z + 0.02, "2cm up"),
            (x, y, z - 0.02, "2cm down"),
            (x + 0.02, y, z, "2cm forward"),
            (x - 0.02, y, z, "2cm back"),
            (x, y + 0.02, z, "2cm to side"),
        ]
        
        for test_x, test_y, test_z, description in test_poses:
            # Create transformation matrix
            matrix_data = [
                1.0, 0.0, 0.0, test_x,
                0.0, 1.0, 0.0, test_y,
                0.0, 0.0, 1.0, test_z,
                0.0, 0.0, 0.0, 1.0
            ]
            
            matrix_str = str(matrix_data).replace('[', '').replace(']', '').replace(' ', '')
            
            self.get_logger().info(f"{description}: ({test_x:.3f}, {test_y:.3f}, {test_z:.3f})")
            self.get_logger().info(f"  Command: ros2 topic pub --once /target_pose_matrix std_msgs/msg/Float64MultiArray \"data: [{matrix_str}]\"")
        
        self.get_logger().info("\nTry these commands to test IK near current position!")


def main(args=None):
    rclpy.init(args=args)
    
    try:
        node = DebugIKNode()
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    except Exception as e:
        print(f"Error: {e}")
    finally:
        rclpy.shutdown()


if __name__ == '__main__':
    main()