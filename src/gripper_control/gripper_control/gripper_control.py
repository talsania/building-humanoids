# gripper_control.py

from dynamixel_sdk import *
import time

class GripperController:
    def __init__(self, device_name='/dev/ttyUSB0', dxl_id=31, baudrate=4000000):
        self.dxl_id = dxl_id
        self.portHandler = PortHandler(device_name)
        self.packetHandler = PacketHandler(2.0)

        if not self.portHandler.openPort():
            raise RuntimeError("Failed to open port")

        if not self.portHandler.setBaudRate(baudrate):
            raise RuntimeError("Failed to set baudrate")

        # Enable torque
        self.packetHandler.write1ByteTxRx(self.portHandler, dxl_id, 64, 1)

    def move_to_position(self, position):
        self.packetHandler.write4ByteTxRx(self.portHandler, self.dxl_id, 116, position)

    def open_gripper(self):
        self.move_to_position(0)  # Fully open

    def close_gripper(self):
        self.move_to_position(4095)  # Fully closed

    def __del__(self):
        try:
            self.packetHandler.write1ByteTxRx(self.portHandler, self.dxl_id, 64, 0)
            self.portHandler.closePort()
        except:
            pass
