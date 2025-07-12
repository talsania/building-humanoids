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

/* Author: Krishang Talsania - Adapted for Pinocchio */

#include <moveit/kris_kinematics_plugin/kris_kinematics_plugin.h>
#include <pluginlib/class_list_macros.hpp>

#include <tf2_eigen/tf2_eigen.hpp>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_state/conversions.h>
#include <pinocchio/parsers/urdf.hpp>
#include <pinocchio/algorithm/model.hpp>

namespace kris_kinematics_plugin
{
static rclcpp::Logger LOGGER = rclcpp::get_logger("moveit_kris_kinematics_plugin.kris_kinematics_plugin");

rclcpp::Clock KrisKinematicsPlugin::steady_clock_{ RCL_STEADY_TIME };

KrisKinematicsPlugin::KrisKinematicsPlugin() : initialized_(false)
{
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

bool KrisKinematicsPlugin::checkConsistency(const Eigen::VectorXd& seed_state,
                                           const std::vector<double>& consistency_limits,
                                           const Eigen::VectorXd& solution) const
{
  for (std::size_t i = 0; i < dimension_; ++i)
    if (fabs(seed_state(i) - solution(i)) > consistency_limits[i])
      return false;
  return true;
}

void KrisKinematicsPlugin::getJointWeights()
{
  // Initialize with equal weights
  joint_weights_.resize(dimension_, 1.0);
  
  // Could add parameter loading here like in KDL plugin
  // For now, using simple equal weighting
}

bool KrisKinematicsPlugin::timedOut(const rclcpp::Time& start_time, double duration) const
{
  return ((steady_clock_.now() - start_time).seconds() >= duration);
}

bool KrisKinematicsPlugin::initialize(const rclcpp::Node::SharedPtr& /*node*/,
                                      const moveit::core::RobotModel& robot_model,
                                      const std::string& group_name,
                                      const std::string& base_frame,
                                      const std::vector<std::string>& tip_frames,
                                      double search_discretization)
{
  storeValues(robot_model, group_name, base_frame, tip_frames, search_discretization);
  joint_model_group_ = robot_model_->getJointModelGroup(group_name);
  if (!joint_model_group_)
    return false;

  if (!joint_model_group_->isChain())
  {
    RCLCPP_ERROR(LOGGER, "Group '%s' is not a chain", group_name.c_str());
    return false;
  }
  if (!joint_model_group_->isSingleDOFJoints())
  {
    RCLCPP_ERROR(LOGGER, "Group '%s' includes joints that have more than 1 DOF", group_name.c_str());
    return false;
  }

  // Get joint names
  joint_names_ = joint_model_group_->getVariableNames();
  link_names_ = joint_model_group_->getLinkModelNames();

  if (tip_frames.size() != 1)
  {
    RCLCPP_ERROR(LOGGER, "Expecting exactly one tip frame");
    return false;
  }

  // Store parameters
  base_frame_ = base_frame;
  tip_frames_ = tip_frames;
  dimension_ = joint_names_.size();

  // Load robot model into Pinocchio
  if (!loadRobotModel(robot_model))
  {
    RCLCPP_ERROR(LOGGER, "Could not load robot model");
    return false;
  }

  // Setup joint limits
  setupJointLimits();

  // Get joint weights
  getJointWeights();

  // Initialize Pinocchio data
  data_ = pinocchio::Data(model_);

  // Setup the joint state groups that we need
  state_ = std::make_shared<moveit::core::RobotState>(robot_model_);

  // Set solver parameters
  max_solver_iterations_ = 500;
  epsilon_ = 1e-5;
  orientation_vs_position_weight_ = 1.0;

  // Setup solver info
  solver_info_.joint_names = joint_names_;
  solver_info_.limits.resize(joint_names_.size());
  for (std::size_t i = 0; i < joint_names_.size(); ++i)
  {
    solver_info_.limits[i].joint_name = joint_names_[i];
    solver_info_.limits[i].has_position_limits = true;
    solver_info_.limits[i].min_position = joint_min_[i];
    solver_info_.limits[i].max_position = joint_max_[i];
  }

  initialized_ = true;
  return true;
}

bool KrisKinematicsPlugin::loadRobotModel(const moveit::core::RobotModel& robot_model)
{
  try
  {
    // Get URDF model
    const urdf::ModelInterfaceSharedPtr& urdf_model = robot_model.getURDF();
    if (!urdf_model)
    {
      RCLCPP_ERROR(LOGGER, "URDF model not available");
      return false;
    }
    
    // Extract chain joints from base to tip (like KDL's getChain)
    std::vector<std::string> chain_joint_names;
    std::vector<std::string> chain_link_names;
    if (!buildChainFromBaseToTip(robot_model, chain_joint_names, chain_link_names))
    {
      RCLCPP_ERROR(LOGGER, "Failed to build chain from base to tip");
      return false;
    }
    
    // Build chain-specific Pinocchio model (like KDL's targeted approach)
    if (!buildChainModel(urdf_model, chain_joint_names, chain_link_names))
    {
      RCLCPP_ERROR(LOGGER, "Failed to build chain-specific Pinocchio model");
      return false;
    }
    
    // Validate the chain connectivity
    if (!validateChain())
    {
      RCLCPP_ERROR(LOGGER, "Chain validation failed - no valid path from base to tip");
      return false;
    }
    
    // Find the tip frame in the chain model
    if (model_.existFrame(tip_frames_[0]))
    {
      tip_frame_id_ = model_.getFrameId(tip_frames_[0]);
      RCLCPP_DEBUG(LOGGER, "Found tip frame '%s' with ID %lu in chain model", tip_frames_[0].c_str(), tip_frame_id_);
    }
    else
    {
      RCLCPP_ERROR(LOGGER, "Could not find tip frame '%s' in chain model", tip_frames_[0].c_str());
      return false;
    }
    
    RCLCPP_INFO(LOGGER, "Built Pinocchio chain model: %zu joints, %zu links (base: %s -> tip: %s)", 
                chain_joint_names.size(), chain_link_names.size(), base_frame_.c_str(), tip_frames_[0].c_str());
    return true;
  }
  catch (const std::exception& e)
  {
    RCLCPP_ERROR(LOGGER, "Error building Pinocchio chain model: %s", e.what());
    return false;
  }
}

bool KrisKinematicsPlugin::buildChainFromBaseToTip(const moveit::core::RobotModel& robot_model, 
                                                    std::vector<std::string>& chain_joint_names,
                                                    std::vector<std::string>& chain_link_names)
{
  chain_joint_names.clear();
  chain_link_names.clear();
  
  // Extract chain like KDL's getChain() - only tip link, joints in between
  const auto* current_link = robot_model.getLinkModel(tip_frames_[0]);
  if (!current_link)
  {
    RCLCPP_ERROR(LOGGER, "Could not find tip link '%s'", tip_frames_[0].c_str());
    return false;
  }
  
  // Like KDL: only store the tip link
  chain_link_names.push_back(current_link->getName());
  
  // Traverse from tip to base, collecting only active joints (like KDL)
  while (current_link && current_link->getName() != base_frame_)
  {
    const auto* parent_joint = current_link->getParentJointModel();
    if (!parent_joint)
    {
      RCLCPP_ERROR(LOGGER, "Found link '%s' with no parent joint", current_link->getName().c_str());
      return false;
    }
    
    // Add joint to chain (at beginning to maintain base->tip order) - only active joints
    if (parent_joint->getVariableCount() > 0)
    {
      const std::vector<std::string>& var_names = parent_joint->getVariableNames();
      chain_joint_names.insert(chain_joint_names.begin(), var_names.begin(), var_names.end());
    }
    
    // Move to parent link (but don't store intermediate links like KDL)
    current_link = parent_joint->getParentLinkModel();
  }
  
  if (!current_link || current_link->getName() != base_frame_)
  {
    RCLCPP_ERROR(LOGGER, "Could not complete chain from '%s' to '%s'", base_frame_.c_str(), tip_frames_[0].c_str());
    return false;
  }
  
  RCLCPP_INFO(LOGGER, "Built kinematic chain (KDL-style): %zu joints, %zu links (base: %s -> tip: %s)", 
              chain_joint_names.size(), chain_link_names.size(), base_frame_.c_str(), tip_frames_[0].c_str());
  
  return !chain_joint_names.empty();
}

bool KrisKinematicsPlugin::buildChainModel(const urdf::ModelInterfaceSharedPtr& urdf_model,
                                           const std::vector<std::string>& chain_joint_names,
                                           const std::vector<std::string>& chain_link_names)
{
  // Build full model first, then extract chain (future optimization: build only chain directly)
  pinocchio::urdf::buildModel(urdf_model, model_);
  
  // For now, use full model but validate it contains our chain
  // Future enhancement: Use pinocchio::buildReducedModel with chain joints
  
  // Verify all chain joints exist in model
  for (const std::string& joint_name : chain_joint_names)
  {
    if (!model_.existJointName(joint_name))
    {
      RCLCPP_ERROR(LOGGER, "Chain joint '%s' not found in Pinocchio model", joint_name.c_str());
      return false;
    }
  }
  
  // Verify chain links exist as frames
  for (const std::string& link_name : chain_link_names)
  {
    if (!model_.existFrame(link_name))
    {
      RCLCPP_WARN(LOGGER, "Chain link '%s' not found as frame in Pinocchio model", link_name.c_str());
    }
  }
  
  RCLCPP_INFO(LOGGER, "Chain model validation: %d total joints, %zu chain joints", 
              model_.njoints - 1, chain_joint_names.size());
  
  return true;
}

bool KrisKinematicsPlugin::validateChain()
{
  if (!model_.existFrame(tip_frames_[0]))
  {
    RCLCPP_ERROR(LOGGER, "Tip frame '%s' not found in Pinocchio model", tip_frames_[0].c_str());
    return false;
  }
  
  if (!model_.existFrame(base_frame_))
  {
    RCLCPP_DEBUG(LOGGER, "Base frame '%s' treated as root", base_frame_.c_str());
  }
  
  RCLCPP_DEBUG(LOGGER, "Chain validation successful: %s -> %s", 
               base_frame_.c_str(), tip_frames_[0].c_str());
  
  return true;
}

void KrisKinematicsPlugin::setupJointLimits()
{
  joint_min_.resize(dimension_);
  joint_max_.resize(dimension_);
  
  const std::vector<const moveit::core::JointModel*>& joint_models = joint_model_group_->getJointModels();
  
  for (std::size_t i = 0; i < joint_models.size(); ++i)
  {
    const moveit::core::JointModel::Bounds& bounds = joint_models[i]->getVariableBounds();
    if (bounds.size() == 1)
    {
      joint_min_[i] = bounds[0].min_position_;
      joint_max_[i] = bounds[0].max_position_;
    }
    else
    {
      joint_min_[i] = -M_PI;
      joint_max_[i] = M_PI;
    }
  }
}

void KrisKinematicsPlugin::clipToJointLimits(const Eigen::VectorXd& q, Eigen::VectorXd& q_delta, Eigen::ArrayXd& weighting) const
{
  for (std::size_t i = 0; i < dimension_; ++i)
  {
    if (q[i] + q_delta[i] > joint_max_[i])
    {
      q_delta[i] = joint_max_[i] - q[i];
      weighting[i] = 0.0;
    }
    else if (q[i] + q_delta[i] < joint_min_[i])
    {
      q_delta[i] = joint_min_[i] - q[i];
      weighting[i] = 0.0;
    }
    else
    {
      weighting[i] = 1.0;
    }
  }
}

// Core IK solver - equivalent to KDL's CartToJnt
int KrisKinematicsPlugin::CartToJnt(const Eigen::VectorXd& q_init, const pinocchio::SE3& p_in,
                                    Eigen::VectorXd& q_out, const unsigned int max_iter,
                                    const Eigen::VectorXd& joint_weights,
                                    const Twist& cartesian_weights) const
{
  q_out = q_init;
  
  // Ensure proper size for Pinocchio model
  Eigen::VectorXd q = Eigen::VectorXd::Zero(model_.nq);
  q.tail(dimension_) = q_init;
  
  for (unsigned int i = 0; i < max_iter; ++i)
  {
    // Compute forward kinematics
    pinocchio::forwardKinematics(model_, data_, q);
    pinocchio::updateFramePlacements(model_, data_);
    
    // Get current end-effector pose
    pinocchio::SE3 current_pose = data_.oMf[tip_frame_id_];
    
    // Compute pose error
    pinocchio::SE3 pose_error = current_pose.inverse() * p_in;
    
    // Convert to 6D error vector
    Eigen::VectorXd error(6);
    error.head<3>() = pose_error.translation();
    error.tail<3>() = pinocchio::log3(pose_error.rotation());
    
    // Apply cartesian weights
    for (int j = 0; j < 6; ++j)
      error[j] *= cartesian_weights[j];
    
    // Check convergence
    if (error.norm() < epsilon_)
    {
      q_out = q.tail(dimension_);
      return 0; // Success
    }
    
    // Compute Jacobian
    Eigen::MatrixXd jacobian = Eigen::MatrixXd::Zero(6, model_.nv);
    pinocchio::computeFrameJacobian(model_, data_, q, tip_frame_id_, 
                                    pinocchio::LOCAL_WORLD_ALIGNED, jacobian);
    
    // Extract relevant columns
    Eigen::MatrixXd J = jacobian.rightCols(dimension_);
    
    // Apply joint weights
    for (std::size_t j = 0; j < dimension_; ++j)
      J.col(j) *= joint_weights[j];
    
    // Solve for joint increment using damped least squares
    double damping = 1e-6;
    Eigen::MatrixXd JJt = J * J.transpose() + damping * Eigen::MatrixXd::Identity(6, 6);
    Eigen::VectorXd dq = J.transpose() * JJt.ldlt().solve(error);
    
    // Apply joint limits
    Eigen::ArrayXd weighting(dimension_);
    clipToJointLimits(q.tail(dimension_), dq, weighting);
    
    // Update joint positions
    q.tail(dimension_) += dq;
  }
  
  // Max iterations reached
  q_out = q.tail(dimension_);
  return -1; // Failed to converge
}

bool KrisKinematicsPlugin::getPositionIK(const geometry_msgs::msg::Pose& ik_pose,
                                          const std::vector<double>& ik_seed_state,
                                          std::vector<double>& solution,
                                          moveit_msgs::msg::MoveItErrorCodes& error_code,
                                          const kinematics::KinematicsQueryOptions& options) const
{
  const IKCallbackFn solution_callback = IKCallbackFn();
  std::vector<double> consistency_limits;
  return searchPositionIK(ik_pose, ik_seed_state, 0.1, consistency_limits, solution, solution_callback, error_code, options);
}

bool KrisKinematicsPlugin::searchPositionIK(const geometry_msgs::msg::Pose& ik_pose,
                                             const std::vector<double>& ik_seed_state,
                                             double timeout,
                                             std::vector<double>& solution,
                                             moveit_msgs::msg::MoveItErrorCodes& error_code,
                                             const kinematics::KinematicsQueryOptions& options) const
{
  const IKCallbackFn solution_callback = IKCallbackFn();
  std::vector<double> consistency_limits;
  return searchPositionIK(ik_pose, ik_seed_state, timeout, consistency_limits, solution, solution_callback, error_code, options);
}

bool KrisKinematicsPlugin::searchPositionIK(const geometry_msgs::msg::Pose& ik_pose,
                                             const std::vector<double>& ik_seed_state,
                                             double timeout,
                                             const std::vector<double>& consistency_limits,
                                             std::vector<double>& solution,
                                             moveit_msgs::msg::MoveItErrorCodes& error_code,
                                             const kinematics::KinematicsQueryOptions& options) const
{
  const IKCallbackFn solution_callback = IKCallbackFn();
  return searchPositionIK(ik_pose, ik_seed_state, timeout, consistency_limits, solution, solution_callback, error_code, options);
}

bool KrisKinematicsPlugin::searchPositionIK(const geometry_msgs::msg::Pose& ik_pose,
                                             const std::vector<double>& ik_seed_state,
                                             double timeout,
                                             std::vector<double>& solution,
                                             const IKCallbackFn& solution_callback,
                                             moveit_msgs::msg::MoveItErrorCodes& error_code,
                                             const kinematics::KinematicsQueryOptions& options) const
{
  std::vector<double> consistency_limits;
  return searchPositionIK(ik_pose, ik_seed_state, timeout, consistency_limits, solution, solution_callback, error_code, options);
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
  if (!initialized_)
  {
    RCLCPP_ERROR(LOGGER, "kinematics not active");
    error_code.val = moveit_msgs::msg::MoveItErrorCodes::PLANNING_FAILED;
    return false;
  }

  if (ik_seed_state.size() != dimension_)
  {
    RCLCPP_ERROR(LOGGER, "Seed state must have size %d instead of size %zu", dimension_, ik_seed_state.size());
    error_code.val = moveit_msgs::msg::MoveItErrorCodes::PLANNING_FAILED;
    return false;
  }

  if (!consistency_limits.empty() && consistency_limits.size() != dimension_)
  {
    RCLCPP_ERROR(LOGGER, "Consistency limits must have size %d instead of size %zu", dimension_, consistency_limits.size());
    error_code.val = moveit_msgs::msg::MoveItErrorCodes::PLANNING_FAILED;
    return false;
  }

  // Convert target pose to Pinocchio SE3
  pinocchio::SE3 target_pose = poseToSE3(ik_pose);
  
  // Setup joint weights
  Eigen::VectorXd joint_weights_eigen = Eigen::Map<const Eigen::VectorXd>(joint_weights_.data(), joint_weights_.size());
  
  // Setup cartesian weights
  Twist cartesian_weights;
  cartesian_weights.setOnes();
  if (options.return_approximate_solution)
  {
    cartesian_weights.tail<3>() *= orientation_vs_position_weight_;
  }

  rclcpp::Time start_time = steady_clock_.now();
  
  // Try with seed state first
  Eigen::VectorXd seed = vectorToEigen(ik_seed_state);
  Eigen::VectorXd q_out;
  
  int ik_valid = CartToJnt(seed, target_pose, q_out, max_solver_iterations_, joint_weights_eigen, cartesian_weights);
  
  if (ik_valid >= 0)
  {
    solution = eigenToVector(q_out);
    
    // Check consistency limits
    if (!consistency_limits.empty())
    {
      if (!checkConsistency(seed, consistency_limits, q_out))
      {
        ik_valid = -1;
      }
    }
    
    if (ik_valid >= 0)
    {
      // Check solution callback
      if (solution_callback)
      {
        solution_callback(ik_pose, solution, error_code);
        if (error_code.val == moveit_msgs::msg::MoveItErrorCodes::SUCCESS)
        {
          return true;
        }
      }
      else
      {
        error_code.val = moveit_msgs::msg::MoveItErrorCodes::SUCCESS;
        return true;
      }
    }
  }

  // If seed state failed, try random sampling
  if (timeout > 0.0)
  {
    Eigen::VectorXd jnt_pos_in(dimension_);
    Eigen::VectorXd jnt_pos_out(dimension_);
    
    while (!timedOut(start_time, timeout))
    {
      if (consistency_limits.empty())
      {
        getRandomConfiguration(jnt_pos_in);
      }
      else
      {
        getRandomConfiguration(seed, consistency_limits, jnt_pos_in);
      }
      
      ik_valid = CartToJnt(jnt_pos_in, target_pose, jnt_pos_out, max_solver_iterations_, joint_weights_eigen, cartesian_weights);
      
      if (ik_valid >= 0)
      {
        solution = eigenToVector(jnt_pos_out);
        
        if (solution_callback)
        {
          solution_callback(ik_pose, solution, error_code);
          if (error_code.val == moveit_msgs::msg::MoveItErrorCodes::SUCCESS)
          {
            return true;
          }
        }
        else
        {
          error_code.val = moveit_msgs::msg::MoveItErrorCodes::SUCCESS;
          return true;
        }
      }
    }
  }

  error_code.val = moveit_msgs::msg::MoveItErrorCodes::NO_IK_SOLUTION;
  return false;
}

bool KrisKinematicsPlugin::getPositionFK(const std::vector<std::string>& link_names,
                                          const std::vector<double>& joint_angles,
                                          std::vector<geometry_msgs::msg::Pose>& poses) const
{
  if (!initialized_)
  {
    RCLCPP_ERROR(LOGGER, "kinematics not active");
    return false;
  }

  if (joint_angles.size() != dimension_)
  {
    RCLCPP_ERROR(LOGGER, "Joint angles must have size %d instead of size %zu", dimension_, joint_angles.size());
    return false;
  }

  // Convert joint angles to Pinocchio
  Eigen::VectorXd q = Eigen::VectorXd::Zero(model_.nq);
  q.tail(dimension_) = vectorToEigen(joint_angles);

  // Compute forward kinematics
  pinocchio::forwardKinematics(model_, data_, q);
  pinocchio::updateFramePlacements(model_, data_);

  poses.resize(link_names.size());
  
  for (std::size_t i = 0; i < link_names.size(); ++i)
  {
    if (link_names[i] == tip_frames_[0])
    {
      poses[i] = se3ToPose(data_.oMf[tip_frame_id_]);
    }
    else
    {
      // For other links, return identity (simplified)
      poses[i].position.x = poses[i].position.y = poses[i].position.z = 0.0;
      poses[i].orientation.x = poses[i].orientation.y = poses[i].orientation.z = 0.0;
      poses[i].orientation.w = 1.0;
    }
  }

  return true;
}

// Utility functions
Eigen::VectorXd KrisKinematicsPlugin::vectorToEigen(const std::vector<double>& vec) const
{
  return Eigen::Map<const Eigen::VectorXd>(vec.data(), vec.size());
}

std::vector<double> KrisKinematicsPlugin::eigenToVector(const Eigen::VectorXd& vec) const
{
  return std::vector<double>(vec.data(), vec.data() + vec.size());
}

geometry_msgs::msg::Pose KrisKinematicsPlugin::se3ToPose(const pinocchio::SE3& transform) const
{
  geometry_msgs::msg::Pose pose;
  
  pose.position.x = transform.translation().x();
  pose.position.y = transform.translation().y();
  pose.position.z = transform.translation().z();
  
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

const std::vector<std::string>& KrisKinematicsPlugin::getJointNames() const
{
  return joint_names_;
}

const std::vector<std::string>& KrisKinematicsPlugin::getLinkNames() const
{
  return link_names_;
}

}  // namespace kris_kinematics_plugin

PLUGINLIB_EXPORT_CLASS(kris_kinematics_plugin::KrisKinematicsPlugin, kinematics::KinematicsBase)