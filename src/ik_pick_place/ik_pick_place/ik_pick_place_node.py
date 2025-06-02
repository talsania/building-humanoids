#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor

from geometry_msgs.msg import PoseStamped, Pose
from std_msgs.msg import Float64MultiArray, String
from moveit_msgs.action import MoveGroup
from moveit_msgs.msg import (
    MotionPlanRequest,
    PlanningOptions,
    Constraints,
    JointConstraint,
    WorkspaceParameters,
    RobotState
)
from moveit_msgs.srv import GetPositionIK
from sensor_msgs.msg import JointState

import numpy as np
from rclpy.action import ActionClient
import time

class SeparatePickPlaceNode(Node):
    def __init__(self):
        super().__init__('separate_pick_place_node')
        
        # Use reentrant callback group for action clients
        self.callback_group = ReentrantCallbackGroup()
        
        # Action client for MoveGroup
        self.move_group_client = ActionClient(
            self,
            MoveGroup,
            '/move_action',
            callback_group=self.callback_group
        )
        
        # Service client for IK
        self.ik_client = self.create_client(
            GetPositionIK,
            '/compute_ik',
            callback_group=self.callback_group
        )
        
        # Subscriber for current joint states
        self.joint_state_subscriber = self.create_subscription(
            JointState,
            '/joint_states',
            self.joint_state_callback,
            10,
            callback_group=self.callback_group
        )
        
        # Separate command subscribers
        self.pick_subscriber = self.create_subscription(
            Float64MultiArray,
            '/pick_command',
            self.pick_command_callback,
            10,
            callback_group=self.callback_group
        )
        
        self.place_subscriber = self.create_subscription(
            Float64MultiArray,
            '/place_command',
            self.place_command_callback,
            10,
            callback_group=self.callback_group
        )
        
        self.home_subscriber = self.create_subscription(
            String,
            '/home_command',
            self.home_command_callback,
            10,
            callback_group=self.callback_group
        )
        
        # Status publisher
        self.status_publisher = self.create_publisher(
            String,
            '/robot_status',
            10
        )
        
        # Robot state tracking
        self.is_busy = False
        self.current_operation = None
        
        # Wait for services and action servers
        self.get_logger().info('Waiting for MoveGroup action server...')
        if not self.move_group_client.wait_for_server(timeout_sec=15.0):
            self.get_logger().error('MoveGroup action server not available!')
        else:
            self.get_logger().info('MoveGroup action server connected!')
        
        self.get_logger().info('Waiting for IK service...')
        if not self.ik_client.wait_for_service(timeout_sec=15.0):
            self.get_logger().error('IK service not available!')
        else:
            self.get_logger().info('IK service connected!')
        
        # Robot configuration
        self.planning_group = "dual_arm"
        self.base_frame = "base_link"
        
        # Joint names for both arms
        self.right_arm_joints = ["j11", "j12", "j13", "j14", "j15", "j16", "j17"]
        self.left_arm_joints = ["j21", "j22", "j23", "j24", "j25", "j26", "j27"]
        self.all_joints = self.right_arm_joints + self.left_arm_joints
        
        # End effector links
        self.right_end_effector = "right_wrist_2"
        self.left_end_effector = "left_wrist_2"
        
        # Current joint state
        self.current_joint_state = None
        
        # Home positions
        self.right_home_joints = [0.0, -0.5, 0.0, 0.0, 0.0, 0.0, 0.0]
        self.left_home_joints = [0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0]
        self.dual_home_joints = self.right_home_joints + self.left_home_joints
        
        # Store last pick pose for place command
        self.last_pick_pose = None
        self.last_arm_used = None
        
        self.get_logger().info('=== Separate Pick and Place Node Initialized ===')
        self.get_logger().info('Available Commands:')
        self.get_logger().info('  1. PICK: ros2 topic pub --once /pick_command std_msgs/msg/Float64MultiArray "data: [...]"')
        self.get_logger().info('  2. PLACE: ros2 topic pub --once /place_command std_msgs/msg/Float64MultiArray "data: [...]"')
        self.get_logger().info('  3. HOME: ros2 topic pub --once /home_command std_msgs/msg/String "data: go_home"')
        self.get_logger().info('If y > 0: Left arm will move, if y < 0: Right arm will move')

    def joint_state_callback(self, msg):
        """Store current joint state for IK seed"""
        self.current_joint_state = msg
        if hasattr(self, '_joint_state_received'):
            return
        self._joint_state_received = True
        self.get_logger().info(f"Received joint states for joints: {msg.name[:5]}...")

    def pick_command_callback(self, msg):
        """Handle pick command"""
        if self.is_busy:
            self.get_logger().warning(f"Robot is busy with {self.current_operation}. Please wait.")
            self.publish_status(f"BUSY: Currently executing {self.current_operation}")
            return
            
        try:
            if len(msg.data) != 16:
                self.get_logger().error(f'Expected 16 elements for 4x4 matrix, got {len(msg.data)}')
                return
            
            self.is_busy = True
            self.current_operation = "PICK"
            
            # Convert to 4x4 numpy matrix
            matrix = np.array(msg.data).reshape(4, 4)
            self.get_logger().info(f'=== PICK COMMAND ===')
            self.get_logger().info(f'Target matrix:\n{matrix}')
            
            # Convert matrix to pose
            target_pose = self.matrix_to_pose(matrix)
            
            # Determine which arm to use
            if target_pose.position.y > 0:
                arm_type = "left"
                end_effector_link = self.left_end_effector
                self.get_logger().info(f"Target y={target_pose.position.y:.3f} > 0, using LEFT arm")
            else:
                arm_type = "right"
                end_effector_link = self.right_end_effector
                self.get_logger().info(f"Target y={target_pose.position.y:.3f} < 0, using RIGHT arm")
            
            # Store target pose temporarily for later use
            self._temp_target_pose = target_pose
            
            # Execute pick operation asynchronously
            self.execute_pick(target_pose, arm_type, end_effector_link)
            
            # Note: Success/failure will be determined by callbacks
            # Don't set is_busy = False here - let callbacks handle it
            
        except Exception as e:
            self.is_busy = False
            self.current_operation = None
            self.get_logger().error(f'Error processing pick command: {str(e)}')
            self.publish_status(f"Pick command error: {str(e)}")

    def place_command_callback(self, msg):
        """Handle place command"""
        if self.is_busy:
            self.get_logger().warning(f"Robot is busy with {self.current_operation}. Please wait.")
            self.publish_status(f"BUSY: Currently executing {self.current_operation}")
            return
            
        try:
            if len(msg.data) != 16:
                self.get_logger().error(f'Expected 16 elements for 4x4 matrix, got {len(msg.data)}')
                return
            
            self.is_busy = True
            self.current_operation = "PLACE"
            
            # Convert to 4x4 numpy matrix
            matrix = np.array(msg.data).reshape(4, 4)
            self.get_logger().info(f'=== PLACE COMMAND ===')
            self.get_logger().info(f'Target matrix:\n{matrix}')
            
            # Convert matrix to pose
            target_pose = self.matrix_to_pose(matrix)
            
            # Use same arm as last pick operation
            if self.last_arm_used is None:
                self.get_logger().warning("No previous pick operation found. Using arm based on Y coordinate.")
                if target_pose.position.y > 0:
                    arm_type = "left"
                    end_effector_link = self.left_end_effector
                else:
                    arm_type = "right"
                    end_effector_link = self.right_end_effector
            else:
                arm_type = self.last_arm_used
                end_effector_link = self.left_end_effector if arm_type == "left" else self.right_end_effector
                self.get_logger().info(f"Using {arm_type} arm from previous pick operation")
            
            # Execute place operation asynchronously
            self.execute_place(target_pose, arm_type, end_effector_link)
            
            # Note: Success/failure will be determined by callbacks
            # Don't set is_busy = False here - let callbacks handle it
            
        except Exception as e:
            self.is_busy = False
            self.current_operation = None
            self.get_logger().error(f'Error processing place command: {str(e)}')
            self.publish_status(f"Place command error: {str(e)}")

    def home_command_callback(self, msg):
        """Handle home command"""
        if self.is_busy:
            self.get_logger().warning(f"Robot is busy with {self.current_operation}. Please wait.")
            self.publish_status(f"BUSY: Currently executing {self.current_operation}")
            return
            
        try:
            self.is_busy = True
            self.current_operation = "HOME"
            
            self.get_logger().info(f'=== HOME COMMAND ===')
            self.get_logger().info('Returning robot to home position...')
            
            # Execute home operation asynchronously
            self.execute_home()
            
            # Note: Success/failure will be determined by callbacks
            # Don't set is_busy = False here - let callbacks handle it
            
        except Exception as e:
            self.is_busy = False
            self.current_operation = None
            self.get_logger().error(f'Error processing home command: {str(e)}')
            self.publish_status(f"Home command error: {str(e)}")

    def matrix_to_pose(self, matrix):
        """Convert 4x4 transformation matrix to geometry_msgs/Pose"""
        pose = Pose()
        
        # Extract position (translation part)
        pose.position.x = float(matrix[0, 3])
        pose.position.y = float(matrix[1, 3])
        pose.position.z = float(matrix[2, 3])
        
        # Use known working orientation
        pose.orientation.x = 0.6081581904825833
        pose.orientation.y = -0.36075423122806877
        pose.orientation.z = -0.6081581904825835
        pose.orientation.w = 0.3607542312280552
        
        return pose

    def execute_pick(self, target_pose, arm_type, end_effector_link):
        """Execute pick operation"""
        try:
            self.publish_status(f"Starting PICK with {arm_type} arm...")
            
            # Check if we have joint states
            if self.current_joint_state is None:
                self.get_logger().warning("No joint states available")
                return False
            
            # Move to target position
            self.get_logger().info("Moving to pick position...")
            target_joints = self.solve_ik_for_pose(target_pose, end_effector_link)
            if target_joints is None:
                self.publish_status("Failed to solve IK for pick position")
                return False
            
            # Start async movement
            self.move_to_joint_state_async(target_joints, arm_type, "PICK")
            return True  # Return immediately, completion handled by callback
            
        except Exception as e:
            self.get_logger().error(f"Error in execute_pick: {str(e)}")
            return False

    def execute_place(self, target_pose, arm_type, end_effector_link):
        """Execute place operation"""
        try:
            self.publish_status(f"Starting PLACE with {arm_type} arm...")
            
            # Move to place position
            self.get_logger().info(f"Moving {arm_type} arm to place position...")
            target_joints = self.solve_ik_for_pose(target_pose, end_effector_link)
            if target_joints is None:
                self.publish_status("Failed to solve IK for place position")
                return False
            
            # Start async movement
            self.move_to_joint_state_async(target_joints, arm_type, "PLACE")
            return True  # Return immediately, completion handled by callback
            
        except Exception as e:
            self.get_logger().error(f"Error in execute_place: {str(e)}")
            return False

    def execute_home(self):
        """Execute home operation"""
        try:
            self.publish_status("Returning to home position...")
            
            # Start async movement
            self.move_to_joint_state_async(self.dual_home_joints, "both", "HOME")
            return True  # Return immediately, completion handled by callback
            
        except Exception as e:
            self.get_logger().error(f"Error in execute_home: {str(e)}")
            return False

    def solve_ik_for_pose(self, target_pose, end_effector_link):
        """Solve inverse kinematics for the target pose"""
        try:
            # Create IK request
            ik_request = GetPositionIK.Request()
            
            # Determine which arm planning group to use
            if end_effector_link == self.left_end_effector:
                ik_planning_group = "left_arm"
                arm_joints = self.left_arm_joints
                arm_home = self.left_home_joints
            else:
                ik_planning_group = "right_arm"
                arm_joints = self.right_arm_joints
                arm_home = self.right_home_joints
            
            # Set up the IK request
            ik_request.ik_request.group_name = ik_planning_group
            ik_request.ik_request.ik_link_name = end_effector_link
            ik_request.ik_request.pose_stamped.header.frame_id = self.base_frame
            ik_request.ik_request.pose_stamped.header.stamp = self.get_clock().now().to_msg()
            ik_request.ik_request.pose_stamped.pose = target_pose
            
            # Set seed state using current joint positions
            ik_request.ik_request.robot_state.joint_state = JointState()
            
            if self.current_joint_state is not None:
                # Use current joint state as seed for the specific arm
                for joint_name in arm_joints:
                    if joint_name in self.current_joint_state.name:
                        idx = self.current_joint_state.name.index(joint_name)
                        ik_request.ik_request.robot_state.joint_state.name.append(joint_name)
                        ik_request.ik_request.robot_state.joint_state.position.append(
                            self.current_joint_state.position[idx]
                        )
                    else:
                        # If joint not in current state, use home position
                        home_idx = arm_joints.index(joint_name)
                        ik_request.ik_request.robot_state.joint_state.name.append(joint_name)
                        ik_request.ik_request.robot_state.joint_state.position.append(
                            arm_home[home_idx]
                        )
            else:
                # Use home positions as seed
                ik_request.ik_request.robot_state.joint_state.name = arm_joints
                ik_request.ik_request.robot_state.joint_state.position = arm_home
            
            # Set IK parameters
            ik_request.ik_request.avoid_collisions = False
            ik_request.ik_request.timeout.sec = 5
            ik_request.ik_request.timeout.nanosec = 0
            
            # Call IK service
            self.get_logger().info(f"Solving IK for pose: ({target_pose.position.x:.3f}, {target_pose.position.y:.3f}, {target_pose.position.z:.3f})")
            self.get_logger().info(f"Using planning group: {ik_planning_group}, end effector: {end_effector_link}")
            
            future = self.ik_client.call_async(ik_request)
            
            # Use a very short timeout to prevent blocking
            import threading
            result_container = [None]
            
            def ik_thread():
                # This runs in a separate thread to avoid blocking
                try:
                    # Give it a short time to complete
                    import time
                    start_time = time.time()
                    while not future.done() and (time.time() - start_time) < 3.0:
                        time.sleep(0.01)
                    
                    if future.done():
                        result_container[0] = future.result()
                    else:
                        result_container[0] = "TIMEOUT"
                except Exception as e:
                    self.get_logger().error(f"IK thread error: {str(e)}")
                    result_container[0] = "ERROR"
            
            # Start thread and wait briefly
            thread = threading.Thread(target=ik_thread)
            thread.start()
            thread.join(timeout=3.5)  # Wait max 3.5 seconds
            
            response = result_container[0]
            
            if response == "TIMEOUT":
                self.get_logger().error("IK service call timed out")
                return None
            elif response == "ERROR":
                self.get_logger().error("IK service call error")
                return None
            elif response is None:
                self.get_logger().error("IK service call failed")
                return None
            
            if response.error_code.val == response.error_code.SUCCESS:
                # Extract joint positions for the specific arm from full solution
                arm_joint_positions = []
                for joint_name in arm_joints:
                    try:
                        joint_index = response.solution.joint_state.name.index(joint_name)
                        arm_joint_positions.append(response.solution.joint_state.position[joint_index])
                    except ValueError:
                        self.get_logger().error(f"Joint {joint_name} not found in IK solution")
                        return None
                
                # Create full dual_arm joint state
                full_joint_positions = []
                
                if end_effector_link == self.left_end_effector:
                    # Moving left arm, keep right arm at current position
                    for joint_name in self.right_arm_joints:
                        if self.current_joint_state and joint_name in self.current_joint_state.name:
                            idx = self.current_joint_state.name.index(joint_name)
                            full_joint_positions.append(self.current_joint_state.position[idx])
                        else:
                            home_idx = self.right_arm_joints.index(joint_name)
                            full_joint_positions.append(self.right_home_joints[home_idx])
                    
                    # Add left arm solution
                    full_joint_positions.extend(arm_joint_positions)
                else:
                    # Moving right arm
                    full_joint_positions.extend(arm_joint_positions)
                    
                    # Keep left arm at current position
                    for joint_name in self.left_arm_joints:
                        if self.current_joint_state and joint_name in self.current_joint_state.name:
                            idx = self.current_joint_state.name.index(joint_name)
                            full_joint_positions.append(self.current_joint_state.position[idx])
                        else:
                            home_idx = self.left_arm_joints.index(joint_name)
                            full_joint_positions.append(self.left_home_joints[home_idx])
                
                self.get_logger().info(f"IK solution found for {ik_planning_group}")
                return full_joint_positions
            else:
                self.get_logger().error(f"IK failed with error code: {response.error_code.val}")
                return None
                
        except Exception as e:
            self.get_logger().error(f"Error in solve_ik_for_pose: {str(e)}")
            return None

    def move_to_joint_state_async(self, joint_positions, arm_type, operation):
        """Move to specific joint positions using MoveGroup action asynchronously"""
        try:
            # Create motion plan request for joint space
            goal_msg = MoveGroup.Goal()
            goal_msg.request = MotionPlanRequest()
            goal_msg.request.group_name = self.planning_group
            goal_msg.request.num_planning_attempts = 10
            goal_msg.request.allowed_planning_time = 10.0
            goal_msg.request.max_velocity_scaling_factor = 0.1
            goal_msg.request.max_acceleration_scaling_factor = 0.1
            
            # Set workspace parameters
            goal_msg.request.workspace_parameters = WorkspaceParameters()
            goal_msg.request.workspace_parameters.header.frame_id = self.base_frame
            goal_msg.request.workspace_parameters.min_corner.x = -1.0
            goal_msg.request.workspace_parameters.min_corner.y = -1.0
            goal_msg.request.workspace_parameters.min_corner.z = 0.0
            goal_msg.request.workspace_parameters.max_corner.x = 1.0
            goal_msg.request.workspace_parameters.max_corner.y = 1.0
            goal_msg.request.workspace_parameters.max_corner.z = 2.0
            
            # Create joint constraints for all joints in dual_arm
            constraints = Constraints()
            for i, (joint_name, position) in enumerate(zip(self.all_joints, joint_positions)):
                joint_constraint = JointConstraint()
                joint_constraint.joint_name = joint_name
                joint_constraint.position = float(position)
                joint_constraint.tolerance_above = 0.01
                joint_constraint.tolerance_below = 0.01
                joint_constraint.weight = 1.0
                constraints.joint_constraints.append(joint_constraint)
            
            goal_msg.request.goal_constraints.append(constraints)
            
            # Set planning options
            goal_msg.planning_options = PlanningOptions()
            goal_msg.planning_options.plan_only = False
            goal_msg.planning_options.look_around = False
            goal_msg.planning_options.look_around_attempts = 0
            goal_msg.planning_options.max_safe_execution_cost = 0.0
            goal_msg.planning_options.replan = False
            goal_msg.planning_options.replan_attempts = 0
            goal_msg.planning_options.replan_delay = 0.0
            
            # Send goal asynchronously
            self.get_logger().info(f"Sending dual_arm goal to /move_action...")
            send_goal_future = self.move_group_client.send_goal_async(goal_msg)
            
            # Add callback for when goal is accepted/rejected
            send_goal_future.add_done_callback(
                lambda future: self.on_goal_sent(future, arm_type, operation)
            )
                
        except Exception as e:
            self.get_logger().error(f"Error in move_to_joint_state_async: {str(e)}")
            self.on_operation_complete(False, arm_type, operation)

    def on_goal_sent(self, future, arm_type, operation):
        """Called when goal send is complete"""
        try:
            goal_handle = future.result()
            if not goal_handle.accepted:
                self.get_logger().error("Joint goal was rejected by MoveGroup")
                self.on_operation_complete(False, arm_type, operation)
                return
            
            self.get_logger().info("Goal accepted, waiting for execution...")
            
            # Wait for result asynchronously
            get_result_future = goal_handle.get_result_async()
            get_result_future.add_done_callback(
                lambda future: self.on_goal_complete(future, arm_type, operation)
            )
            
        except Exception as e:
            self.get_logger().error(f"Error in goal sent callback: {str(e)}")
            self.on_operation_complete(False, arm_type, operation)

    def on_goal_complete(self, future, arm_type, operation):
        """Called when goal execution is complete"""
        try:
            result = future.result()
            if result.status == 4:  # SUCCEEDED
                self.get_logger().info("Move completed successfully")
                self.on_operation_complete(True, arm_type, operation)
            else:
                self.get_logger().error(f"Move failed with status: {result.status}")
                self.on_operation_complete(False, arm_type, operation)
                
        except Exception as e:
            self.get_logger().error(f"Error in goal complete callback: {str(e)}")
            self.on_operation_complete(False, arm_type, operation)

    def on_operation_complete(self, success, arm_type, operation):
        """Called when any operation is complete"""
        try:
            if operation == "PICK":
                if success:
                    self.get_logger().info("Reached pick position, gripping object...")
                    self.publish_status("Gripping object...")
                    
                    # Use timer for gripper simulation
                    self.create_timer(1.5, lambda: self.on_grip_complete(arm_type), clock=None)
                else:
                    self.publish_status("Failed to reach pick position")
                    self.get_logger().error("❌ PICK FAILED - could not reach position")
                    self.is_busy = False
                    self.current_operation = None
                    
            elif operation == "PLACE":
                if success:
                    self.get_logger().info("Reached place position, releasing object...")
                    self.publish_status("Releasing object...")
                    
                    # Use timer for gripper simulation
                    self.create_timer(1.5, lambda: self.on_release_complete(arm_type), clock=None)
                else:
                    self.publish_status("Failed to reach place position")
                    self.get_logger().error("❌ PLACE FAILED - could not reach position")
                    self.is_busy = False
                    self.current_operation = None
                    
            elif operation == "HOME":
                if success:
                    self.last_pick_pose = None
                    self.last_arm_used = None
                    self.publish_status("HOME completed successfully")
                    self.get_logger().info("✅ HOME SUCCESSFUL")
                else:
                    self.publish_status("HOME failed")
                    self.get_logger().error("❌ HOME FAILED")
                
                self.is_busy = False
                self.current_operation = None
                
        except Exception as e:
            self.get_logger().error(f"Error in operation complete: {str(e)}")
            self.is_busy = False
            self.current_operation = None

    def on_grip_complete(self, arm_type):
        """Called when grip simulation is complete"""
        # Store for place command
        if hasattr(self, '_temp_target_pose'):
            self.last_pick_pose = self._temp_target_pose
        self.last_arm_used = arm_type
        
        self.publish_status(f"PICK completed successfully with {arm_type} arm")
        self.get_logger().info(f"✅ PICK SUCCESSFUL with {arm_type} arm")
        self.is_busy = False
        self.current_operation = None

    def on_release_complete(self, arm_type):
        """Called when release simulation is complete"""
        self.publish_status(f"PLACE completed successfully with {arm_type} arm")
        self.get_logger().info(f"✅ PLACE SUCCESSFUL with {arm_type} arm")
        self.is_busy = False
        self.current_operation = None

    def publish_status(self, message):
        """Publish status message"""
        msg = String()
        msg.data = message
        self.status_publisher.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    
    try:
        node = SeparatePickPlaceNode()
        
        # Use MultiThreadedExecutor for action clients
        executor = MultiThreadedExecutor()
        executor.add_node(node)
        
        try:
            executor.spin()
        finally:
            executor.shutdown()
            node.destroy_node()
            
    except KeyboardInterrupt:
        pass
    except Exception as e:
        print(f"Error: {e}")
    finally:
        rclpy.shutdown()


if __name__ == '__main__':
    main()