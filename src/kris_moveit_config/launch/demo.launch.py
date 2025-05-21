# from moveit_configs_utils import MoveItConfigsBuilder
# from moveit_configs_utils.launches import generate_demo_launch


# def generate_launch_description():
#     moveit_config = MoveItConfigsBuilder("myrobot_description", package_name="kris_moveit_config").to_moveit_configs()
#     return generate_demo_launch(moveit_config)

from moveit_configs_utils import MoveItConfigsBuilder
from moveit_configs_utils.launches import generate_demo_launch
from launch_ros.actions import Node

def generate_launch_description():
    moveit_config = MoveItConfigsBuilder(
        "myrobot_description",
        package_name="kris_moveit_config"
    ).to_moveit_configs()

    # 1) get the standard demo launch
    ld = generate_demo_launch(moveit_config)

    # 2) then append a spawner for head_controller
    ld.add_action(Node(
        package='controller_manager',
        executable='spawner',
        arguments=['head_controller'],
        output='screen'
    ))

    return ld
