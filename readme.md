# humanoid_ws
ROS 2, MoveIt, Python, C++, Git, colcon, rosdep, URDF/Xacro, YAML

## Commands

#### install dependences
> chmod +x ./bootstrap.sh
> 
> ./bootstrap.sh

#### build workspace
> colcon build
> 
> source install/setup.bash

#### add to ~/.bashrc
> source /opt/ros/humble/setup.bash
> 
> source ~/ws_moveit2/install/setup.bash
> 
> source ~/humanoid_ws/install/setup.bash

#### run in seperate terminals
> ros2 launch myrobot_moveit_config umbrella.launch.py

> ros2 run half_humanoid_control_actions humanoid_command_listener.py

> ros2 run half_humanoid_control_actions humanoid_command_publisher.py

## Updates

- Build MoveIt config files, launch scripts, and URDF/XACRO robot descriptions.

- Integrate Dynamixel actuators with the workspace - hardware-software communication.

- Develope ROS2 actions using listeners and publishers for gestures.

- Optimize backend pipeline, use OMPL for plan & execute, run with terminal only, eliminate execution delays.
