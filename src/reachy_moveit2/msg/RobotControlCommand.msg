# RobotControlCommand.msg
std_msgs/Header header

# Mode for control: "cartesian" or "joint"
string mode

# For joint state control (if mode is "joint")
sensor_msgs/JointState joint_state

# For Cartesian control (if mode is "cartesian")
geometry_msgs/PoseStamped cartesian_target
