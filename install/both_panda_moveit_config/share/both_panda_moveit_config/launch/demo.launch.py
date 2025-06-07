from launch import LaunchDescription
from moveit_configs_utils import MoveItConfigsBuilder
from moveit_configs_utils.launches import generate_demo_launch


def generate_launch_description():
    moveit_config = (
        MoveItConfigsBuilder("bimanual_panda", package_name="both_panda_moveit_config").robot_description(file_path="config/bimanual_panda.urdf.xacro")
        .robot_description_semantic(file_path="config/bimanual_panda.srdf")
        .robot_description_kinematics(file_path="config/kinematics.yaml")
        .trajectory_execution(file_path="config/moveit_controllers.yaml")
        .planning_pipelines(pipelines=["ompl"])
        .to_moveit_configs()
    )
    return generate_demo_launch(moveit_config)
    