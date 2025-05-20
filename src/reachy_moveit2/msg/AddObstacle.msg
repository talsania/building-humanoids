# AddObstacle.msg
std_msgs/Header header

# Unique identifier for the obstacle.
string id

# Operation to perform: "ADD" or "REMOVE"
string operation

# Shape of the obstacle.
shape_msgs/SolidPrimitive primitive

# Pose of the obstacle in the planning frame.
geometry_msgs/PoseStamped pose
