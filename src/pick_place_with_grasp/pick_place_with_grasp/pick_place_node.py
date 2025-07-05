#!/usr/bin/env python3

import rclpy
import scipy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray
from sensor_msgs.msg import JointState
import numpy as np
from scipy.spatial.transform import Rotation
import xml.etree.ElementTree as ET
import os
from scipy.optimize import minimize
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from std_msgs.msg import Float64MultiArray
from rclpy.action import ActionClient
from moveit_msgs.action import MoveGroup
from moveit_msgs.msg import MotionPlanRequest, Constraints, JointConstraint
from builtin_interfaces.msg import Duration
import numpy as np
import time
# from gripper_control.gripper_control import GripperController

class DualArmIKSolver(Node):
    def __init__(self):
        super().__init__('pick_place_node')

        self.left_gripper_pub = self.create_publisher(String, '/left_gripper_command', 10)
        self.right_gripper_pub = self.create_publisher(String, '/right_gripper_command', 10)


        # ——— Pre-grasp offset and storage ———
        self.pre_grasp_distance = 0.25  # meters
        self._stored_grasp_transform = None
        self._pre_grasp_timer = None

        # ——— Post-place offset and storage ———
        self.post_place_distance = 0.1  # meters  
        self._stored_place_transform = None
        self._post_place_timer = None

        # ——— Sequence tracking ———
        self.pick_sequence_step = 0  # 0: idle, 1: pre-pick, 2: pick, 3: pre-pick-return
        self.place_sequence_step = 0  # 0: idle, 1: post-place-approach, 2: place, 3: post-place-return

        self.joint_values = []
        self.new_ik_solution = False  # Flag to track new IK solutions

        self._action_client = ActionClient(self, MoveGroup, 'move_action')

        # Camera frame transformation matrix (camera -> base_link)
        self.T_camera_to_base_link = np.array([
            [-0.01694981,  -0.56415425,   0.82549542,   0.11293099],
            [-0.99984696,   0.00598689,  -0.01643823,  -0.00151968],
            [ 0.00433155,  -0.82564771,  -0.56416939,   0.41848761],
            [ 0.00000000,   0.00000000,   0.00000000,   1.00000000]
        ])

        # Pick default joint positions (Ideal position)
        self.pick_default_positions = [
            0.0,  # j11
            0.0,     # j12
            0.0,     # j13
            0.0,  # j14
            0.0,     # j15
            0.0,     # j16
            0.0,     # j17
            0.0, # j21
            0.0,     # j22
            0.0,     # j23
            0.0,  # j24
            0.0,     # j25
            0.0,     # j26
            0.0      # j27
        ]

        # Flag to track if we need to return to pick_default after a place command
        self.should_return_to_default = False
        self.last_action_type = ""  # Track what type of action was last executed
        self.place_action_completed = False  # New flag to track place completion

        # Publishers for transformed matrices (base_link frame)
        self.pick_transform_publisher = self.create_publisher(Float64MultiArray, '/pick_transform', 10)
        self.place_transform_publisher = self.create_publisher(Float64MultiArray, '/place_transform', 10)

        # Subscribers for camera frame transformation matrices
        self.pick_camera_subscriber = self.create_subscription(
            Float64MultiArray, '/pick_camera_tf', self.pick_camera_callback, 10)
        self.place_camera_subscriber = self.create_subscription(
            Float64MultiArray, '/place_camera_tf', self.place_camera_callback, 10)
        
        # Subscribers for transformation matrices
        self.pick_subscriber = self.create_subscription(
            Float64MultiArray, '/pick_transform', self.pick_callback, 10)
        self.place_subscriber = self.create_subscription(
            Float64MultiArray, '/place_transform', self.place_callback, 10)
        
        # Subscribe to joint states to get current positions
        self.joint_state_subscriber = self.create_subscription(
            JointState, '/joint_states', self.joint_state_callback, 10)
        
        # Send the joint values to MoveIt:
        self.joint_values_publisher = self.create_publisher(Float64MultiArray,'joint_values',10)

        # Current joint states
        self.current_joint_states = {}
        self.joint_names = ['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17',  # right arm
                           'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27',  # left arm
                           'j31', 'j32']  # neck joints needed for camera transform
        
        # Initialize current positions to zero
        for joint in self.joint_names:
            self.current_joint_states[joint] = 0.0
        
        # Load separate URDF models and parse them
        self.setup_urdf_models()
        
        # Test forward kinematics with zero angles
        self.test_forward_kinematics()
        
        self.get_logger().info("=== PICK-PLACE NODE INITIALIZED ===")
        self.get_logger().info("Pick Sequence: Ideal → Pre-pick → Pick → Pre-pick")
        self.get_logger().info("Place Sequence: Post-place → Place → Post-place → Ideal")

    def open_gripper(self, arm_type):
        msg = String()
        msg.data = 'open'
        if arm_type == 'left':
            self.left_gripper_pub.publish(msg)
            self.get_logger().info("Opened left gripper")
        else:
            self.right_gripper_pub.publish(msg)
            self.get_logger().info("Opened right gripper")

    def close_gripper(self, arm_type):
        msg = String()
        msg.data = 'close'
        if arm_type == 'left':
            self.left_gripper_pub.publish(msg)
            self.get_logger().info("Closed left gripper")
        else:
            self.right_gripper_pub.publish(msg)
            self.get_logger().info("Closed right gripper")

    def pick_camera_callback(self, msg):
        """Handle camera frame pick transform requests and convert to base_link"""
        if len(msg.data) != 16:
            self.get_logger().error("Camera transform matrix must have 16 elements (4x4)")
            return
        
        # Reshape incoming camera frame transform
        T_camera = np.array(msg.data).reshape(4, 4)
        
        # Transform the complete pose from camera frame to base_link frame
        T_base_link = self.T_camera_to_base_link @ T_camera
        
        # Publish to base_link frame topic
        base_msg = Float64MultiArray()
        base_msg.data = T_base_link.flatten().tolist()
        self.pick_transform_publisher.publish(base_msg)

    def place_camera_callback(self, msg):
        """Handle camera frame place transform requests and convert to base_link"""
        if len(msg.data) != 16:
            self.get_logger().error("Camera transform matrix must have 16 elements (4x4)")
            return
        
        # Reshape incoming camera frame transform
        T_camera = np.array(msg.data).reshape(4, 4)
        
        # Transform the complete pose from camera frame to base_link frame
        T_base_link = self.T_camera_to_base_link @ T_camera
        
        # Publish to base_link frame topic
        base_msg = Float64MultiArray()
        base_msg.data = T_base_link.flatten().tolist()
        self.place_transform_publisher.publish(base_msg)

    def setup_urdf_models(self):
        """Load and parse separate URDF files for left and right arms"""
        try:
            # Load left arm URDF
            left_urdf_path = os.path.expanduser("~/humanoid_ws/src/myrobot_description/urdf/left_arm_URDF.urdf")
            with open(left_urdf_path, 'r') as f:
                self.left_urdf_content = f.read()
            
            # Load right arm URDF  
            right_urdf_path = os.path.expanduser("~/humanoid_ws/src/myrobot_description/urdf/right_arm_URDF.urdf")
            with open(right_urdf_path, 'r') as f:
                self.right_urdf_content = f.read()
            
            # Parse URDF to extract joint and link information
            self.left_arm_model = self.parse_urdf(self.left_urdf_content)
            self.right_arm_model = self.parse_urdf(self.right_urdf_content)
            
        except Exception as e:
            self.get_logger().error(f"Error loading URDF files: {str(e)}")
    
    def test_forward_kinematics(self):
        """Test forward kinematics with zero joint angles"""
        try:
            zero_angles = [0.0] * 7
            
            # Test left arm
            left_fk = self.forward_kinematics(zero_angles, self.left_arm_model, 'left')
            
            # Test right arm  
            right_fk = self.forward_kinematics(zero_angles, self.right_arm_model, 'right')
            
            # Debug: Test if IK can solve for the zero position
            success, solution = self.solve_ik_from_urdf(left_fk, 'left')
            if success:
                # Verify the solution
                verify_fk = self.forward_kinematics(list(solution.values()), self.left_arm_model, 'left')
                error = np.linalg.norm(verify_fk[:3, 3] - left_fk[:3, 3])
            else:
                self.get_logger().error("✗ IK failed for zero position - FK model needs fixing")
            
        except Exception as e:
            self.get_logger().error(f"Error testing FK: {str(e)}")
    
    def parse_urdf(self, urdf_content):
        """Parse URDF content and extract joint/link information"""
        root = ET.fromstring(urdf_content)
        
        joints = {}
        links = {}
        
        # Parse joints
        for joint in root.findall('joint'):
            joint_name = joint.get('name')
            joint_type = joint.get('type')
            
            # Get parent and child links
            parent = joint.find('parent').get('link') if joint.find('parent') is not None else None
            child = joint.find('child').get('link') if joint.find('child') is not None else None
            
            # Get origin (xyz and rpy)
            origin = joint.find('origin')
            xyz = [0, 0, 0]
            rpy = [0, 0, 0]
            if origin is not None:
                if origin.get('xyz'):
                    xyz = [float(x) for x in origin.get('xyz').split()]
                if origin.get('rpy'):
                    rpy = [float(x) for x in origin.get('rpy').split()]
            
            # Get axis
            axis = joint.find('axis')
            axis_xyz = [0, 0, 1]  # default
            if axis is not None and axis.get('xyz'):
                axis_xyz = [float(x) for x in axis.get('xyz').split()]
            
            # Get limits
            limit = joint.find('limit')
            joint_limits = None
            if limit is not None:
                joint_limits = {
                    'lower': float(limit.get('lower', '-3.14')),
                    'upper': float(limit.get('upper', '3.14'))
                }
            
            joints[joint_name] = {
                'type': joint_type,
                'parent': parent,
                'child': child,
                'origin_xyz': xyz,
                'origin_rpy': rpy,
                'axis': axis_xyz,
                'limits': joint_limits
            }
        
        return {'joints': joints, 'links': links}
    
    def joint_state_callback(self, msg):
        """Update current joint states"""
        for i, name in enumerate(msg.name):
            if name in self.joint_names:
                self.current_joint_states[name] = msg.position[i]
        
        # Send to MoveIt only if we have a new IK solution
        if self.new_ik_solution and self.joint_values:
            joint_names=['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17', 'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27']
            
            self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions=self.joint_values)
            
            # Reset the flag and clear joint values to prevent continuous sending
            self.new_ik_solution = False
            self.joint_values = []
    
    def create_transformation_matrix(self, xyz, rpy):
        """Create 4x4 transformation matrix from xyz and rpy"""
        # Create rotation matrix from roll, pitch, yaw
        rotation = Rotation.from_euler('xyz', rpy)
        rot_matrix = rotation.as_matrix()
        
        # Create 4x4 transformation matrix
        T = np.eye(4)
        T[:3, :3] = rot_matrix
        T[:3, 3] = xyz
        
        return T
    
    def get_camera_to_base_transform(self):
        """Calculate transformation from camera frame to base_link frame using current neck joint states"""
        # Get current joint states for neck joints (use zero if not available)
        j31_angle = self.current_joint_states.get('j31', 0.0)  # neck yaw
        j32_angle = self.current_joint_states.get('j32', 0.0)  # neck pitch
        
        # Step 1: base_link to neck_yaw origin
        T1 = self.create_transformation_matrix([0.00875, 0, 0.1486], [1.5708, 0, 1.5708])
        
        # Step 2: neck_yaw to neck_pitch origin
        T2 = self.create_transformation_matrix([0, 0.030398, 0], [-1.5708, 0, 1.5708])
        
        # Step 3: neck_pitch to camera origin
        T3 = self.create_transformation_matrix([0.23949, -0.10418, 0.0015188], [-0.34907, -1.5533, 1.3204])
        
        # Apply joint rotations
        R_j31 = np.eye(4)
        R_j31[:3, :3] = Rotation.from_rotvec(j31_angle * np.array([0, 1, 0])).as_matrix()
        
        R_j32 = np.eye(4) 
        R_j32[:3, :3] = Rotation.from_rotvec(j32_angle * np.array([0, 0, 1])).as_matrix()
        
        # Build transformation chain
        T_base_to_camera = T1 @ R_j31 @ T2 @ R_j32 @ T3
        
        # Get camera to base transformation
        T_camera_to_base = np.linalg.inv(T_base_to_camera)
        
        return T_camera_to_base
    
    def transform_camera_to_base(self, camera_transform):
        """Transform a pose from camera frame to base_link frame"""
        T_camera_to_base = self.get_camera_to_base_transform()
        
        # Apply transformation: T_base = T_camera_to_base * T_camera
        base_transform = T_camera_to_base @ camera_transform
        
        return base_transform
    
    def forward_kinematics(self, joint_angles, arm_model, arm_type):
        """Calculate forward kinematics using URDF model"""
        # Get joint names in order for the specific arm
        if arm_type == 'left':
            joint_order = ['j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27']
        else:  # right
            joint_order = ['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17']
        
        # Start with identity matrix (base_link frame)
        T_total = np.eye(4)
        
        # Apply transformations for each joint in the kinematic chain
        for i, joint_name in enumerate(joint_order):
            if joint_name in arm_model['joints']:
                joint_info = arm_model['joints'][joint_name]
                
                # Get joint angle
                if i < len(joint_angles):
                    joint_angle = joint_angles[i]
                else:
                    joint_angle = 0.0
                
                # Create transformation matrix for this joint's origin
                xyz = joint_info['origin_xyz']
                rpy = joint_info['origin_rpy']
                
                # Base transformation from URDF origin
                T_joint_origin = self.create_transformation_matrix(xyz, rpy)
                
                # Apply the origin transformation first
                T_total = T_total @ T_joint_origin
                
                # Then apply joint rotation based on axis and angle
                if joint_info['type'] == 'revolute':
                    axis = joint_info['axis']
                    
                    # Create joint rotation matrix
                    joint_rot_matrix = np.eye(4)
                    
                    # Handle different axis orientations more carefully
                    axis_norm = np.linalg.norm(axis)
                    if axis_norm > 0:
                        axis = np.array(axis) / axis_norm
                        
                        # Use Rodriguez rotation formula for arbitrary axis
                        joint_rotation = Rotation.from_rotvec(joint_angle * axis)
                        joint_rot_matrix[:3, :3] = joint_rotation.as_matrix()
                        
                        T_total = T_total @ joint_rot_matrix
        
        return T_total
    
    def solve_ik_from_urdf(self, target_transform, arm_type):
        """Solve IK using the separate URDF models"""
        try:
            if arm_type == 'left':
                arm_model = self.left_arm_model
                joint_names = ['j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27']
                joint_limits = [
                    (-1.571, 1.571),   # j21
                    (-0.105, 1.22),    # j22
                    (-1.571, 1.571),   # j23
                    (-1.0472, 1.309),  # j24
                    (-1.57, 1.57),     # j25
                    (-0.52, 0.52),     # j26
                    (-1.571, 1.571)    # j27
                ]
            else:  # right
                arm_model = self.right_arm_model
                joint_names = ['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17']
                joint_limits = [
                    (-1.571, 1.571),   # j11
                    (-1.22, 0.105),    # j12  
                    (-1.571, 1.571),   # j13
                    (-1.0472, 1.309),  # j14
                    (-1.57, 1.57),     # j15
                    (-0.52, 0.52),     # j16
                    (-1.571, 1.571)    # j17
                ]
            
            # Get current joint positions as initial guess
            current_joints = []
            for joint_name in joint_names:
                current_joints.append(self.current_joint_states.get(joint_name, 0.0))
            
            # Define objective function for IK
            def objective(joint_angles):
                # Calculate forward kinematics
                current_transform = self.forward_kinematics(joint_angles, arm_model, arm_type)
                
                # Calculate position error
                pos_error = np.linalg.norm(current_transform[:3, 3] - target_transform[:3, 3])
                
                # Calculate orientation error using rotation matrices
                R_current = current_transform[:3, :3]
                R_target = target_transform[:3, :3]
                
                # Using trace-based rotation error (more stable)
                rot_error = 1.0 - (np.trace(R_current.T @ R_target) - 1.0) / 2.0
                rot_error = max(0.0, rot_error)  # Ensure non-negative
                
                total_error = pos_error + 0.5 * rot_error
                return total_error
            
            # Try multiple starting points for better convergence
            best_result = None
            best_error = float('inf')
            
            for attempt in range(3):
                if attempt == 0:
                    # Use current joint positions
                    initial_guess = current_joints.copy()
                elif attempt == 1:
                    # Try with small random perturbation
                    initial_guess = [pos + 0.1 * (np.random.random() - 0.5) for pos in current_joints]
                else:
                    # Try with larger random initialization
                    initial_guess = []
                    for lower, upper in joint_limits:
                        initial_guess.append(lower + (upper - lower) * np.random.random())
                
                # Ensure initial guess is within bounds
                for i, (lower, upper) in enumerate(joint_limits):
                    initial_guess[i] = max(lower, min(upper, initial_guess[i]))
                
                # Solve optimization
                result = minimize(
                    objective, 
                    initial_guess, 
                    bounds=joint_limits, 
                    method='L-BFGS-B',
                    options={'ftol': 1e-8, 'gtol': 1e-6, 'maxiter': 2000}
                )
                
                if result.fun < best_error:
                    best_result = result
                    best_error = result.fun
                
                # If we get a good solution, break early
                if result.fun < 0.01:
                    break
            
            if best_result is not None and best_error < 0.5:
                # Verify the solution
                final_transform = self.forward_kinematics(best_result.x, arm_model, arm_type)
                
                return True, dict(zip(joint_names, best_result.x))
            else:
                self.get_logger().warn(f"IK optimization failed for {arm_type} arm. Best error: {best_error:.6f}")
                return False, None
                
        except Exception as e:
            self.get_logger().error(f"Error in URDF-based IK solving: {str(e)}")
            return False, None
    
    def pick_callback(self, msg):
        """Handle pick transform requests - NEW SEQUENCE"""
        if len(msg.data) != 16:
            self.get_logger().error("Transform matrix must have 16 elements (4x4)")
            return
        
        # Reshape incoming transform
        camera_transform = np.array(msg.data).reshape(4, 4)
        
        # Transform from camera frame to base_link frame
        base_transform = self.transform_camera_to_base(camera_transform)
        
        # Store the actual grasp transform
        self._stored_grasp_transform = base_transform.copy()
        
        # Reset sequence tracking
        self.pick_sequence_step = 0
        
        self.get_logger().info("=== STARTING PICK SEQUENCE ===")
        self.get_logger().info("Step 1: Moving to Ideal Position")
        
        # Step 1: Go to Ideal Position first
        self.last_action_type = "pick_ideal_start"
        self.go_to_ideal_position()
    
    def place_callback(self, msg):
        """Handle place transform requests - NEW SEQUENCE"""
        if len(msg.data) != 16:
            self.get_logger().error("Transform matrix must have 16 elements (4x4)")
            return
        
        # Reshape incoming transform
        camera_transform = np.array(msg.data).reshape(4, 4)
        
        # Transform from camera frame to base_link frame
        base_transform = self.transform_camera_to_base(camera_transform)
        
        # Store the actual place transform
        self._stored_place_transform = base_transform.copy()
        
        # Reset sequence tracking
        self.place_sequence_step = 0
        
        self.get_logger().info("=== STARTING PLACE SEQUENCE ===")
        self.get_logger().info("Step 1: Moving to Post-Place Approach Position")
        
        # Step 1: Go to Post-Place approach position first
        self.last_action_type = "place_post_approach"
        self.place_sequence_step = 1
        self._execute_post_place_approach()
    
    def _execute_post_place_approach(self):
        """Execute post-place approach position"""
        if self._stored_place_transform is None:
            self.get_logger().error("No stored place transform!")
            return
        
        # Compute post-place approach position (10cm away)
        R = self._stored_place_transform[:3, :3]
        t = self._stored_place_transform[:3, 3]
        local_forward = np.array([0.0, -1.0, 0.0])
        approach_vec = R.dot(local_forward)
        t_post = t - self.post_place_distance * approach_vec
        T_post = self._stored_place_transform.copy()
        T_post[:3, 3] = t_post
        
        self.get_logger().info("Executing Post-Place Approach Position")
        self.process_transform_request(T_post, "place_post_approach")
    
    def process_transform_request(self, transform, action_type):
        """Process transform request and determine which arm to use"""
        # Determine which arm to use based on y coordinate IN BASE_LINK FRAME
        base_link_y = transform[1, 3]
        
        if base_link_y > 0:  # y > 0 in base_link frame
            arm_type = 'left'
        else:  # y <= 0 in base_link frame
            arm_type = 'right'
        
        # Solve IK using separate URDF
        success, solution = self.solve_ik_from_urdf(transform, arm_type)
        
        if success:
            self.create_joint_values_list(solution, arm_type)
        else:
            self.get_logger().error(f"Failed to find IK solution for {arm_type} arm")
    
    def create_joint_values_list(self, ik_solution, active_arm):
        """Create joint values list in fixed order: right arm joints followed by left arm joints"""
        try:
            # Fixed order: right arm joints first, then left arm joints
            joint_names_order = ['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17',  # right arm
                                'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27']  # left arm
            
            self.joint_values = []
            
            for joint_name in joint_names_order:
                if joint_name in ik_solution:
                    # Use IK solution for the active arm
                    self.joint_values.append(ik_solution[joint_name])
                else:
                    # Keep current position for the other arm
                    current_pos = self.current_joint_states.get(joint_name, 0.0)
                    self.joint_values.append(current_pos)
            
            # Set flag to indicate new IK solution is ready
            self.new_ik_solution = True
            
            return self.joint_values
            
        except Exception as e:
            self.get_logger().error(f"Error creating joint values list: {str(e)}")
            return None
    
    def go_to_ideal_position(self):
        """Move robot to ideal (pick_default) position"""
        joint_names = ['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17', 'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27']
        
        self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions=self.pick_default_positions)
    
    def send_goal(self, group_name, joint_names, joint_positions):
        if not self._action_client.wait_for_server(timeout_sec=5.0):
            self.get_logger().error("MoveGroup action server not available!")
            return

        goal_msg = MoveGroup.Goal()
        goal_msg.request = MotionPlanRequest()
        goal_msg.request.group_name = group_name

        constraint = Constraints()
        for name, pos in zip(joint_names, joint_positions):
            jc = JointConstraint()
            jc.joint_name = name
            jc.position = pos
            jc.tolerance_above = 0.01
            jc.tolerance_below = 0.01
            jc.weight = 1.0
            constraint.joint_constraints.append(jc)

        goal_msg.request.goal_constraints.append(constraint)
        goal_msg.planning_options.planning_scene_diff.is_diff = True
        goal_msg.planning_options.plan_only = False
        goal_msg.planning_options.look_around = False
        goal_msg.planning_options.replan = False

        send_goal_future = self._action_client.send_goal_async(goal_msg)
        send_goal_future.add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error('Goal rejected by MoveGroup.')
            return
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        result = future.result().result
        
        # PICK SEQUENCE HANDLING
        if self.last_action_type == "pick_ideal_start":
            if result.error_code.val == 1:
                self.get_logger().info("Step 2: Moving to Pre-Pick Position")
                self.last_action_type = "pick_pre_pick"
                self.pick_sequence_step = 1
                self._execute_pre_pick()
            else:
                self.get_logger().warn("Ideal position failed, attempting pre-pick anyway")
                self._execute_pre_pick()
            return
            
        elif self.last_action_type == "pick_pre_pick":
            if result.error_code.val == 1:
                self.get_logger().info("Step 3: Moving to Pick Position")
                self.last_action_type = "pick_actual"
                self.pick_sequence_step = 2
                self._pre_grasp_timer = self.create_timer(1.0, self._execute_actual_pick)
            else:
                self.get_logger().warn("Pre-pick failed, attempting pick anyway")
                self._execute_actual_pick()
            return
            
        elif self.last_action_type == "pick_actual":
            if result.error_code.val == 1:
                arm_type = 'left' if self._stored_grasp_transform[1, 3] > 0 else 'right'
                self.get_logger().info("Pick motion completed, closing gripper...")
                self.close_gripper(arm_type)

                self.get_logger().info("Step 4: Returning to Pre-Pick Position")
                self.last_action_type = "pick_pre_pick_return"
                self.pick_sequence_step = 3
                self._pre_grasp_timer = self.create_timer(1.0, self._execute_pre_pick_return)
            else:
                self.get_logger().warn("Pick failed, attempting pre-pick return anyway")
                self._execute_pre_pick_return()
            return

            
        elif self.last_action_type == "pick_pre_pick_return":
            if result.error_code.val == 1:
                self.get_logger().info("=== PICK SEQUENCE COMPLETED ===")
                self.get_logger().info("Robot ready for PLACE command")
                self.pick_sequence_step = 0  # Reset
            else:
                self.get_logger().warn("Pre-pick return failed")
            return

        # PLACE SEQUENCE HANDLING
        elif self.last_action_type == "place_post_approach":
            if result.error_code.val == 1:
                self.get_logger().info("Step 2: Moving to Place Position")
                self.last_action_type = "place_actual"
                self.place_sequence_step = 2
                self._post_place_timer = self.create_timer(1.0, self._execute_actual_place)
            else:
                self.get_logger().warn("Post-place approach failed, attempting place anyway")
                self._execute_actual_place()
            return
            
        elif self.last_action_type == "place_actual":
            if result.error_code.val == 1:
                arm_type = 'left' if self._stored_place_transform[1, 3] > 0 else 'right'
                self.get_logger().info("Place motion completed, opening gripper...")
                self.open_gripper(arm_type)

                self.get_logger().info("Step 3: Moving to Post-Place Position")
                self.last_action_type = "place_post_return"
                self.place_sequence_step = 3
                self._post_place_timer = self.create_timer(1.0, self._execute_post_place_return)
            else:
                self.get_logger().warn("Place failed, attempting post-place return anyway")
                self._execute_post_place_return()
            return
            
        elif self.last_action_type == "place_post_return":
            if result.error_code.val == 1:
                self.get_logger().info("Step 4: Returning to Ideal Position")
                self.last_action_type = "place_ideal_end"
                self.place_sequence_step = 0  # Reset
                self._post_place_timer = self.create_timer(1.0, self._execute_ideal_return)
            else:
                self.get_logger().warn("Post-place return failed, attempting ideal return anyway")
                self._execute_ideal_return()
            return
            
        elif self.last_action_type == "place_ideal_end":
            if result.error_code.val == 1:
                self.get_logger().info("=== PLACE SEQUENCE COMPLETED ===")
                self.get_logger().info("Robot returned to Ideal Position - Ready for new commands")
            else:
                self.get_logger().warn("Return to ideal position failed")
            return
    
    def _execute_pre_pick(self):
        """Execute pre-pick position"""
        if self._stored_grasp_transform is None:
            self.get_logger().error("No stored grasp transform!")
            return
        
        # Compute pre-pick position (10cm away)
        R = self._stored_grasp_transform[:3, :3]
        t = self._stored_grasp_transform[:3, 3]
        local_forward = np.array([0.0, -1.0, 0.0])
        approach_vec = R.dot(local_forward)
        t_pre = t - self.pre_grasp_distance * approach_vec
        T_pre = self._stored_grasp_transform.copy()
        T_pre[:3, 3] = t_pre
        
        self.process_transform_request(T_pre, "pick_pre_pick")
    
    def _execute_actual_pick(self):
        if self._pre_grasp_timer:
            self._pre_grasp_timer.cancel()
            self._pre_grasp_timer = None

        if self._stored_grasp_transform is None:
            self.get_logger().error("No stored grasp transform!")
            return

        # Determine arm to open correct gripper
        arm_type = 'left' if self._stored_grasp_transform[1, 3] > 0 else 'right'
        self.close_gripper(arm_type)

        self.process_transform_request(self._stored_grasp_transform, "pick_actual")

    def _execute_pre_pick_return(self):
        """Execute return to pre-pick position after picking"""
        if self._pre_grasp_timer:
            self._pre_grasp_timer.cancel()
            self._pre_grasp_timer = None

        if self._stored_grasp_transform is None:
            self.get_logger().error("No stored grasp transform!")
            return
        
        # Compute pre-pick position (same as before)
        R = self._stored_grasp_transform[:3, :3]
        t = self._stored_grasp_transform[:3, 3]
        local_forward = np.array([0.0, -1.0, 0.0])
        approach_vec = R.dot(local_forward)
        t_pre = t - self.pre_grasp_distance * approach_vec
        T_pre = self._stored_grasp_transform.copy()
        T_pre[:3, 3] = t_pre
        
        self.process_transform_request(T_pre, "pick_pre_pick_return")
    
    def _execute_actual_place(self):
        if self._post_place_timer:
            self._post_place_timer.cancel()
            self._post_place_timer = None

        if self._stored_place_transform is None:
            self.get_logger().error("No stored place transform!")
            return

        # Determine arm to close correct gripper
        arm_type = 'left' if self._stored_place_transform[1, 3] > 0 else 'right'
        self.open_gripper(arm_type)

        self.process_transform_request(self._stored_place_transform, "place_actual")

    def _execute_post_place_return(self):
        """Execute return to post-place position after placing"""
        if self._post_place_timer:
            self._post_place_timer.cancel()
            self._post_place_timer = None

        if self._stored_place_transform is None:
            self.get_logger().error("No stored place transform!")
            return
        
        # Compute post-place position (same as approach)
        R = self._stored_place_transform[:3, :3]
        t = self._stored_place_transform[:3, 3]
        local_forward = np.array([0.0, -1.0, 0.0])
        approach_vec = R.dot(local_forward)
        t_post = t - self.post_place_distance * approach_vec
        T_post = self._stored_place_transform.copy()
        T_post[:3, 3] = t_post
        
        self.process_transform_request(T_post, "place_post_return")
    
    def _execute_ideal_return(self):
        """Execute return to ideal position"""
        if self._post_place_timer:
            self._post_place_timer.cancel()
            self._post_place_timer = None
        
        self.get_logger().info("Returning to Ideal Position")
        self.go_to_ideal_position()

def main(args=None):
    rclpy.init(args=args)
    node = DualArmIKSolver()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()