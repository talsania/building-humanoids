#!/usr/bin/env python3

import os
from dynamixel_sdk import *

# Control table addresses for XM430-W350 (adjust if using different model)
ADDR_TORQUE_ENABLE = 64
ADDR_GOAL_POSITION = 116
ADDR_MOVING_SPEED = 112  # For older models
ADDR_PROFILE_VELOCITY = 112  # For newer X-series

# Protocol version
PROTOCOL_VERSION = 2.0

# Default settings
DEVICENAME = '/dev/ttyUSB0'  # Adjust for your system (Windows: 'COM1', etc.)
BAUDRATE = 4000000

# Servo parameters
TORQUE_ENABLE = 1
TORQUE_DISABLE = 0
TARGET_POSITION = 2048  # 180 degrees
MIN_SPEED = 50  # Minimal speed value (adjust as needed)

def main():
    # Servo IDs
    servo_ids = list(range(11, 18)) + list(range(21, 28)) + list(range(31,32))  # IDs 11-17 and 21-27
    
    # Initialize PortHandler and PacketHandler
    portHandler = PortHandler(DEVICENAME)
    packetHandler = PacketHandler(PROTOCOL_VERSION)
    
    # Open port
    if not portHandler.openPort():
        print("Failed to open the port")
        return
    print(f"Succeeded to open the port: {DEVICENAME}")
    
    # Set port baudrate
    if not portHandler.setBaudRate(BAUDRATE):
        print("Failed to change the baudrate")
        return
    print(f"Succeeded to change the baudrate to: {BAUDRATE}")
    
    try:
        # Enable torque and set speed for all servos
        for servo_id in servo_ids:
            # Enable torque
            dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(
                portHandler, servo_id, ADDR_TORQUE_ENABLE, TORQUE_ENABLE
            )
            if dxl_comm_result != COMM_SUCCESS:
                print(f"Failed to enable torque for servo {servo_id}: {packetHandler.getTxRxResult(dxl_comm_result)}")
                continue
            elif dxl_error != 0:
                print(f"Servo {servo_id} torque enable error: {packetHandler.getRxPacketError(dxl_error)}")
                continue
            
            # Set minimal speed (profile velocity)
            dxl_comm_result, dxl_error = packetHandler.write4ByteTxRx(
                portHandler, servo_id, ADDR_PROFILE_VELOCITY, MIN_SPEED
            )
            if dxl_comm_result != COMM_SUCCESS:
                print(f"Failed to set speed for servo {servo_id}: {packetHandler.getTxRxResult(dxl_comm_result)}")
            elif dxl_error != 0:
                print(f"Servo {servo_id} speed setting error: {packetHandler.getRxPacketError(dxl_error)}")
            else:
                print(f"Servo {servo_id}: Torque enabled, speed set to {MIN_SPEED}")
        
        print(f"\nMoving all servos to position {TARGET_POSITION} (180 degrees)...")
        
        # Move all servos to target position
        for servo_id in servo_ids:
            dxl_comm_result, dxl_error = packetHandler.write4ByteTxRx(
                portHandler, servo_id, ADDR_GOAL_POSITION, TARGET_POSITION
            )
            if dxl_comm_result != COMM_SUCCESS:
                print(f"Failed to move servo {servo_id}: {packetHandler.getTxRxResult(dxl_comm_result)}")
            elif dxl_error != 0:
                print(f"Servo {servo_id} movement error: {packetHandler.getRxPacketError(dxl_error)}")
            else:
                print(f"Servo {servo_id}: Moving to position {TARGET_POSITION}")
        
        print("\nAll movement commands sent successfully!")
        print("Press Enter to disable torque and exit...")
        input()
        
    except KeyboardInterrupt:
        print("\nOperation interrupted by user")
    
    finally:
        # Disable torque for all servos
        print("\nDisabling torque for all servos...")
        for servo_id in servo_ids:
            dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(
                portHandler, servo_id, ADDR_TORQUE_ENABLE, TORQUE_DISABLE
            )
            if dxl_comm_result == COMM_SUCCESS and dxl_error == 0:
                print(f"Servo {servo_id}: Torque disabled")
        
        # Close port
        portHandler.closePort()
        print("Port closed")

if __name__ == "__main__":
    main()