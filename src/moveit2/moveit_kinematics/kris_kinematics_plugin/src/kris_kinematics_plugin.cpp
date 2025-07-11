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

#include <moveit/kris_kinematics_plugin/kris_kinematics_plugin.h>
#include <pluginlib/class_list_macros.hpp>

#include <tf2_eigen/tf2_eigen.hpp>
#include <tf2_kdl/tf2_kdl.hpp>
#include <sstream>
#include <tinyxml.h>

namespace kris_kinematics_plugin
{
static rclcpp::Logger LOGGER = rclcpp::get_logger("moveit_kris_kinematics_plugin.kris_kinematics_plugin");

rclcpp::Clock KrisKinematicsPlugin::steady_clock_{ RCL_STEADY_TIME };

KrisKinematicsPlugin::KrisKinematicsPlugin() : initialized_(false)
{
  max_solver_iterations_ = 500;
  epsilon_ = 1e-5;
  orientation_vs_position_weight_ = 1.0;
}

bool KrisKinematicsPlugin::initialize(const rclcpp::Node::SharedPtr& /*node*/,
                                      const moveit::core::RobotModel& robot_model,
                                      const std::string& group_name,
                                      const std::string& base_frame,
                                      const std::vector<std::string>& tip_frames,
                                      double search_discretization)
{
  storeValues(robot_model, group_name, base_frame, tip_frames, search_discretization);
  
  joint_model_group_ = robot_model.getJointModelGroup(group_name);
  if (!joint_model_group_)
  {
    RCLCPP_ERROR(LOGGER, "Could not find joint model group: %s", group_name.c_str());
    return false;
  }

  if (tip_frames.empty())
  {
    RCLCPP_ERROR(LOGGER, "No tip frame specified");
    return false;
  }

  // Store base frame and tip frames
  base_frame_ = base_frame;
  tip_frames_ = tip_frames;
  
  // Get joint names
  joint_names_ = joint_model_group_->getVariableNames();
  
  if (joint_names_.empty())
  {
    RCLCPP_ERROR(LOGGER, "No joints found in group: %s", group_name.c_str());
    return false;
  }
  
  dimension_ = joint_names_.size();

  // Load robot model into Pinocchio
  if (!loadRobotModel(robot_model))
  {
    RCLCPP_ERROR(LOGGER, "Failed to load robot model into Pinocchio");
    return false;
  }

  // Setup joint limits
  setupJointLimits();

  // Initialize Pinocchio data
  data_ = pinocchio::Data(model_);

  // Get joint weights
  getJointWeights();

  // Create robot state
  state_ = std::make_shared<moveit::core::RobotState>(robot_model_);

  // Setup solver info
  solver_info_.joint_names = joint_names_;
  solver_info_.limits.resize(joint_names_.size());
  for (size_t i = 0; i < joint_names_.size(); ++i)
  {
    solver_info_.limits[i].joint_name = joint_names_[i];
    solver_info_.limits[i].has_position_limits = true;
    solver_info_.limits[i].min_position = joint_position_lower_limits_[i];
    solver_info_.limits[i].max_position = joint_position_upper_limits_[i];
    solver_info_.limits[i].has_velocity_limits = true;
    solver_info_.limits[i].max_velocity = joint_velocity_limits_[i];
    solver_info_.limits[i].has_acceleration_limits = true;
    solver_info_.limits[i].max_acceleration = joint_acceleration_limits_[i];
  }

  initialized_ = true;
  RCLCPP_INFO(LOGGER, "KrisKinematicsPlugin initialized successfully");
  RCLCPP_INFO(LOGGER, "Group: %s, Base: %s, Tip: %s", 
              group_name.c_str(), base_frame.c_str(), tip_frames[0].c_str());
  RCLCPP_INFO(LOGGER, "Number of joints: %zu", joint_names_.size());
  
  return true;
}

bool KrisKinematicsPlugin::loadRobotModel(const moveit::core::RobotModel& robot_model)
{
  try
  {
    // For now, we'll use a simplified approach - the URDF should be available as a parameter
    // This is a temporary workaround until we fix the URDF extraction from robot_model
    
    // Try to get URDF from robot description parameter
    std::string urdf_param = "/robot_description";
    if (rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("temp_node"))
    {
      if (node->has_parameter(urdf_param))
      {
        std::string urdf_string = node->get_parameter(urdf_param).as_string();
        pinocchio::urdf::buildModelFromXML(urdf_string, model_);
      }
      else
      {
        // Fallback - build a minimal model for testing
        RCLCPP_WARN(LOGGER, "Could not find robot_description parameter, using minimal model");
        // Create a minimal model for testing
        model_ = pinocchio::Model();
        return true;
      }
    }
    else
    {
      throw std::runtime_error("Failed to create temporary node for URDF access");
    }
    
    // Get link names
    const std::vector<const moveit::core::LinkModel*>& links = joint_model_group_->getLinkModels();
    link_names_.clear();
    for (const auto* link : links)
    {
      link_names_.push_back(link->getName());
    }

    // Find tip frame in Pinocchio model
    if (!tip_frames_.empty())
    {
      std::string tip_frame = tip_frames_[0];
      if (model_.existFrame(tip_frame))
      {
        tip_frame_id_ = model_.getFrameId(tip_frame);
      }
      else
      {
        RCLCPP_WARN(LOGGER, "Tip frame %s not found in Pinocchio model", tip_frame.c_str());
        // Try to find by searching frames
        for (size_t i = 0; i < model_.frames.size(); ++i)
        {
          if (model_.frames[i].name == tip_frame)
          {
            tip_frame_id_ = i;
            break;
          }
        }
      }
    }

    RCLCPP_INFO(LOGGER, "Pinocchio model loaded: %d joints, %zu frames", 
                model_.njoints, model_.frames.size());
    
    return true;
  }
  catch (const std::exception& e)
  {
    RCLCPP_ERROR(LOGGER, "Error loading robot model: %s", e.what());
    return false;
  }
}

void KrisKinematicsPlugin::setupJointLimits()
{
  const std::vector<const moveit::core::JointModel*>& joint_models = joint_model_group_->getJointModels();
  
  joint_position_lower_limits_.clear();
  joint_position_upper_limits_.clear();
  joint_velocity_limits_.clear();
  joint_acceleration_limits_.clear();

  for (const auto* joint_model : joint_models)
  {
    const moveit::core::JointModel::Bounds& bounds = joint_model->getVariableBounds();
    
    for (const auto& bound : bounds)
    {
      joint_position_lower_limits_.push_back(bound.min_position_);
      joint_position_upper_limits_.push_back(bound.max_position_);
      joint_velocity_limits_.push_back(bound.max_velocity_);
      joint_acceleration_limits_.push_back(bound.max_acceleration_);
    }
  }
}

void KrisKinematicsPlugin::getJointWeights()
{
  // For now, use equal weights for all joints
  joint_weights_.resize(joint_names_.size(), 1.0);
  
  // Could add parameter loading here like in KDL plugin
  // if (lookupParam(node_, "joint_weights.weights", weights, weights))
  // {
  //   ...
  // }
}

bool KrisKinematicsPlugin::getJacobian(const std::vector<double>& joint_angles,
                                       Eigen::MatrixXd& jacobian) const
{
  if (joint_angles.size() != joint_names_.size())
  {
    RCLCPP_ERROR(LOGGER, "Joint angles size mismatch: %zu vs %zu", 
                 joint_angles.size(), joint_names_.size());
    return false;
  }

  try
  {
    // Convert joint angles to Eigen
    Eigen::VectorXd q = vectorToEigen(joint_angles);
    
    // Make sure we have the right size
    if (q.size() != model_.nq)
    {
      // Pad with zeros if needed (for floating base, etc.)
      Eigen::VectorXd q_full = Eigen::VectorXd::Zero(model_.nq);
      q_full.tail(q.size()) = q;
      q = q_full;
    }

    // Compute forward kinematics
    pinocchio::forwardKinematics(model_, data_, q);
    
    // Compute Jacobian
    jacobian = Eigen::MatrixXd::Zero(6, model_.nv);
    
    if (tip_frame_id_ < model_.frames.size())
    {
      // Compute Jacobian for the tip frame
      pinocchio::computeFrameJacobian(model_, data_, q, tip_frame_id_, 
                                      pinocchio::LOCAL_WORLD_ALIGNED, jacobian);
    }
    else
    {
      // Use end-effector joint if tip frame not found
      pinocchio::computeJointJacobian(model_, data_, q, model_.njoints - 1, jacobian);
    }

    // Extract the relevant columns (for the actual joints we're controlling)
    jacobian = jacobian.rightCols(joint_angles.size());

    RCLCPP_DEBUG(LOGGER, "Jacobian computed: %dx%d", 
                 (int)jacobian.rows(), (int)jacobian.cols());
    
    return true;
  }
  catch (const std::exception& e)
  {
    RCLCPP_ERROR(LOGGER, "Error computing Jacobian: %s", e.what());
    return false;
  }
}

bool KrisKinematicsPlugin::getJacobianAtTipFrame(const std::vector<double>& joint_angles,
                                                 const std::string& tip_frame,
                                                 Eigen::MatrixXd& jacobian) const
{
  // Find the frame ID
  pinocchio::FrameIndex frame_id;
  if (model_.existFrame(tip_frame))
  {
    frame_id = model_.getFrameId(tip_frame);
  }
  else
  {
    RCLCPP_ERROR(LOGGER, "Frame %s not found in model", tip_frame.c_str());
    return false;
  }

  try
  {
    // Convert joint angles to Eigen
    Eigen::VectorXd q = vectorToEigen(joint_angles);
    
    // Make sure we have the right size
    if (q.size() != model_.nq)
    {
      Eigen::VectorXd q_full = Eigen::VectorXd::Zero(model_.nq);
      q_full.tail(q.size()) = q;
      q = q_full;
    }

    // Compute forward kinematics
    pinocchio::forwardKinematics(model_, data_, q);
    
    // Compute Jacobian for the specified frame
    jacobian = Eigen::MatrixXd::Zero(6, model_.nv);
    pinocchio::computeFrameJacobian(model_, data_, q, frame_id, 
                                    pinocchio::LOCAL_WORLD_ALIGNED, jacobian);

    // Extract the relevant columns
    jacobian = jacobian.rightCols(joint_angles.size());

    return true;
  }
  catch (const std::exception& e)
  {
    RCLCPP_ERROR(LOGGER, "Error computing frame Jacobian: %s", e.what());
    return false;
  }
}

Eigen::VectorXd KrisKinematicsPlugin::vectorToEigen(const std::vector<double>& vec) const
{
  Eigen::VectorXd eigen_vec(vec.size());
  for (size_t i = 0; i < vec.size(); ++i)
  {
    eigen_vec[i] = vec[i];
  }
  return eigen_vec;
}

std::vector<double> KrisKinematicsPlugin::eigenToVector(const Eigen::VectorXd& vec) const
{
  std::vector<double> std_vec(vec.size());
  for (int i = 0; i < vec.size(); ++i)
  {
    std_vec[i] = vec[i];
  }
  return std_vec;
}

geometry_msgs::msg::Pose KrisKinematicsPlugin::se3ToPose(const pinocchio::SE3& transform) const
{
  geometry_msgs::msg::Pose pose;
  
  // Position
  pose.position.x = transform.translation().x();
  pose.position.y = transform.translation().y();
  pose.position.z = transform.translation().z();
  
  // Orientation
  Eigen::Quaterniond quat(transform.rotation());
  pose.orientation.x = quat.x();
  pose.orientation.y = quat.y();
  pose.orientation.z = quat.z();
  pose.orientation.w = quat.w();
  
  return pose;
}

pinocchio::SE3 KrisKinematicsPlugin::poseToSE3(const geometry_msgs::msg::Pose& pose) const
{
  Eigen::Vector3d translation(pose.position.x, pose.position.y, pose.position.z);
  Eigen::Quaterniond rotation(pose.orientation.w, pose.orientation.x, 
                             pose.orientation.y, pose.orientation.z);
  
  return pinocchio::SE3(rotation.toRotationMatrix(), translation);
}

bool KrisKinematicsPlugin::getPositionFK(const std::vector<std::string>& link_names,
                                          const std::vector<double>& joint_angles,
                                          std::vector<geometry_msgs::msg::Pose>& poses) const
{
  if (joint_angles.size() != joint_names_.size())
  {
    return false;
  }

  try
  {
    // Convert joint angles to Eigen
    Eigen::VectorXd q = vectorToEigen(joint_angles);
    
    // Make sure we have the right size
    if (q.size() != model_.nq)
    {
      Eigen::VectorXd q_full = Eigen::VectorXd::Zero(model_.nq);
      q_full.tail(q.size()) = q;
      q = q_full;
    }

    // Compute forward kinematics
    pinocchio::forwardKinematics(model_, data_, q);
    pinocchio::updateFramePlacements(model_, data_);

    poses.clear();
    for (const std::string& link_name : link_names)
    {
      geometry_msgs::msg::Pose pose;
      
      if (model_.existFrame(link_name))
      {
        pinocchio::FrameIndex frame_id = model_.getFrameId(link_name);
        pinocchio::SE3 placement = data_.oMf[frame_id];
        pose = se3ToPose(placement);
      }
      else
      {
        RCLCPP_WARN(LOGGER, "Frame %s not found", link_name.c_str());
        // Return identity pose
        pose.position.x = pose.position.y = pose.position.z = 0.0;
        pose.orientation.x = pose.orientation.y = pose.orientation.z = 0.0;
        pose.orientation.w = 1.0;
      }
      
      poses.push_back(pose);
    }

    return true;
  }
  catch (const std::exception& e)
  {
    RCLCPP_ERROR(LOGGER, "Error in forward kinematics: %s", e.what());
    return false;
  }
}

// Full IK implementation using Pinocchio
bool KrisKinematicsPlugin::getPositionIK(const geometry_msgs::msg::Pose& ik_pose,
                                          const std::vector<double>& ik_seed_state,
                                          std::vector<double>& solution,
                                          moveit_msgs::msg::MoveItErrorCodes& error_code,
                                          const kinematics::KinematicsQueryOptions& options) const
{
  return solvePositionIK(ik_pose, ik_seed_state, solution, 0.05, // 50ms timeout
                         std::vector<double>(), IKCallbackFn(), error_code, options);
}

bool KrisKinematicsPlugin::searchPositionIK(const geometry_msgs::msg::Pose& ik_pose,
                                             const std::vector<double>& ik_seed_state,
                                             double timeout,
                                             std::vector<double>& solution,
                                             moveit_msgs::msg::MoveItErrorCodes& error_code,
                                             const kinematics::KinematicsQueryOptions& options) const
{
  return solvePositionIK(ik_pose, ik_seed_state, solution, timeout,
                         std::vector<double>(), IKCallbackFn(), error_code, options);
}

bool KrisKinematicsPlugin::searchPositionIK(const geometry_msgs::msg::Pose& ik_pose,
                                             const std::vector<double>& ik_seed_state,
                                             double timeout,
                                             const std::vector<double>& consistency_limits,
                                             std::vector<double>& solution,
                                             moveit_msgs::msg::MoveItErrorCodes& error_code,
                                             const kinematics::KinematicsQueryOptions& options) const
{
  return solvePositionIK(ik_pose, ik_seed_state, solution, timeout,
                         consistency_limits, IKCallbackFn(), error_code, options);
}

bool KrisKinematicsPlugin::searchPositionIK(const geometry_msgs::msg::Pose& ik_pose,
                                             const std::vector<double>& ik_seed_state,
                                             double timeout,
                                             std::vector<double>& solution,
                                             const IKCallbackFn& solution_callback,
                                             moveit_msgs::msg::MoveItErrorCodes& error_code,
                                             const kinematics::KinematicsQueryOptions& options) const
{
  return getPositionIK(ik_pose, ik_seed_state, solution, error_code, options);
}

bool KrisKinematicsPlugin::searchPositionIK(const geometry_msgs::msg::Pose& ik_pose,
                                             const std::vector<double>& ik_seed_state,
                                             double timeout,
                                             const std::vector<double>& consistency_limits,
                                             std::vector<double>& solution,
                                             const IKCallbackFn& solution_callback,
                                             moveit_msgs::msg::MoveItErrorCodes& error_code,
                                             const kinematics::KinematicsQueryOptions& options) const
{
  return getPositionIK(ik_pose, ik_seed_state, solution, error_code, options);
}

// Utility functions
bool KrisKinematicsPlugin::timedOut(const rclcpp::Time& start_time, double duration) const
{
  return (steady_clock_.now() - start_time).seconds() >= duration;
}

bool KrisKinematicsPlugin::checkConsistency(const Eigen::VectorXd& seed_state,
                                           const std::vector<double>& consistency_limits,
                                           const Eigen::VectorXd& solution) const
{
  for (std::size_t i = 0; i < dimension_; ++i)
  {
    if (fabs(seed_state(i) - solution(i)) > consistency_limits[i])
      return false;
  }
  return true;
}

void KrisKinematicsPlugin::getRandomConfiguration(Eigen::VectorXd& jnt_array) const
{
  state_->setToRandomPositions(joint_model_group_);
  state_->copyJointGroupPositions(joint_model_group_, &jnt_array[0]);
}

void KrisKinematicsPlugin::getRandomConfiguration(const Eigen::VectorXd& seed_state,
                                                 const std::vector<double>& consistency_limits,
                                                 Eigen::VectorXd& jnt_array) const
{
  joint_model_group_->getVariableRandomPositionsNearBy(state_->getRandomNumberGenerator(), &jnt_array[0],
                                                       &seed_state[0], consistency_limits);
}

// Getters
const std::vector<std::string>& KrisKinematicsPlugin::getJointNames() const
{
  return joint_names_;
}

const std::vector<std::string>& KrisKinematicsPlugin::getLinkNames() const
{
  return link_names_;
}

}  // namespace kris_kinematics_plugin

// Plugin registration
PLUGINLIB_EXPORT_CLASS(kris_kinematics_plugin::KrisKinematicsPlugin, kinematics::KinematicsBase)