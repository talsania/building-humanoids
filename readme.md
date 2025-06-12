# humanoid_ws

ROS 2, MoveIt, Python, C++, Git, colcon, rosdep, URDF/Xacro, YAML

## Dev Updates

- Build MoveIt config files, launch scripts, and URDF/XACRO robot descriptions
- Integrate Dynamixel actuators for hardware-software communication
- Use only OMPL for planning and execution
- Develope ROS 2 actions using listeners and publishers for gestures
- Add pick & place functionality, pre-grasp positions for pre-pick and pre-place
- Solve Gripper URDF issue, add gripper controls node seperately
- End-to-end backend pipeline with AI team

## Workspace Setup

### Build ws

```bash
cd ~/humanoid_ws
colcon build
source install/setup.bash
```

### Env Config

Add to your `~/.bashrc` file:
```bash
source /opt/ros/humble/setup.bash
source ~/ws_moveit2/install/setup.bash
source ~/humanoid_ws/install/setup.bash
```

## Commands

### Launch Simulation & Hardware

```bash
ros2 launch myrobot_moveit_config umbrella.launch.py
```

### Gesture Control

Start the gesture subscriber:
```bash
ros2 run half_humanoid_control_actions humanoid_command_listener
```

Send gesture commands:
```bash
ros2 topic pub /humanoid_command std_msgs/msg/String "{data: 'hi'}"
```

### Pick & Place Operations

Start the IK solver:
```bash
ros2 run pick_place_with_grasp pick_place_node
```

Send pick transform:
```bash
ros2 topic pub --once /pick_transform std_msgs/msg/Float64MultiArray
 1960  "data: [1,0,0,0.4, 0,1,0,-0.1, 0,0,1,0.150, 0,0,0,1]"
```

### Gripper Open & Close

Start Gripper Node
```bash
ros2 run gripper_control gripper_control_node
```

Gripper Ops
```bash
ros2 topic pub --once /left_gripper_command std_msgs/String "data: 'close'"    # Left Hand (ID:28)
ros2 topic pub --once /left_gripper_command std_msgs/String "data: 'open'"    

ros2 topic pub --once /right_gripper_command std_msgs/String "data: 'close'"    # Right Hand (ID:18)
ros2 topic pub --once /right_gripper_command std_msgs/String "data: 'open'"    
```

## Hardware Info
*180° in Dynamixel Wizard = 0° in Rviz*

- **XM430-W350** for Arms, **XL430-W250** for Head and Grippers
- **Protocol:** 2.0
- **Baud Rate:** 4000000
- **Left Arm:** 11 -> 17
- **Right Arm:** 21 -> 27
- **Grippers:** 28, 18 (90 = close, 180 = open)
- **Head:** 31, 32
