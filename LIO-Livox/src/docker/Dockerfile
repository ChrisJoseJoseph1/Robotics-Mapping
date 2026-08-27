FROM osrf/ros:melodic-desktop-full-bionic

ENV DEBIAN_FRONTEND=noninteractive
ENV ROS_DISTRO=melodic

SHELL ["/bin/bash", "-c"]

# ------------------------------------------------------------
# Base tools + ROS / LIO-Livox dependencies
# ------------------------------------------------------------
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    curl \
    nano \
    vim \
    lsb-release \
    gnupg2 \
    net-tools \
    iputils-ping \
    python-catkin-tools \
    python-rosdep \
    python-wstool \
    python-vcstool \
    python-pip \
    ros-melodic-rviz \
    ros-melodic-pcl-ros \
    ros-melodic-pcl-conversions \
    ros-melodic-eigen-conversions \
    ros-melodic-tf \
    ros-melodic-tf-conversions \
    ros-melodic-message-filters \
    ros-melodic-rosbag \
    ros-melodic-image-transport \
    ros-melodic-cv-bridge \
    libeigen3-dev \
    libpcl-dev \
    libopencv-dev \
    libceres-dev \
    libsuitesparse-dev \
    pcl-tools \
    && rm -rf /var/lib/apt/lists/*

# ------------------------------------------------------------
# Install Livox-SDK v1
# Required by livox_ros_driver, which original LIO-Livox uses.
# Do NOT replace this with Livox-SDK2.
# ------------------------------------------------------------
RUN cd /tmp && \
    git clone https://github.com/Livox-SDK/Livox-SDK.git && \
    cd Livox-SDK && \
    mkdir -p build && \
    cd build && \
    cmake .. && \
    make -j$(nproc) && \
    make install && \
    ldconfig && \
    rm -rf /tmp/Livox-SDK

# ------------------------------------------------------------
# Install Livox-SDK2
# Needed only because your rosbag contains livox_ros_driver2/CustomMsg.
# This is for compatibility/bridge support, not for changing LIO-Livox.
# ------------------------------------------------------------
RUN cd /tmp && \
    git clone https://github.com/Livox-SDK/Livox-SDK2.git && \
    cd Livox-SDK2 && \
    mkdir -p build && \
    cd build && \
    cmake .. && \
    make -j$(nproc) && \
    make install && \
    ldconfig && \
    rm -rf /tmp/Livox-SDK2

# ------------------------------------------------------------
# Workspace paths.
# These will be mounted from host:
#   /home/chris/catkin_ws -> /root/catkin_ws
#   /home/chris/rosbags   -> /root/rosbags
# ------------------------------------------------------------
RUN mkdir -p /root/catkin_ws/src /root/rosbags

# ------------------------------------------------------------
# Auto-source ROS and catkin workspace when opening container shell
# ------------------------------------------------------------
RUN echo "source /opt/ros/melodic/setup.bash" >> /root/.bashrc && \
    echo "if [ -f /root/catkin_ws/devel/setup.bash ]; then source /root/catkin_ws/devel/setup.bash; fi" >> /root/.bashrc

WORKDIR /root/catkin_ws

CMD ["/bin/bash"]