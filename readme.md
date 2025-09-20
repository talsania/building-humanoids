# humanoid_ws

Building Humanoids: MIS/END-TIRI/ME/HPM/2526/004
![PXL_20250609_142242649](https://github.com/user-attachments/assets/f465c342-139f-4c75-b549-1a14104c73db)

## Dev Updates V2

- Update URDF to v2 for Gripper integration
- Obstacle Avoidance using octomap
- Moveit issue with revolute to prismatic conversion and execution on real hardware (open #3518)
- Add Gripper gestures
- Add classes for Troubleshooting Feedbacks
- Add Cpp code for Safety contraints - absolute and relative torque, absolute velocity and joint limits
- Class for Hardwarre Connections and Temperature check
- Piroky Custom Library in Cpp instead of KDL (M-C-G matrix)

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

<img width="2880" height="1800" alt="Screenshot from 2025-05-22 10-28-24" src="https://github.com/user-attachments/assets/56c0bdde-ed8b-463d-b3f7-9321200664f6" />

## Commands

### Launch Simulation & Hardware

```bash
ros2 launch myrobot_moveit_config robot.launch.py
```

### Gesture Control

*Topic name:* ```/humanoid_command```

Start the gesture subscriber:
```bash
ros2 run half_humanoid_control_actions humanoid_command_listener
```

Send gesture commands:
```bash
ros2 topic pub /humanoid_command std_msgs/msg/String "{data: 'hi'}"
```

### Pick & Place Operations

*Topic name for camera frame:* ```/pick_camera_tf``` ```/place_camera_tf```

*Topic name for base_link frame:* ```/pick_transform``` ```/place_transform```

Start the IK solver:
```bash
ros2 run pick_place_with_grasp pick_place_node
```

Send pick transform:
```bash
ros2 topic pub --once /pick_transform std_msgs/msg/Float64MultiArray
 1960  "data: [1,0,0,0.4, 0,1,0,-0.1, 0,0,1,0.150, 0,0,0,1]"
```

### Realsense Camera

*Topic name:* ```/camera/depth/color/points```

```bash
ros2 run realsense2_camera realsense2_camera_node --ros-args   -p align_depth.enable:=true   -p pointcloud.enable:=true   -p depth_module.profile:="640x480x30"   -p enable_color:=true   -p enable_depth:=true   -p enable_accel:=false   -p enable_gyro:=false
```

<img width="700" height="1465" alt="Screenshot from 2025-06-03 20-25-32~2" src="https://github.com/user-attachments/assets/7d588d1f-dfc4-4a46-b11d-3ed7d06425d5" />

## Hardware Info

*180° in Dynamixel Wizard = 0° in Rviz*

- **XM430-W350** for Arms, **XL430-W250** for Head and Grippers
- **Protocol:** 2.0
- **Baud Rate:** 4000000
- **Left Arm:** 11 -> 17
- **Right Arm:** 21 -> 27
- **Grippers:** 28, 18 (1024 = close, 2048 = open)
- **Head:** 31, 32
