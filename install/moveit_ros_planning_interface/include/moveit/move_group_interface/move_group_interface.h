#pragma once

#include <moveit/macros/class_forward.h>
#include <moveit/robot_state/robot_state.h>
#include <moveit/utils/moveit_error_code.h>
#include <moveit_msgs/msg/robot_trajectory.hpp>
#include <moveit_msgs/msg/robot_state.hpp>
#include <moveit_msgs/msg/planner_interface_description.hpp>
#include <moveit_msgs/msg/constraints.hpp>
#include <moveit_msgs/msg/grasp.hpp>
#include <moveit_msgs/action/move_group.hpp>
#include <moveit_msgs/action/execute_trajectory.hpp>
#include <moveit_msgs/msg/motion_plan_request.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <memory>
#include <utility>
#include <tf2_ros/buffer.h>
#include <moveit_move_group_interface_export.h>

namespace moveit
{
namespace planning_interface
{
using MoveItErrorCode [[deprecated("Use moveit::core::MoveItErrorCode")]] = moveit::core::MoveItErrorCode;

MOVEIT_CLASS_FORWARD(MoveGroupInterface);

class MOVEIT_MOVE_GROUP_INTERFACE_EXPORT MoveGroupInterface
{
public:
    static const std::string ROBOT_DESCRIPTION;

    struct Options
    {
        Options(std::string group_name, std::string desc = ROBOT_DESCRIPTION, std::string move_group_namespace = "")
            : group_name_(std::move(group_name))
            , robot_description_(std::move(desc))
            , move_group_namespace_(std::move(move_group_namespace))
        {
        }

        std::string group_name_;
        std::string robot_description_;
        moveit::core::RobotModelConstPtr robot_model_;
        std::string move_group_namespace_;
    };

    MOVEIT_STRUCT_FORWARD(Plan);

    struct Plan
    {
        moveit_msgs::msg::RobotState start_state_;
        moveit_msgs::msg::RobotTrajectory trajectory_;
        double planning_time_;
    };

    MoveGroupInterface(const rclcpp::Node::SharedPtr& node, const Options& opt,
                                         const std::shared_ptr<tf2_ros::Buffer>& tf_buffer = std::shared_ptr<tf2_ros::Buffer>(),
                                         const rclcpp::Duration& wait_for_servers = rclcpp::Duration::from_seconds(-1));

    MoveGroupInterface(const rclcpp::Node::SharedPtr& node, const std::string& group,
                                         const std::shared_ptr<tf2_ros::Buffer>& tf_buffer = std::shared_ptr<tf2_ros::Buffer>(),
                                         const rclcpp::Duration& wait_for_servers = rclcpp::Duration::from_seconds(-1));

    ~MoveGroupInterface();

    MoveGroupInterface(const MoveGroupInterface&) = delete;
    MoveGroupInterface& operator=(const MoveGroupInterface&) = delete;

    MoveGroupInterface(MoveGroupInterface&& other) noexcept;
    MoveGroupInterface& operator=(MoveGroupInterface&& other) noexcept;
    const std::string& getName() const;
    const std::vector<std::string>& getNamedTargets() const;
    moveit::core::RobotModelConstPtr getRobotModel() const;
    rclcpp::Node::SharedPtr getNodeHandle();
    const std::string& getPlanningFrame() const;
    const std::vector<std::string>& getJointModelGroupNames() const;
    const std::vector<std::string>& getJointNames() const;
    const std::vector<std::string>& getLinkNames() const;
    std::map<std::string, double> getNamedTargetValues(const std::string& name) const;
    const std::vector<std::string>& getActiveJoints() const;
    const std::vector<std::string>& getJoints() const;
    unsigned int getVariableCount() const;
    bool getInterfaceDescriptions(std::vector<moveit_msgs::msg::PlannerInterfaceDescription>& desc) const;
    bool getInterfaceDescription(moveit_msgs::msg::PlannerInterfaceDescription& desc) const;
    std::map<std::string, std::string> getPlannerParams(const std::string& planner_id,
                                                                                                            const std::string& group = "") const;
    void setPlannerParams(const std::string& planner_id, const std::string& group,
                                                const std::map<std::string, std::string>& params, bool bReplace = false);
    std::string getDefaultPlanningPipelineId() const;
    void setPlanningPipelineId(const std::string& pipeline_id);
    const std::string& getPlanningPipelineId() const;
    std::string getDefaultPlannerId(const std::string& group = "") const;
    void setPlannerId(const std::string& planner_id);
    const std::string& getPlannerId() const;
    void setPlanningTime(double seconds);
    void setNumPlanningAttempts(unsigned int num_planning_attempts);
    void setMaxVelocityScalingFactor(double max_velocity_scaling_factor);
    void setMaxAccelerationScalingFactor(double max_acceleration_scaling_factor);
    double getPlanningTime() const;
    double getGoalJointTolerance() const;
    double getGoalPositionTolerance() const;
    double getGoalOrientationTolerance() const;
    void setGoalTolerance(double tolerance);
    void setGoalJointTolerance(double tolerance);
    void setGoalPositionTolerance(double tolerance);
    void setGoalOrientationTolerance(double tolerance);
    void setWorkspace(double minx, double miny, double minz, double maxx, double maxy, double maxz);
    void setStartState(const moveit_msgs::msg::RobotState& start_state);
    void setStartState(const moveit::core::RobotState& start_state);
    void setStartStateToCurrentState();
    void setSupportSurfaceName(const std::string& name);
    bool setJointValueTarget(const std::vector<double>& group_variable_values);
    bool setJointValueTarget(const std::map<std::string, double>& variable_values);
    bool setJointValueTarget(const std::vector<std::string>& variable_names, const std::vector<double>& variable_values);
    bool setJointValueTarget(const moveit::core::RobotState& robot_state);
    bool setJointValueTarget(const std::string& joint_name, const std::vector<double>& values);
    bool setJointValueTarget(const std::string& joint_name, double value);
    bool setJointValueTarget(const sensor_msgs::msg::JointState& state);
    bool setJointValueTarget(const geometry_msgs::msg::Pose& eef_pose, const std::string& end_effector_link = "");
    bool setJointValueTarget(const geometry_msgs::msg::PoseStamped& eef_pose, const std::string& end_effector_link = "");
    bool setJointValueTarget(const Eigen::Isometry3d& eef_pose, const std::string& end_effector_link = "");
    bool setApproximateJointValueTarget(const geometry_msgs::msg::Pose& eef_pose,
                                                                            const std::string& end_effector_link = "");
    bool setApproximateJointValueTarget(const geometry_msgs::msg::PoseStamped& eef_pose,
                                                                            const std::string& end_effector_link = "");
    bool setApproximateJointValueTarget(const Eigen::Isometry3d& eef_pose, const std::string& end_effector_link = "");
    void setRandomTarget();
    bool setNamedTarget(const std::string& name);
    void getJointValueTarget(std::vector<double>& group_variable_values) const;
    [[deprecated]] const moveit::core::RobotState& getJointValueTarget() const;
    bool setPositionTarget(double x, double y, double z, const std::string& end_effector_link = "");
    bool setRPYTarget(double roll, double pitch, double yaw, const std::string& end_effector_link = "");
    bool setOrientationTarget(double x, double y, double z, double w, const std::string& end_effector_link = "");
    bool setPoseTarget(const Eigen::Isometry3d& end_effector_pose, const std::string& end_effector_link = "");
    bool setPoseTarget(const geometry_msgs::msg::Pose& target, const std::string& end_effector_link = "");
    bool setPoseTarget(const geometry_msgs::msg::PoseStamped& target, const std::string& end_effector_link = "");
    bool setPoseTargets(const EigenSTL::vector_Isometry3d& end_effector_pose, const std::string& end_effector_link = "");
    bool setPoseTargets(const std::vector<geometry_msgs::msg::Pose>& target, const std::string& end_effector_link = "");
    bool setPoseTargets(const std::vector<geometry_msgs::msg::PoseStamped>& target,
                                            const std::string& end_effector_link = "");
    void setPoseReferenceFrame(const std::string& pose_reference_frame);
    bool setEndEffectorLink(const std::string& end_effector_link);
    bool setEndEffector(const std::string& eef_name);
    void clearPoseTarget(const std::string& end_effector_link = "");
    void clearPoseTargets();
    const geometry_msgs::msg::PoseStamped& getPoseTarget(const std::string& end_effector_link = "") const;
    const std::vector<geometry_msgs::msg::PoseStamped>& getPoseTargets(const std::string& end_effector_link = "") const;
    const std::string& getEndEffectorLink() const;
    const std::string& getEndEffector() const;
    const std::string& getPoseReferenceFrame() const;
    moveit::core::MoveItErrorCode asyncMove();
    rclcpp_action::Client<moveit_msgs::action::MoveGroup>& getMoveGroupClient() const;
    moveit::core::MoveItErrorCode move();
    moveit::core::MoveItErrorCode plan(Plan& plan);
    moveit::core::MoveItErrorCode asyncExecute(const Plan& plan);
    moveit::core::MoveItErrorCode asyncExecute(const moveit_msgs::msg::RobotTrajectory& trajectory);
    moveit::core::MoveItErrorCode execute(const Plan& plan);
    moveit::core::MoveItErrorCode execute(const moveit_msgs::msg::RobotTrajectory& trajectory);
    double computeCartesianPath(const std::vector<geometry_msgs::msg::Pose>& waypoints, double eef_step,
                                                            double jump_threshold, moveit_msgs::msg::RobotTrajectory& trajectory,
                                                            bool avoid_collisions = true, moveit_msgs::msg::MoveItErrorCodes* error_code = nullptr);
    double computeCartesianPath(const std::vector<geometry_msgs::msg::Pose>& waypoints, double eef_step,
                                                            double jump_threshold, moveit_msgs::msg::RobotTrajectory& trajectory,
                                                            const moveit_msgs::msg::Constraints& path_constraints, bool avoid_collisions = true,
                                                            moveit_msgs::msg::MoveItErrorCodes* error_code = nullptr);
    void stop();
    void allowReplanning(bool flag);
    void setReplanAttempts(int32_t attempts);
    void setReplanDelay(double delay);
    void allowLooking(bool flag);
    void setLookAroundAttempts(int32_t attempts);
    void constructMotionPlanRequest(moveit_msgs::msg::MotionPlanRequest& request);
    bool attachObject(const std::string& object, const std::string& link = "");
    bool attachObject(const std::string& object, const std::string& link, const std::vector<std::string>& touch_links);
    bool detachObject(const std::string& name = "");
    bool startStateMonitor(double wait = 1.0);
    std::vector<double> getCurrentJointValues() const;
    moveit::core::RobotStatePtr getCurrentState(double wait = 1) const;
    geometry_msgs::msg::PoseStamped getCurrentPose(const std::string& end_effector_link = "") const;
    std::vector<double> getCurrentRPY(const std::string& end_effector_link = "") const;
    std::vector<double> getRandomJointValues() const;
    geometry_msgs::msg::PoseStamped getRandomPose(const std::string& end_effector_link = "") const;
    void rememberJointValues(const std::string& name);
    void rememberJointValues(const std::string& name, const std::vector<double>& values);
    const std::map<std::string, std::vector<double> >& getRememberedJointValues() const
    {
        return remembered_joint_values_;
    }
    void forgetJointValues(const std::string& name);
    void setConstraintsDatabase(const std::string& host, unsigned int port);
    std::vector<std::string> getKnownConstraints() const;
    moveit_msgs::msg::Constraints getPathConstraints() const;
    bool setPathConstraints(const std::string& constraint);
    void setPathConstraints(const moveit_msgs::msg::Constraints& constraint);
    void clearPathConstraints();
    moveit_msgs::msg::TrajectoryConstraints getTrajectoryConstraints() const;
    void setTrajectoryConstraints(const moveit_msgs::msg::TrajectoryConstraints& constraint);
    void clearTrajectoryConstraints();

protected:
    const moveit::core::RobotState& getTargetRobotState() const;

private:
    std::map<std::string, std::vector<double> > remembered_joint_values_;
    class MoveGroupInterfaceImpl;
    MoveGroupInterfaceImpl* impl_;
};
}  // namespace planning_interface
}  // namespace moveit
