#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from dynamixel_sdk import *
import time

# Constants
PROTOCOL_VERSION = 2.0
DEVICENAME = '/dev/ttyUSB1' # SECOND U2D2 FOR 2 ACTUATORS
BAUDRATE = 4000000

ADDR_TORQUE_ENABLE = 64
ADDR_GOAL_POSITION = 116
ADDR_PRESENT_POSITION = 132
ADDR_PROFILE_VELOCITY = 112

POSITION_OPEN = 2048    # 180 degrees
POSITION_CLOSE = 1024   # 90 degrees
SAFE_VELOCITY = 100

class DualGripperControlNode(Node):
    def __init__(self):
        super().__init__('dual_gripper_control_node')

        self.portHandler = PortHandler(DEVICENAME)
        self.packetHandler = PacketHandler(PROTOCOL_VERSION)

        if not self.portHandler.openPort():
            self.get_logger().error("❌ Failed to open port")
            return

        if not self.portHandler.setBaudRate(BAUDRATE):
            self.get_logger().error("❌ Failed to set baudrate")
            return

        self.get_logger().info("✅ Serial port opened and baudrate set")

        # Scan for motors and initialize only 38 & 48
        self.motor_map = {}
        self.virtual_goal_positions = {}

        self.get_logger().info("🔍 Scanning for motors...")
        for test_id in range(1, 61):  # up to ID 60
            model_number, comm_result, error = self.packetHandler.ping(self.portHandler, test_id)
            if comm_result == COMM_SUCCESS:
                if test_id == 48:
                    label = "left"
                elif test_id == 38:
                    label = "right"
                else:
                    continue  # ignore other devices

                self.motor_map[label] = test_id
                self.virtual_goal_positions[test_id] = None
                self.get_logger().info(f"✅ {label.upper()} gripper motor found with ID {test_id}, model {model_number}")

                result, error = self.packetHandler.write1ByteTxRx(
                    self.portHandler, test_id, ADDR_TORQUE_ENABLE, 1
                )
                if result == COMM_SUCCESS:
                    self.get_logger().info(f"✅ Torque enabled for {label} motor")
                else:
                    self.get_logger().error(f"❌ Failed to enable torque for {label} motor")

        self.create_subscription(String, '/left_gripper_command', self.left_callback, 10)
        self.create_subscription(String, '/right_gripper_command', self.right_callback, 10)
    
    def reconnect_serial_port(self):
        try:
            self.get_logger().info("🔁 Attempting to reopen serial port...")

            self.portHandler.closePort()
            time.sleep(0.5)

            if not self.portHandler.openPort():
                self.get_logger().error("❌ Re-open failed")
                return

            if not self.portHandler.setBaudRate(BAUDRATE):
                self.get_logger().error("❌ Re-set baudrate failed")
                return

            self.get_logger().info("✅ Serial port re-opened and baudrate re-set")

            # Re-enable torque for existing motors
            for label, motor_id in self.motor_map.items():
                result, error = self.packetHandler.write1ByteTxRx(
                    self.portHandler, motor_id, ADDR_TORQUE_ENABLE, 1
                )
                if result == COMM_SUCCESS:
                    self.get_logger().info(f"✅ Re-enabled torque for {label} motor")
                else:
                    self.get_logger().warn(f"⚠️ Failed to re-enable torque for {label}")
        except Exception as e:
            self.get_logger().error(f"❌ Serial recovery failed: {e}")

    def left_callback(self, msg):
        if "left" in self.motor_map:
            self.handle_gripper_command(self.motor_map["left"], msg.data, "left")

    def right_callback(self, msg):
        if "right" in self.motor_map:
            self.handle_gripper_command(self.motor_map["right"], msg.data, "right")

    def handle_gripper_command(self, motor_id, command, label):
        command = command.strip().lower()
        goal_pos = POSITION_OPEN if command == "open" else POSITION_CLOSE if command == "close" else None

        if goal_pos is None:
            self.get_logger().warn(f"⚠️ Invalid command for {label} gripper: {command}")
            return

        self.packetHandler.write4ByteTxRx(
            self.portHandler, motor_id, ADDR_PROFILE_VELOCITY, SAFE_VELOCITY
        )

        dxl_comm_result, dxl_error = self.packetHandler.write4ByteTxRx(
            self.portHandler, motor_id, ADDR_GOAL_POSITION, goal_pos)

        if dxl_comm_result != COMM_SUCCESS:
            self.get_logger().error(f"❌ [{label}] Write failed: {self.packetHandler.getTxRxResult(dxl_comm_result)}")
            return
        elif dxl_error != 0:
            self.get_logger().error(f"❌ [{label}] Error: {self.packetHandler.getRxPacketError(dxl_error)}")
            return

        self.get_logger().info(f"✅ [{label}] Gripper '{command}' command sent (goal={goal_pos})")

        timeout = 2.0
        stuck_threshold = 5
        unchanged_count = 0
        last_pos = -1
        start_time = time.time()

        while time.time() - start_time < timeout:
            # present_pos, comm_result, error = self.packetHandler.read4ByteTxRx(
            #     self.portHandler, motor_id, ADDR_PRESENT_POSITION
            # )
            try:
                present_pos, comm_result, error = self.packetHandler.read4ByteTxRx(
                    self.portHandler, motor_id, ADDR_PRESENT_POSITION
                )
            except Exception as e:
                self.get_logger().warn(f"[{label}] Serial exception occurred: {e}")
                self.reconnect_serial_port()
                return

            if comm_result != COMM_SUCCESS:
                self.get_logger().warn(f"[{label}] Read error: {self.packetHandler.getTxRxResult(comm_result)}")
                break

            if error & 0x01:
                self.get_logger().error(f"❌ [{label}] Hardware error! Resetting torque.")
                self.packetHandler.write1ByteTxRx(self.portHandler, motor_id, ADDR_TORQUE_ENABLE, 0)
                time.sleep(0.2)
                self.packetHandler.write1ByteTxRx(self.portHandler, motor_id, ADDR_TORQUE_ENABLE, 1)
                break

            diff = abs(present_pos - goal_pos)
            self.get_logger().info(f"[{label}] Present={present_pos} Target={goal_pos} Δ={diff}")

            if diff <= 10:
                self.get_logger().info(f"[{label}] Reached target")
                self.virtual_goal_positions[motor_id] = goal_pos
                break

            if abs(present_pos - last_pos) < 3:
                unchanged_count += 1
                if unchanged_count >= stuck_threshold:
                    self.get_logger().warn(f"⚠️ [{label}] Motor stalled at {present_pos}. Treating as goal.")
                    self.packetHandler.write4ByteTxRx(
                        self.portHandler, motor_id, ADDR_GOAL_POSITION, present_pos
                    )
                    self.virtual_goal_positions[motor_id] = present_pos
                    break
            else:
                unchanged_count = 0

            last_pos = present_pos
            time.sleep(0.1)

        final_pos = self.virtual_goal_positions.get(motor_id, goal_pos)
        self.get_logger().info(f"📌 [{label}] Stored final goal: {final_pos}")

def main(args=None):
    rclpy.init(args=args)
    node = DualGripperControlNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
