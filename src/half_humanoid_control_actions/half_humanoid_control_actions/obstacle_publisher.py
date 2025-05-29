import rclpy
from rclpy.node import Node
from moveit_msgs.msg import PlanningScene, CollisionObject
from shape_msgs.msg import SolidPrimitive
from geometry_msgs.msg import Pose
from std_msgs.msg import Header

class ObstaclePublisher(Node):
    def __init__(self):
        super().__init__('obstacle_publisher')
        self.publisher_ = self.create_publisher(PlanningScene, 'planning_scene', 10)
        self.timer = self.create_timer(2.0, self.add_obstacle)  # Publishes once after 2 sec

    def add_obstacle(self):
        # Define box dimensions
        box = SolidPrimitive()
        box.type = SolidPrimitive.BOX
        box.dimensions = [0.4, 0.4, 0.4]  # 40cm cube

        # Define box pose
        pose = Pose()
        pose.position.x = 0.6
        pose.position.y = 0.0
        pose.position.z = 0.2  # Half the height to rest on ground
        pose.orientation.w = 1.0

        # Create CollisionObject
        collision_object = CollisionObject()
        collision_object.id = "box1"
        collision_object.header = Header()
        collision_object.header.frame_id = "base_link"  # Adjust to your robot base
        collision_object.primitives.append(box)
        collision_object.primitive_poses.append(pose)
        collision_object.operation = CollisionObject.ADD

        # Send in PlanningScene message
        scene = PlanningScene()
        scene.is_diff = True
        scene.world.collision_objects.append(collision_object)

        self.publisher_.publish(scene)
        self.get_logger().info("Published obstacle to planning scene.")

        # Optional: only publish once
        self.timer.cancel()

def main(args=None):
    rclpy.init(args=args)
    node = ObstaclePublisher()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
