#!/bin/bash

# Test script for Jacobian functionality
echo "=== Kris Kinematics Plugin Jacobian Test ==="

# Check if URDF file path is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <urdf_file> [frame_name]"
    echo "Example: $0 /path/to/your/robot.urdf end_effector"
    exit 1
fi

URDF_FILE="$1"
FRAME_NAME="${2:-end_effector}"

echo "URDF file: $URDF_FILE"
echo "Frame name: $FRAME_NAME"

# Check if URDF file exists
if [ ! -f "$URDF_FILE" ]; then
    echo "Error: URDF file '$URDF_FILE' not found!"
    exit 1
fi

# Build the test
echo "Building Jacobian test..."
cd "$(dirname "$0")/test"
mkdir -p build
cd build

# Try to build with cmake
if cmake .. && make; then
    echo "Build successful!"
    
    # Run the test
    echo "Running Jacobian test..."
    ./test_jacobian_standalone "$URDF_FILE" "$FRAME_NAME"
    
    echo "Test completed!"
else
    echo "Build failed. Make sure you have pinocchio installed."
    echo "Try: sudo apt install ros-humble-pinocchio"
    exit 1
fi