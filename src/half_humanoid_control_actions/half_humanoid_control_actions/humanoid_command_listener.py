import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from rclpy.action import ActionClient
from moveit_msgs.action import MoveGroup
from moveit_msgs.msg import MotionPlanRequest, Constraints, JointConstraint
from builtin_interfaces.msg import Duration
import numpy as np
import time

def d_to_r(degrees):
  """Converts an angle from degrees to radians using the numpy library."""
  return np.radians(degrees)

class HumanoidCommandListener(Node):
    def __init__(self):
        super().__init__('humanoid_command_listener')

        self._action_client = ActionClient(self, MoveGroup, 'move_action')
        self.subscription = self.create_subscription(
            String,
            'humanoid_command',
            self.command_callback,
            10
        )

        self.get_logger().info("Listening to 'humanoid_command' topic.")

    def command_callback(self, msg):
        command = msg.data.strip().lower()
        def_pose = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
        if command == "hi":
            # self.send_goal(joint_names=['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17', 'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27',],
            #                joint_positions=[1.5708, 0.0, 0.0, 1.309, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
                # Initial raised hand pose
            hi_pose = [1.5708, 0.0, 0.0, 1.309, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
            joint_names=['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17', 'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27']

            self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= hi_pose)
            time.sleep(1.5)
            self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= def_pose)

        elif command == "handshake":
            # self.send_goal(joint_names=['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17', 'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27',],
            #                joint_positions=[0.7854, 0.0, 0.0, 0.7854, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
                           
            handshake_pose = [0.7854, 0.0, 0.0, 0.7854, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]  
            joint_names = ['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17', 'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27']
            self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= handshake_pose)
            time.sleep(1.5)
            self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= def_pose)
            
        elif command == "cross_arms":
            # self.send_goal(joint_names=['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17', 'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27',],
            #                joint_positions=[d_to_r(17),d_to_r(6), d_to_r(90), d_to_r(62), d_to_r(4), d_to_r(2), d_to_r(0), d_to_r(-27), d_to_r(-6), d_to_r(-80), d_to_r(63), d_to_r(0), d_to_r(0), d_to_r(0)])  
           
            cross_pose = [d_to_r(17),d_to_r(6), d_to_r(90), d_to_r(62), d_to_r(4), d_to_r(2), d_to_r(0), d_to_r(-27), d_to_r(-6), d_to_r(-80), d_to_r(63), d_to_r(0), d_to_r(0), d_to_r(0)]  
            joint_names = ['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17', 'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27']
            self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= cross_pose)
            time.sleep(1.5)
            self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= def_pose)

        elif command == "wave_right":
            # Initial raised hand pose
            wave_pose = [1.5708, 0.0, 0.0, 1.309, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
            wave1 = wave_pose.copy()
            wave2 = wave_pose.copy()

            # Slight variations in elbow or wrist joint
            wave1[6] = d_to_r(10)  # j15
            wave2[6] = d_to_r(-10)

            joint_names=['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17', 'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27']

            self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= wave_pose)
            time.sleep(1.5)

            for _ in range(3):
                self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= wave1)
                time.sleep(2.0)
                self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= wave2)
                time.sleep(2.0)

            self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= def_pose) 

        elif command == "wave_left":
            # Initial raised hand pose
            wave_pose = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, d_to_r(-90), 0.0, 0.0, d_to_r(75), 0.0, 0.0, 0.0]
            wave1 = wave_pose.copy()
            wave2 = wave_pose.copy()

            # Slight variations in elbow or wrist joint
            wave1[13] = d_to_r(10)  
            wave2[13] = d_to_r(-10)

            joint_names=['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17', 'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27']

            self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= wave_pose)
            time.sleep(1.5)

            for _ in range(3):
                self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= wave1)
                time.sleep(2.0)
                self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= wave2)
                time.sleep(2.0)

            self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= def_pose)

        elif command == "bro":
            # Initial raised hand pose
            bro_pose = [d_to_r(90), 0.0, d_to_r(80), d_to_r(70), d_to_r(90), 0.0, 0.0, d_to_r(0), 0.0, 0.0, d_to_r(0), 0.0, 0.0, 0.0]
            bro1 = bro_pose.copy()
            bro2 = bro_pose.copy()

            # Slight variations in elbow or wrist joint
            bro1[3] = d_to_r(65)  # j15
            bro2[3] = d_to_r(75)

            joint_names=['j11', 'j12', 'j13', 'j14', 'j15', 'j16', 'j17', 'j21', 'j22', 'j23', 'j24', 'j25', 'j26', 'j27']

            self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= bro_pose)
            time.sleep(1.5)

            for _ in range(3):
                self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= bro1)
                time.sleep(2.0)
                self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= bro2)
                time.sleep(2.0)

            self.send_goal(group_name='dual_arm', joint_names=joint_names, joint_positions= def_pose)  


        elif command == "nod_yes":
            joint_names = ['j31', 'j_32']
            def_head_pose = [0.0, 0.0]
            yes1 = def_head_pose.copy()
            yes2 = def_head_pose.copy()

            yes1[1] = d_to_r(20)
            yes2[1] = d_to_r(-20)

            self.send_goal(group_name='head', joint_names=joint_names, joint_positions=def_head_pose)

            for _ in range(3):
                self.send_goal(group_name='head', joint_names=joint_names, joint_positions=yes1)
                time.sleep(1.0)
                self.send_goal(group_name='head', joint_names=joint_names, joint_positions=yes2)
                time.sleep(1.0)
                
            self.send_goal(group_name='head', joint_names=joint_names, joint_positions=def_head_pose)

        elif command == "nod_no":
            joint_names = ['j31', 'j_32']
            def_head_pose = [0.0, 0.0]
            yes1 = def_head_pose.copy()
            yes2 = def_head_pose.copy()

            yes1[0] = d_to_r(20)
            yes2[0] = d_to_r(-20)

            self.send_goal(group_name='head', joint_names=joint_names, joint_positions=def_head_pose)

            for _ in range(3):
                self.send_goal(group_name='head', joint_names=joint_names, joint_positions=yes1)
                time.sleep(1.0)
                self.send_goal(group_name='head', joint_names=joint_names, joint_positions=yes2)
                time.sleep(1.0)
                
            self.send_goal(group_name='head', joint_names=joint_names, joint_positions=def_head_pose)

        
        else:
            self.get_logger().warn(f"Unknown command: {command}")

    def send_goal(self, group_name, joint_names, joint_positions):
        if not self._action_client.wait_for_server(timeout_sec=5.0):
            self.get_logger().error("MoveGroup action server not available!")
            return

        goal_msg = MoveGroup.Goal()
        goal_msg.request = MotionPlanRequest()
        goal_msg.request.group_name = group_name  # Use given group name

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

        self.get_logger().info(f"Sending goal to MoveGroup for group: {group_name}...")
        send_goal_future = self._action_client.send_goal_async(goal_msg)
        send_goal_future.add_done_callback(self.goal_response_callback)


    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error('Goal rejected by MoveGroup.')
            return
        self.get_logger().info('Goal accepted.')
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        result = future.result().result
        self.get_logger().info(f'Result: {result.error_code.val}')


def main(args=None):
    rclpy.init(args=args)
    node = HumanoidCommandListener()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
