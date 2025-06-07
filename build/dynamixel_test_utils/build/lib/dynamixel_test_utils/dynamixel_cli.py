#!/usr/bin/env python3
# Command-line interface for Dynamixel motors

import os
import sys
import time
from dynamixel_sdk import *

# Protocol version
PROTOCOL_VERSION = 2.0

# Default settings
BAUDRATE = 4000000
DEVICENAME = '/dev/ttyUSB0'  # Change this to match your port

# Control table addresses (may vary by model)
ADDR_TORQUE_ENABLE = 64
ADDR_GOAL_POSITION = 116
ADDR_PRESENT_POSITION = 132

class DynamixelCLI:
    def __init__(self):
        # Initialize SDK
        self.portHandler = PortHandler(DEVICENAME)
        self.packetHandler = PacketHandler(PROTOCOL_VERSION)
        self.is_connected = False
        
    def connect(self):
        # Open port
        if not self.portHandler.openPort():
            print("Failed to open the port")
            return False
        
        # Set port baudrate
        if not self.portHandler.setBaudRate(BAUDRATE):
            print("Failed to change baudrate")
            return False
        
        print(f"Connected to port {DEVICENAME} at {BAUDRATE} baud")
        self.is_connected = True
        return True
    
    def disconnect(self):
        if self.is_connected:
            self.portHandler.closePort()
            print("Disconnected from port")
            self.is_connected = False
    
    def scan(self):
        if not self.is_connected:
            if not self.connect():
                return
        
        print("Scanning for Dynamixel motors...")
        found_motors = []
        
        for motor_id in range(0, 253):
            model_number, comm_result, error = self.packetHandler.ping(self.portHandler, motor_id)
            if comm_result == COMM_SUCCESS:
                print(f"Found motor ID: {motor_id}, model number: {model_number}")
                found_motors.append(motor_id)
        
        print(f"Scan complete. Found {len(found_motors)} motors.")
        return found_motors
    
    def enable_torque(self, motor_id):
        if not self.is_connected:
            if not self.connect():
                return False
        
        comm_result, error = self.packetHandler.write1ByteTxRx(self.portHandler, motor_id, ADDR_TORQUE_ENABLE, 1)
        if comm_result != COMM_SUCCESS:
            print(f"Failed to enable torque on motor {motor_id}: {self.packetHandler.getTxRxResult(comm_result)}")
            return False
        
        print(f"Torque enabled on motor {motor_id}")
        return True
    
    def disable_torque(self, motor_id):
        if not self.is_connected:
            if not self.connect():
                return False
        
        comm_result, error = self.packetHandler.write1ByteTxRx(self.portHandler, motor_id, ADDR_TORQUE_ENABLE, 0)
        if comm_result != COMM_SUCCESS:
            print(f"Failed to disable torque on motor {motor_id}: {self.packetHandler.getTxRxResult(comm_result)}")
            return False
        
        print(f"Torque disabled on motor {motor_id}")
        return True
    
    def move_motor(self, motor_id, position):
        if not self.is_connected:
            if not self.connect():
                return False
        
        # Ensure position is within limits
        position = max(0, min(4095, position))
        
        comm_result, error = self.packetHandler.write4ByteTxRx(self.portHandler, motor_id, ADDR_GOAL_POSITION, position)
        if comm_result != COMM_SUCCESS:
            print(f"Failed to move motor {motor_id}: {self.packetHandler.getTxRxResult(comm_result)}")
            return False
        
        print(f"Motor {motor_id} moved to position {position}")
        return True
    
    def read_position(self, motor_id):
        if not self.is_connected:
            if not self.connect():
                return None
        
        position, comm_result, error = self.packetHandler.read4ByteTxRx(self.portHandler, motor_id, ADDR_PRESENT_POSITION)
        if comm_result != COMM_SUCCESS:
            print(f"Failed to read position from motor {motor_id}: {self.packetHandler.getTxRxResult(comm_result)}")
            return None
        
        print(f"Motor {motor_id} position: {position}")
        return position
    
    def run_cli(self):
        print("Dynamixel Motor CLI")
        print("------------------")
        print("Commands:")
        print("  scan                      - Scan for connected motors")
        print("  enable <id>               - Enable torque on motor")
        print("  disable <id>              - Disable torque on motor")
        print("  move <id> <position>      - Move motor to position (0-4095)")
        print("  read <id>                 - Read current position of motor")
        print("  monitor <id> [interval]   - Monitor position continuously")
        print("  quit                      - Exit the program")
        
        if not self.is_connected:
            self.connect()
        
        try:
            while True:
                cmd = input("\nEnter command: ").strip().split()
                if not cmd:
                    continue
                
                if cmd[0] == "quit":
                    break
                elif cmd[0] == "scan":
                    self.scan()
                elif cmd[0] == "enable" and len(cmd) > 1:
                    self.enable_torque(int(cmd[1]))
                elif cmd[0] == "disable" and len(cmd) > 1:
                    self.disable_torque(int(cmd[1]))
                elif cmd[0] == "move" and len(cmd) > 2:
                    self.move_motor(int(cmd[1]), int(cmd[2]))
                elif cmd[0] == "read" and len(cmd) > 1:
                    self.read_position(int(cmd[1]))
                elif cmd[0] == "monitor" and len(cmd) > 1:
                    interval = 0.5  # Default interval
                    if len(cmd) > 2:
                        interval = float(cmd[2])
                    
                    motor_id = int(cmd[1])
                    print(f"Monitoring motor {motor_id}. Press Ctrl+C to stop...")
                    try:
                        while True:
                            self.read_position(motor_id)
                            time.sleep(interval)
                    except KeyboardInterrupt:
                        print("\nStopped monitoring")
                else:
                    print("Invalid command or missing parameters")
        
        except KeyboardInterrupt:
            print("\nExiting...")
        finally:
            self.disconnect()

def main():
    cli = DynamixelCLI()
    cli.run_cli()

if __name__ == '__main__':
    main()
