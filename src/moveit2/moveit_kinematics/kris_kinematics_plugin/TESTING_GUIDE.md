# Kris Kinematics Plugin Testing Guide

This guide will help you test the Pinocchio-based kinematics plugin step by step before integrating it into your MoveIt configuration.

## Step 1: Install Dependencies

First, make sure you have Pinocchio installed:
```bash
sudo apt install ros-humble-pinocchio
```

## Step 2: Test Jacobian Computation (Standalone)

### Test with your robot URDF:
```bash
# Navigate to the plugin directory
cd /home/kptal/humanoid_ws/src/moveit2/moveit_kinematics/kris_kinematics_plugin

# Run the Jacobian test
./test_jacobian.sh /path/to/your/robot.urdf end_effector_frame_name
```

### Example with common robot URDFs:
```bash
# If you have a Panda robot URDF
./test_jacobian.sh /opt/ros/humble/share/moveit_resources_panda_description/urdf/panda.urdf panda_hand

# If you have a UR5 robot URDF  
./test_jacobian.sh /path/to/ur5.urdf tool0

# For your custom robot, replace with your URDF path and end-effector frame name
./test_jacobian.sh /path/to/your/robot.urdf your_end_effector_frame
```

### What the test checks:
1. **URDF Loading**: Verifies Pinocchio can parse your robot URDF
2. **Joint/Frame Discovery**: Lists all available joints and frames
3. **Jacobian Computation**: Computes analytical Jacobian using Pinocchio
4. **Numerical Validation**: Compares analytical vs numerical Jacobian
5. **Different Configurations**: Tests with zero and non-zero joint angles

## Step 3: Test Forward Kinematics

Create a simple FK test:
```bash
# Build the main plugin with colcon (from workspace root)
cd /home/kptal/humanoid_ws
colcon build --packages-select moveit_kinematics --allow-overriding moveit_kinematics

# Source the workspace
source install/setup.bash
```

## Step 4: Test with MoveIt (Before Full Integration)

### 4.1 Create a test configuration file:
```yaml
# Create test_kinematics.yaml
arm:
  kinematics_solver: kris_kinematics_plugin/KrisKinematicsPlugin
  kinematics_solver_search_resolution: 0.005
  kinematics_solver_timeout: 0.05
  kinematics_solver_attempts: 3
```

### 4.2 Test the plugin loads correctly:
```bash
# Test plugin loading
ros2 pkg list | grep kris_kinematics_plugin
```

## Step 5: Integration into kris_moveit_config

Once all tests pass, update your kinematics.yaml:

### Current (KDL):
```yaml
your_arm_group:
  kinematics_solver: kdl_kinematics_plugin/KDLKinematicsPlugin
  kinematics_solver_search_resolution: 0.005
  kinematics_solver_timeout: 0.05
```

### New (Pinocchio):
```yaml
your_arm_group:
  kinematics_solver: kris_kinematics_plugin/KrisKinematicsPlugin
  kinematics_solver_search_resolution: 0.005
  kinematics_solver_timeout: 0.05
```

## Step 6: Verify Integration

### 6.1 Test MoveIt demo:
```bash
# Launch your MoveIt demo
ros2 launch kris_moveit_config demo.launch.py
```

### 6.2 Check for errors:
- Look for plugin loading messages
- Verify no Jacobian computation errors
- Test motion planning in RViz

## Troubleshooting

### Common Issues:

1. **Pinocchio not found**: Install with `sudo apt install ros-humble-pinocchio`
2. **Frame not found**: Check your URDF for correct frame names
3. **Plugin not loading**: Ensure the plugin XML is correctly exported
4. **Jacobian dimensions mismatch**: Verify your robot's DOF matches expectations

### Debug Commands:
```bash
# Check available frames in your URDF
rostopic echo /robot_description | grep -i frame

# List available kinematics plugins
ros2 pkg list | grep kinematics

# Check plugin registration
ros2 plugin list | grep kris_kinematics
```

## Expected Test Results

### Jacobian Test Output:
```
=== Pinocchio Jacobian Tester ===
Loading URDF from: /path/to/robot.urdf
Model loaded successfully!
Number of joints: X
Number of DOF: Y
Found frame 'end_effector' with ID: Z
Jacobian computed successfully!
Jacobian dimensions: 6xY
Max absolute difference: < 1e-6
Test result: PASSED
```

### Success Criteria:
- ✅ URDF loads without errors
- ✅ Target frame is found
- ✅ Jacobian dimensions are correct (6 x num_joints)
- ✅ Numerical vs analytical test passes (error < 1e-3)
- ✅ No NaN or infinite values in Jacobian
- ✅ Jacobian norm > 0 (not all zeros)

Once all tests pass, you can confidently replace KDL with your Pinocchio-based plugin!