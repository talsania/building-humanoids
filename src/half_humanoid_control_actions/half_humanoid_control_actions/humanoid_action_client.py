#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from moveit_msgs.action import MoveGroup
from moveit_msgs.msg import MotionPlanRequest, Constraints, JointConstraint

class HumanoidActionClient(Node):
    def __init__(self):
        super().__init__('humanoid_action_client')
        self.client = ActionClient(self, MoveGroup, 'move_action')
        self.client.wait_for_server()
        self.get_logger().info('Connected to MoveGroup action server.')

        self.send_goal()

    def send_goal(self):
        goal = MoveGroup.Goal()
        goal.request = MotionPlanRequest()
        goal.request.group_name = 'dual_arm' 

        constraints = Constraints()

        joints = {
            'j11': 1.5708,  
            'j14': 1.309
        }

        for name, position in joints.items():
            jc = JointConstraint()
            jc.joint_name = name
            jc.position = position
            jc.weight = 1.0
            constraints.joint_constraints.append(jc)

        goal.request.goal_constraints.append(constraints)

        self.future = self.client.send_goal_async(goal, feedback_callback=self.feedback_cb)
        self.future.add_done_callback(self.goal_response_cb)

    def feedback_cb(self, feedback_msg):
        self.get_logger().info("Feedback received.")

    def goal_response_cb(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error('Goal rejected.')
            return
        self.get_logger().info('Goal accepted.')
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self.result_cb)

    def result_cb(self, future):
        result = future.result().result
        self.get_logger().info(f'Result: error code {result.error_code.val}')

def main(args=None):
    rclpy.init(args=args)
    node = HumanoidActionClient()
    rclpy.spin(node)
    rclpy.shutdown()
