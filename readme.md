### Add to ~/.bashrc

> source /opt/ros/humble/setup.bash
>
> source ~/ws_moveit2/install/setup.bash
>
> source ~/humanoid_ws/install/setup.bash

### Commands

> ros2 launch myrobot_moveit_config umbrella.launch.py

> ros2 run half_humanoid_control_actions humanoid_command_listener.py

> ros2 run half_humanoid_control_actions humanoid_command_publisher.py

### Updates

- Build MoveIt config files, launch scripts, and URDF/XACRO robot descriptions to setup the humanoid workspace.

- Integrate Dynamixel actuators with the workspace for hardware-software communication.

- Develope ROS2 actions using custom listeners and publishers for real-time control.

- Optimize backend pipeline to optimize execution delays using OMPL only.
