# from launch import LaunchDescription
# from launch.actions import IncludeLaunchDescription
# from launch.launch_description_sources import PythonLaunchDescriptionSource
# from launch.substitutions import PathJoinSubstitution
# from launch_ros.actions import Node
# from launch_ros.substitutions import FindPackageShare

# def generate_launch_description():

#     # --- MoveIt Launch ---
#     pkg_moveit = FindPackageShare("myrobot_moveit_config")

#     # Launch MoveGroup
#     move_group = IncludeLaunchDescription(
#         PythonLaunchDescriptionSource(
#             PathJoinSubstitution([pkg_moveit, "launch", "move_group.launch.py"])
#         )
#     )

#     # Launch planning and control (Rviz, etc.)
#     planning_and_control = IncludeLaunchDescription(
#         PythonLaunchDescriptionSource(
#             PathJoinSubstitution([pkg_moveit, "launch", "planning_and_control.launch.py"])
#         )
#     )

#     # --- RealSense Camera Node ---
#     realsense_camera_node = Node(
#         package='realsense2_camera',
#         executable='realsense2_camera_node',
#         name='realsense2_camera',
#         parameters=[{
#             'align_depth.enable': True,
#             'pointcloud.enable': True,
#             'depth_module.profile': '640x480x30',
#             'enable_color': True,
#             'enable_depth': True,
#             'enable_accel': False,
#             'enable_gyro': False,
#         }],
#         output='screen'
#     )

#     # --- Gripper Control Node ---
#     # gripper_control_node = Node(
#     #     package='gripper_control',
#     #     executable='gripper_control_node',
#     #     name='gripper_control_node',
#     #     output='screen'
#     # )

#     # --- Humanoid Command Listener Node ---
#     humanoid_command_listener_node = Node(
#         package='half_humanoid_control_actions',
#         executable='humanoid_command_listener',
#         name='humanoid_command_listener',
#         output='screen'
#     )

#     # --- Pick and Place Node ---
#     # pick_place_node = Node(
#     #     package='pick_place_with_grasp',
#     #     executable='pick_place_node',
#     #     name='pick_place_node',
#     #     output='screen'
#     # )

#     # --- Launch Description ---
#     # Combine all components into a single launch description
#     return LaunchDescription([
#         move_group,
#         planning_and_control,
#         realsense_camera_node,
#         # gripper_control_node,
#         humanoid_command_listener_node,
#         # pick_place_node,
#     ])

# -------------------------------------------------------------------------

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch_ros.actions import Node

def generate_launch_description():
    pkg_moveit = FindPackageShare("myrobot_moveit_config")

    # Launch MoveGroup
    move_group = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([pkg_moveit, "launch", "move_group.launch.py"])
        )
    )

    # Launch planning and control
    planning_and_control = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([pkg_moveit, "launch", "planning_and_control.launch.py"])
        )
    )

    return LaunchDescription([
        move_group,
        planning_and_control,
    ])
