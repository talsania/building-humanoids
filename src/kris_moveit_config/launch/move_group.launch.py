import os
import yaml

from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import Command
from launch_ros.parameter_descriptions import ParameterValue
from moveit_configs_utils import MoveItConfigsBuilder


def generate_launch_description():
    # 1) Locate your config files
    pkg_share = get_package_share_directory('kris_moveit_config')
    xacro_file = os.path.join(pkg_share, 'config', 'v2.urdf.xacro')
    ompl_yaml  = os.path.join(pkg_share, 'config', 'ompl_planning.yaml')

    # 2) robot_description: expand the URDF Xacro for REAL hardware
    robot_description_content = Command([
        'xacro ', xacro_file,
        ' use_fake_hardware:=false',
        ' fake_sensor_commands:=false'
    ])
    robot_description = {
        'robot_description': ParameterValue(
            robot_description_content,
            value_type=str
        )
    }

    # 3) Build the rest of the MoveIt parameters (semantic, kinematics, limits)
    mb = MoveItConfigsBuilder(
        robot_name='v2',
        package_name='kris_moveit_config'
    )
    # NOTE: we do *not* call mb.robot_description(...) here, since we override it manually
    mb.robot_description_semantic(file_path='config/v2.srdf')
    mb.robot_description_kinematics(file_path='config/kinematics.yaml')
    mb.joint_limits(file_path='config/joint_limits.yaml')

    moveit_config = mb.to_moveit_configs()
    base_params   = moveit_config.to_dict()

    # 4) Clean up any CHOMP or pre‐set adapters
    base_params.pop('chomp', None)
    if 'ompl' in base_params:
        base_params['ompl'].pop('request_adapters', None)

    # 5) Load your OMPL YAML and merge
    try:
        with open(ompl_yaml, 'r') as f:
            ompl_cfg = yaml.safe_load(f).get('ompl', {})
    except Exception as e:
        print(f"[Warning] could not load OMPL config: {e}")
        ompl_cfg = {}

    base_params.setdefault('ompl', {}).update(ompl_cfg)
    base_params['ompl'].update({
        'planning_plugin':    'ompl_interface/OMPLPlanner',
        'request_adapters': (
            "default_planner_request_adapters/AddTimeOptimalParameterization "
            "default_planner_request_adapters/FixWorkspaceBounds "
            "default_planner_request_adapters/FixStartStateBounds "
            "default_planner_request_adapters/FixStartStateCollision "
            "default_planner_request_adapters/FixStartStatePathConstraints"
        )
    })

    # 6) Disable Pilz adapters
    base_params.setdefault('pilz_industrial_motion_planner', {})['request_adapters'] = ""

    # 7) Global pipelines & adapters
    base_params.update({
        'planning_pipelines': ['ompl'],
        'default_planning_pipeline': 'ompl',
        'request_adapters': [
            'default_planner_request_adapters/AddTimeOptimalParameterization',
            'default_planner_request_adapters/FixWorkspaceBounds',
            'default_planner_request_adapters/FixStartStateBounds',
            'default_planner_request_adapters/FixStartStateCollision',
            'default_planner_request_adapters/FixStartStatePathConstraints',
        ],
        'default_planner_request_adapters/FixStartStateBounds.start_state_max_bounds_error': 0.1,
    })

    # 8) Launch the Move Group with BOTH the real hardware robot_description and the MoveIt params
    move_group_node = Node(
        package='moveit_ros_move_group',
        executable='move_group',
        output='screen',
        parameters=[
            robot_description,
            base_params
        ],
        arguments=[
            '--ros-args',
            '--log-level', 'INFO',
            '--log-level', 'moveit_ros_move_group:=DEBUG',
            '--log-level', 'moveit_planners_ompl:=DEBUG',
            '--log-level', 'pluginlib:=DEBUG',
        ],
    )

    return LaunchDescription([move_group_node])
