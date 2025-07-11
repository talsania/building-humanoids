/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2012, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Adapted from kdl_kinematics_plugin for Pinocchio */

#pragma once

// ROS
#include <rclcpp/rclcpp.hpp>
#include <random_numbers/random_numbers.h>

// ROS msgs
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <moveit_msgs/srv/get_position_fk.hpp>
#include <moveit_msgs/srv/get_position_ik.hpp>
#include <moveit_msgs/msg/kinematic_solver_info.hpp>
#include <moveit_msgs/msg/move_it_error_codes.hpp>

// Pinocchio
#include <pinocchio/multibody/model.hpp>
#include <pinocchio/multibody/data.hpp>
#include <pinocchio/algorithm/joint-configuration.hpp>
#include <pinocchio/algorithm/kinematics.hpp>
#include <pinocchio/algorithm/jacobian.hpp>
#include <pinocchio/algorithm/frames.hpp>
#include <pinocchio/parsers/urdf.hpp>

// MoveIt
#include <moveit/kinematics_base/kinematics_base.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>

#include <cfloat>

namespace kris_kinematics_plugin
{
/**
 * @brief Specific implementation of kinematics using Pinocchio.
 * This version supports any kinematic chain, mimicking the KDL interface.
 */
class KrisKinematicsPlugin : public kinematics::KinematicsBase
{
public:
  /**
   *  @brief Default constructor
   */
  KrisKinematicsPlugin();

  bool
  getPositionIK(const geometry_msgs::msg::Pose& ik_pose, const std::vector<double>& ik_seed_state,
                std::vector<double>& solution, moveit_msgs::msg::MoveItErrorCodes& error_code,
                const kinematics::KinematicsQueryOptions& options = kinematics::KinematicsQueryOptions()) const override;

  bool searchPositionIK(
      const geometry_msgs::msg::Pose& ik_pose, const std::vector<double>& ik_seed_state, double timeout,
      std::vector<double>& solution, moveit_msgs::msg::MoveItErrorCodes& error_code,
      const kinematics::KinematicsQueryOptions& options = kinematics::KinematicsQueryOptions()) const override;

  bool searchPositionIK(
      const geometry_msgs::msg::Pose& ik_pose, const std::vector<double>& ik_seed_state, double timeout,
      const std::vector<double>& consistency_limits, std::vector<double>& solution,
      moveit_msgs::msg::MoveItErrorCodes& error_code,
      const kinematics::KinematicsQueryOptions& options = kinematics::KinematicsQueryOptions()) const override;

  bool searchPositionIK(
      const geometry_msgs::msg::Pose& ik_pose, const std::vector<double>& ik_seed_state, double timeout,
      std::vector<double>& solution, const IKCallbackFn& solution_callback,
      moveit_msgs::msg::MoveItErrorCodes& error_code,
      const kinematics::KinematicsQueryOptions& options = kinematics::KinematicsQueryOptions()) const override;

  bool searchPositionIK(
      const geometry_msgs::msg::Pose& ik_pose, const std::vector<double>& ik_seed_state, double timeout,
      const std::vector<double>& consistency_limits, std::vector<double>& solution,
      const IKCallbackFn& solution_callback, moveit_msgs::msg::MoveItErrorCodes& error_code,
      const kinematics::KinematicsQueryOptions& options = kinematics::KinematicsQueryOptions()) const override;

  bool getPositionFK(const std::vector<std::string>& link_names, const std::vector<double>& joint_angles,
                     std::vector<geometry_msgs::msg::Pose>& poses) const override;

  bool initialize(const rclcpp::Node::SharedPtr& node, const moveit::core::RobotModel& robot_model,
                  const std::string& group_name, const std::string& base_frame,
                  const std::vector<std::string>& tip_frames, double search_discretization) override;

  /**
   * @brief  Return all the joint names in the order they are used internally
   */
  const std::vector<std::string>& getJointNames() const override;

  /**
   * @brief  Return all the link names in the order they are represented internally
   */
  const std::vector<std::string>& getLinkNames() const override;

  /**
   * @brief  Get the Jacobian matrix for the current joint configuration
   */
  bool getJacobian(const std::vector<double>& joint_angles, Eigen::MatrixXd& jacobian) const;

  /**
   * @brief  Get the Jacobian matrix for a specific tip frame
   */
  bool getJacobianAtTipFrame(const std::vector<double>& joint_angles, const std::string& tip_frame,
                             Eigen::MatrixXd& jacobian) const;

protected:
  typedef Eigen::Matrix<double, 6, 1> Twist;

  /// Solve position IK using Pinocchio
  bool solvePositionIK(const geometry_msgs::msg::Pose& ik_pose, const std::vector<double>& ik_seed_state,
                       std::vector<double>& solution, double timeout,
                       const std::vector<double>& consistency_limits = std::vector<double>(),
                       const IKCallbackFn& solution_callback = IKCallbackFn()) const;

private:
  void getJointWeights();
  bool timedOut(const rclcpp::Time& start_time, double duration) const;

  /** @brief Check whether the solution lies within the consistency limits of the seed state
   *  @param seed_state Seed state
   *  @param consistency_limits
   *  @param solution solution configuration
   *  @return true if check succeeds
   */
  bool checkConsistency(const Eigen::VectorXd& seed_state, const std::vector<double>& consistency_limits,
                        const Eigen::VectorXd& solution) const;

  void getRandomConfiguration(Eigen::VectorXd& jnt_array) const;

  /** @brief Get a random configuration within consistency limits close to the seed state
   *  @param seed_state Seed state
   *  @param consistency_limits
   *  @param jnt_array Returned random configuration
   */
  void getRandomConfiguration(const Eigen::VectorXd& seed_state, const std::vector<double>& consistency_limits,
                              Eigen::VectorXd& jnt_array) const;

  /// Load robot model into Pinocchio
  bool loadRobotModel(const moveit::core::RobotModel& robot_model);

  /// Setup joint limits from MoveIt
  void setupJointLimits();

  /// Convert between std::vector and Eigen::VectorXd
  Eigen::VectorXd vectorToEigen(const std::vector<double>& vec) const;
  std::vector<double> eigenToVector(const Eigen::VectorXd& vec) const;

  /// Convert SE3 to geometry_msgs::Pose
  geometry_msgs::msg::Pose se3ToPose(const pinocchio::SE3& transform) const;

  /// Convert geometry_msgs::Pose to SE3
  pinocchio::SE3 poseToSE3(const geometry_msgs::msg::Pose& pose) const;

  static rclcpp::Clock steady_clock_;

  bool initialized_;  ///< Internal variable that indicates whether solver is configured and ready

  unsigned int dimension_;                             ///< Dimension of the group
  moveit_msgs::msg::KinematicSolverInfo solver_info_;  ///< Stores information for the inverse kinematics solver

  const moveit::core::JointModelGroup* joint_model_group_;
  moveit::core::RobotStatePtr state_;
  
  // Pinocchio model and data
  pinocchio::Model model_;
  mutable pinocchio::Data data_;
  
  std::vector<std::string> joint_names_;
  std::vector<std::string> link_names_;
  std::vector<double> joint_weights_;
  std::vector<double> joint_position_lower_limits_;
  std::vector<double> joint_position_upper_limits_;
  std::vector<double> joint_velocity_limits_;
  std::vector<double> joint_acceleration_limits_;
  
  pinocchio::FrameIndex tip_frame_id_;
  std::string base_frame_;
  std::vector<std::string> tip_frames_;

  int max_solver_iterations_;
  double epsilon_;
  /** weight of orientation error vs position error
   *
   * < 1.0: orientation has less importance than position
   * > 1.0: orientation has more importance than position
   * = 0.0: perform position-only IK */
  double orientation_vs_position_weight_;
};
}  // namespace kris_kinematics_plugin