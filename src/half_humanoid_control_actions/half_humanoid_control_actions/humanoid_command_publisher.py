import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class HumanoidCommandPublisher(Node):
    def __init__(self):
        super().__init__('humanoid_command_publisher')
        self.publisher = self.create_publisher(String, 'humanoid_command', 10)
        rclpy.spin_once(self,timeout_sec=0.1)
        self.run()


    def run(self):   
        while rclpy.ok():
            user_input = input("Enter a command for the humanoid (hi / wave_left / wave_right / bro / nod_yes /nod_no / handshake / cross_arms ): ").strip().lower()
            
            if user_input in ['hi', 'wave_left', 'wave_right', 'nod_yes', 'bro', 'nod_no', 'handshake', 'cross_arms']:
                msg = String()
                msg.data = user_input
                self.publisher.publish(msg)
                self.get_logger().info(f"Published command: '{user_input}' to 'humanoid_command' topic.")

            elif user_input == 'q':
                self.get_logger().info('Exiting..')
                break

            else:
                self.get_logger().warn("Invalid command! ")
            rclpy.spin_once(self,timeout_sec=0.1)

            # # Shutdown after publishing
            # rclpy.shutdown()


def main(args=None):
    rclpy.init(args=args)
    node = HumanoidCommandPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
