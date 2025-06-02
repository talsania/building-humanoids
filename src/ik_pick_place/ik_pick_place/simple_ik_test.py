#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from moveit_msgs.srv import GetPositionIK
from sensor_msgs.msg import JointState
from geometry_msgs.msg import PoseStamped, Pose

class SimpleIKTest(Node):
    def __init__(self):
        super().__init__('simple_ik_test')
        
        # Service client for IK
        self.ik_client = self.create_client(GetPositionIK, '/compute_ik')
        
        # Wait for services
        self.get_logger().info('Waiting for IK service...')
        if not self.ik_client.wait_for_service(timeout_sec=10.0):
            self.get_logger().error('IK service not available!')
        else:
            self.get_logger().info('IK service connected!')
            
        # Test IK immediately
        self.test_simple_ik()

    def test_simple_ik(self):
        """Test IK with the current left wrist position from FK"""
        try:
            # Create IK request using the EXACT same parameters that worked in FK
            ik_request = GetPositionIK.Request()
            
            # Set up target pose (from your successful FK result)
            target_pose = Pose()
            target_pose.position.x = 0.00787500000003225
            target_pose.position.y = 0.5785253287846371
            target_pose.position.z = -0.5162412691851846
            target_pose.orientation.x = 0.6081581904825833
            target_pose.orientation.y = -0.36075423122806877
            target_pose.orientation.z = -0.6081581904825835
            target_pose.orientation.w = 0.3607542312280552
            
            ik_request.ik_request.group_name = "left_arm"
            ik_request.ik_request.ik_link_name = "left_wrist_2"
            ik_request.ik_request.pose_stamped.header.frame_id = "base_link"
            ik_request.ik_request.pose_stamped.header.stamp = self.get_clock().now().to_msg()
            ik_request.ik_request.pose_stamped.pose = target_pose
            
            # Set seed state (EXACT same as FK that worked)
            ik_request.ik_request.robot_state.joint_state = JointState()
            ik_request.ik_request.robot_state.joint_state.name = ['j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27']
            ik_request.ik_request.robot_state.joint_state.position = [0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0]
            
            # Test 1: With collision checking
            self.get_logger().info("=== TEST 1: IK with collision checking ===")
            ik_request.ik_request.avoid_collisions = True
            ik_request.ik_request.timeout.sec = 5
            
            future = self.ik_client.call_async(ik_request)
            rclpy.spin_until_future_complete(self, future, timeout_sec=10.0)
            
            if future.done():
                response = future.result()
                self.get_logger().info(f"Result: Error code {response.error_code.val}")
                if response.error_code.val == 1:  # SUCCESS
                    self.get_logger().info("SUCCESS! IK solution found with collision checking")
                    solution = response.solution.joint_state
                    self.get_logger().info(f"Solution joints: {solution.name}")
                    self.get_logger().info(f"Solution positions: {[f'{p:.4f}' for p in solution.position]}")
                else:
                    self.get_logger().error(f"FAILED with collision checking: {response.error_code.val}")
            else:
                self.get_logger().error("IK call timed out with collision checking")
            
            # Test 2: Without collision checking
            self.get_logger().info("=== TEST 2: IK without collision checking ===")
            ik_request.ik_request.avoid_collisions = False
            
            future = self.ik_client.call_async(ik_request)
            rclpy.spin_until_future_complete(self, future, timeout_sec=10.0)
            
            if future.done():
                response = future.result()
                self.get_logger().info(f"Result: Error code {response.error_code.val}")
                if response.error_code.val == 1:  # SUCCESS
                    self.get_logger().info("SUCCESS! IK solution found without collision checking")
                    solution = response.solution.joint_state
                    self.get_logger().info(f"Solution joints: {solution.name}")
                    self.get_logger().info(f"Solution positions: {[f'{p:.4f}' for p in solution.position]}")
                else:
                    self.get_logger().error(f"FAILED without collision checking: {response.error_code.val}")
            else:
                self.get_logger().error("IK call timed out without collision checking")
                
            # Test 3: Try with dual_arm group
            self.get_logger().info("=== TEST 3: IK with dual_arm group ===")
            ik_request.ik_request.group_name = "dual_arm"
            ik_request.ik_request.avoid_collisions = False
            
            # For dual_arm, need all joints
            all_joints = ['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17', 'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27']
            all_positions = [0.0, -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0]
            
            ik_request.ik_request.robot_state.joint_state.name = all_joints
            ik_request.ik_request.robot_state.joint_state.position = all_positions
            
            future = self.ik_client.call_async(ik_request)
            rclpy.spin_until_future_complete(self, future, timeout_sec=10.0)
            
            if future.done():
                response = future.result()
                self.get_logger().info(f"Result: Error code {response.error_code.val}")
                if response.error_code.val == 1:  # SUCCESS
                    self.get_logger().info("SUCCESS! IK solution found with dual_arm group")
                    solution = response.solution.joint_state
                    self.get_logger().info(f"Solution joints: {solution.name}")
                    self.get_logger().info(f"Solution positions: {[f'{p:.4f}' for p in solution.position]}")
                else:
                    self.get_logger().error(f"FAILED with dual_arm group: {response.error_code.val}")
            else:
                self.get_logger().error("IK call timed out with dual_arm group")
                
        except Exception as e:
            self.get_logger().error(f"Error in test_simple_ik: {str(e)}")
            import traceback
            self.get_logger().error(f"Traceback: {traceback.format_exc()}")


def main(args=None):
    rclpy.init(args=args)
    
    try:
        node = SimpleIKTest()
        rclpy.spin_once(node, timeout_sec=1.0)  # Just run once
    except KeyboardInterrupt:
        pass
    except Exception as e:
        print(f"Error: {e}")
    finally:
        rclpy.shutdown()


if __name__ == '__main__':
    main()