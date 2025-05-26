# launch/planning_and_control.launch.py
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch_ros.parameter_descriptions import ParameterValue

def generate_launch_description():
    pkg = FindPackageShare("myrobot_moveit_config")

    # 1) Build the robot_description (this must call your ros2_control macro
    #    so that <robot name="..."> actually appears in the URDF)
    robot_description = ParameterValue(
        Command([
            "xacro ",
            PathJoinSubstitution([pkg, "config", "myrobot_description.urdf.xacro"]),
            " name:=myrobot",                 # <— make sure you give it a name!
            " port_name:=/dev/ttyUSB0",
            " use_fake_hardware:=false",
            " fake_sensor_commands:=false",
            " initial_positions_file:=",
            PathJoinSubstitution([pkg, "config", "initial_positions.yaml"]),
        ]),
        value_type=str,
    )

    # 2) Build the SRDF
    robot_description_semantic = ParameterValue(
        Command([
            "xacro ",
            PathJoinSubstitution([pkg, "config", "myrobot_description.srdf"]),
        ]),
        value_type=str,
    )

    # 3) Paths to your MoveIt YAMLs
    moveit_controllers   = PathJoinSubstitution([pkg, "config", "moveit_controllers_for_launch.yaml"])
    kinematics_yaml      = PathJoinSubstitution([pkg, "config", "kinematics.yaml"])
    joint_limits_yaml    = PathJoinSubstitution([pkg, "config", "joint_limits.yaml"])
    planning_scene_yaml  = PathJoinSubstitution([pkg, "config", "planning_scene_monitor_params.yaml"])
    # 3b) OMPL planning pipeline config
    ompl_planning_yaml   = PathJoinSubstitution([pkg, "config", "ompl_planning.yaml"])

    # 4) ros2_control controller definitions
    ros2_ctrl_yaml       = PathJoinSubstitution([pkg, "config", "ros2_controllers.yaml"])

    return LaunchDescription([
        # —————————————————————————————————————————————
        # Publish robot_description & TFs
        Node(
            package="robot_state_publisher",
            executable="robot_state_publisher",
            parameters=[{"robot_description": robot_description}],
            output="screen",
        ),

        # —————————————————————————————————————————————
        # ros2_control: now our URDF’s <ros2_control> block is present
        Node(
            package="controller_manager",
            executable="ros2_control_node",
            parameters=[
                {"robot_description": robot_description},  # re-publish URDF so it sees <ros2_control>
                ros2_ctrl_yaml
            ],
            output="screen",
        ),

        # spawn the two controllers
        Node(package="controller_manager", executable="spawner",
             arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
             output="screen"),
        Node(package="controller_manager", executable="spawner",
             arguments=["dual_arm_controller",    "--controller-manager", "/controller_manager"],
             output="screen"),

        # —————————————————————————————————————————————
        # MoveIt! move_group
        Node(
            package="moveit_ros_move_group",
            executable="move_group",
            name="move_group",
            output="screen",
            parameters=[
                {"robot_description": robot_description},
                {"robot_description_semantic": robot_description_semantic},
                moveit_controllers,
                kinematics_yaml,
                joint_limits_yaml,
                planning_scene_yaml,
                ompl_planning_yaml,
                
            ],
        ),

        # —————————————————————————————————————————————
        # RViz
        Node(
            package="rviz2",
            executable="rviz2",
            name="rviz2",
            output="screen",
            # Hand RViz both descriptions so PlanningSceneMonitor can load them
            parameters=[
                {"robot_description": robot_description},
                {"robot_description_semantic": robot_description_semantic}
            ],
            arguments=["-d", PathJoinSubstitution([pkg, "config", "moveit.rviz"])],
        ),
    ])
