#!/usr/bin/env bash

set -e  # Exit immediately if any command fails

# 1) Check for ROS 2 installation and source it
ROS_DISTRO=humble

if [ -f "/opt/ros/${ROS_DISTRO}/setup.bash" ]; then
  source "/opt/ros/${ROS_DISTRO}/setup.bash"
  echo "[✔] Sourced /opt/ros/${ROS_DISTRO}/setup.bash"
else
  echo "[✘] Cannot find /opt/ros/${ROS_DISTRO}/setup.bash"
  echo "    Make sure ROS 2 ${ROS_DISTRO} is installed!"
  exit 1
fi

# 2) Install rosdep & colcon if not already present
echo "[✔] Installing python3-rosdep and colcon-common-extensions (if needed)..."
sudo apt update
sudo apt install -y python3-rosdep python3-colcon-common-extensions

# 3) Initialize rosdep (only once per machine)
if [ ! -f /etc/ros/rosdep/sources.list.d/20-default.list ]; then
  echo "[✔] Initializing rosdep..."
  sudo rosdep init
fi
echo "[✔] Updating rosdep database..."
rosdep update

# 4) Install any missing dependencies (system + ROS2) from package.xml in src/
echo "[✔] Installing ROS2 and system dependencies via rosdep..."
rosdep install \
  --from-paths src \
  --ignore-src \
  --rosdistro "${ROS_DISTRO}" \
  -y

echo
echo "──────────────────────────────────────"
echo "- - - ALL DEPENDENCIES INSTALLED - - -"
echo "──────────────────────────────────────"