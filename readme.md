# humanoid_ws
ROS 2, MoveIt, Python, C++, Git, colcon, rosdep, URDF/Xacro, YAML

## Setup

### Build Workspace
```bash
cd ~/humanoid_ws
colcon build
source install/setup.bash
```

### Environment Configuration
Add to your `~/.bashrc` file:
```bash
source /opt/ros/humble/setup.bash
source ~/ws_moveit2/install/setup.bash
source ~/humanoid_ws/install/setup.bash
```

## Usage

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
Start the dual arm IK solver:
```bash
ros2 run dual_arm_ik_solver dual_arm_ik_solver
```

Send pick transform:
```bash
ros2 topic pub --once /pick_transform std_msgs/msg/Float64MultiArray \
  "data: [1,0,0,0.4, 0,1,0,-0.1, 0,0,1,0.150, 0,0,0,1]"
```

## Development Updates

- Built MoveIt config files, launch scripts, and URDF/XACRO robot descriptions
- Integrated Dynamixel actuators with hardware-software communication
- Developed ROS 2 actions using listeners and publishers for gestures
- Added pick & place functionality
- Optimized backend pipeline with AI team using OMPL for planning and execution
