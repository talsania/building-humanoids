#!/usr/bin/env python3
# Simple script to move a Dynamixel motor

import os
import sys
import time
from dynamixel_sdk import *

# Protocol version
PROTOCOL_VERSION = 2.0

# Default settings
BAUDRATE = 4000000
DEVICENAME = '/dev/ttyUSB0'  # Change this to match your port
DXL_ID = 11  # Change this to your motor ID

# Control table addresses (may vary by model)
ADDR_TORQUE_ENABLE = 64
ADDR_GOAL_POSITION = 116
ADDR_PRESENT_POSITION = 132

# Data value limits (may vary by model)
DXL_MINIMUM_POSITION_VALUE = 0
DXL_MAXIMUM_POSITION_VALUE = 4095  # 0-4095 for XM430-W350

def move_motor():
    # Initialize SDK
    portHandler = PortHandler(DEVICENAME)
    packetHandler = PacketHandler(PROTOCOL_VERSION)
    
    # Open port
    if not portHandler.openPort():
        print("Failed to open the port")
        return
    
    # Set port baudrate
    if not portHandler.setBaudRate(BAUDRATE):
        print("Failed to change baudrate")
        return
    
    print(f"Connected to motor ID {DXL_ID} on {DEVICENAME}")
    
    # Ping the motor
    model_number, comm_result, error = packetHandler.ping(portHandler, DXL_ID)
    if comm_result != COMM_SUCCESS:
        print(f"Failed to ping motor {DXL_ID}")
        portHandler.closePort()
        return
    
    print(f"Motor ID {DXL_ID} found, model number: {model_number}")
    
    # Enable torque
    comm_result, error = packetHandler.write1ByteTxRx(portHandler, DXL_ID, ADDR_TORQUE_ENABLE, 1)
    if comm_result != COMM_SUCCESS:
        print(f"Failed to enable torque: {packetHandler.getTxRxResult(comm_result)}")
        portHandler.closePort()
        return
    
    print("Torque enabled")
    
    try:
        # Move to center position
        center_position = (DXL_MINIMUM_POSITION_VALUE + DXL_MAXIMUM_POSITION_VALUE) // 2
        print(f"Moving to center position ({center_position})...")
        packetHandler.write4ByteTxRx(portHandler, DXL_ID, ADDR_GOAL_POSITION, center_position)
        time.sleep(2)
        
        # Move to minimum position
        print(f"Moving to minimum position ({DXL_MINIMUM_POSITION_VALUE})...")
        packetHandler.write4ByteTxRx(portHandler, DXL_ID, ADDR_GOAL_POSITION, DXL_MINIMUM_POSITION_VALUE)
        time.sleep(2)
        
        # Move to maximum position
        print(f"Moving to maximum position ({DXL_MAXIMUM_POSITION_VALUE})...")
        packetHandler.write4ByteTxRx(portHandler, DXL_ID, ADDR_GOAL_POSITION, DXL_MAXIMUM_POSITION_VALUE)
        time.sleep(2)
        
        # Move back to center position
        print(f"Moving back to center position ({center_position})...")
        packetHandler.write4ByteTxRx(portHandler, DXL_ID, ADDR_GOAL_POSITION, center_position)
        time.sleep(2)
        
    except KeyboardInterrupt:
        print("Stopping due to keyboard interrupt")
    
    finally:
        # Disable torque
        packetHandler.write1ByteTxRx(portHandler, DXL_ID, ADDR_TORQUE_ENABLE, 0)
        print("Torque disabled")
        
        # Close port
        portHandler.closePort()
        print("Port closed")

def main():
    move_motor()

if __name__ == '__main__':
    main()
