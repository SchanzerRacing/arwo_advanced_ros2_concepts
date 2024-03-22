#!/bin/bash
# shellcheck disable=SC1090,SC1091
set -e

# setup ros2 environment
source /opt/ros/"$ROS_DISTRO"/setup.bash
colcon build
source "$HOME/ros2_ws/install/setup.bash"

# add sourcing to .bashrc
echo "source '/opt/ros/$ROS_DISTRO/setup.bash'" >> ~/.bashrc
echo "source '$HOME/ros2_ws/install/setup.bash'" >> ~/.bashrc

exec "$@"
