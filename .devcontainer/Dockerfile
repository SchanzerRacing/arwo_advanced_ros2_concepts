FROM osrf/ros:humble-desktop-full

ARG USERNAME=rosdev
ARG UID=1000
ARG GID=$UID

# Install some dependencies packages
RUN apt update -q \
    && apt upgrade -q -y \
    && apt install -y --no-install-recommends \
    software-properties-common \
    python3-pip \
    xauth \
    ros-humble-rqt \
    ros-humble-rqt-common-plugins \
    ros-humble-nav2-lifecycle-manager \
    ros-humble-image-publisher \
    python3-bloom \
    python3-rosdep \
    fakeroot \
    debhelper \
    dh-python \
    && apt clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Create and switch to user
RUN groupadd -g $GID $USERNAME \
    && useradd -lm -u $UID -g $USERNAME -s /bin/bash $USERNAME \
    && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers
USER $USERNAME

# Create workspace so that user own this directory
RUN mkdir -p /home/$USERNAME/ros2_ws/src
WORKDIR /home/$USERNAME/ros2_ws

# Setup entrypoint
COPY ./ros_entrypoint.sh /
RUN sudo chmod +x /ros_entrypoint.sh
ENTRYPOINT ["/ros_entrypoint.sh"]
CMD ["bash"]
