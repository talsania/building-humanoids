#!/usr/bin/env python3
# Simple script to scan for Dynamixel motors

import os
import sys
from dynamixel_sdk import *

# Protocol version
PROTOCOL_VERSION = 2.0  # Default for most newer Dynamixel motors

# Default setting
BAUDRATE = 4000000
DEVICENAME = '/dev/ttyUSB0'  # Change this to match your port

def scan_dynamixels():
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
    
    print(f"Scanning for Dynamixel motors on {DEVICENAME} at {BAUDRATE} baud...")
    
    # Try with Protocol 2.0 first
    found_motors = []
    for motor_id in range(0, 253):  # Scan all possible IDs
        model_number, comm_result, error = packetHandler.ping(portHandler, motor_id)
        
        if comm_result == COMM_SUCCESS:
            print(f"Found motor ID: {motor_id}, model number: {model_number}")
            found_motors.append((motor_id, model_number))
    
    # If no motors found, try Protocol 1.0
    if not found_motors:
        print("No motors found with Protocol 2.0, trying Protocol 1.0...")
        packetHandler = PacketHandler(1.0)
        
        for motor_id in range(0, 253):
            model_number, comm_result, error = packetHandler.ping(portHandler, motor_id)
            
            if comm_result == COMM_SUCCESS:
                print(f"Found motor ID: {motor_id}, model number: {model_number} (Protocol 1.0)")
                found_motors.append((motor_id, model_number))
    
    print(f"Scan complete. Found {len(found_motors)} motors.")
    
    # Close port
    portHandler.closePort()

def main():
    scan_dynamixels()

if __name__ == '__main__':
    main()
