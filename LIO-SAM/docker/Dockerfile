FROM osrf/ros:noetic-desktop-full

SHELL ["/bin/bash", "-c"]

# Basic tools + ROS deps
RUN apt-get update && apt-get install -y \
    curl \
    software-properties-common \
    git \
    python3 \
    python3-pip \
    python3-dev \
    python3-empy \
    python3-catkin-pkg \
    python3-rospkg \
    python3-nose \
    python3-setuptools \
    python3-yaml \
    python-is-python3 \
    libeigen3-dev \
    libceres-dev \
    libpcl-dev \
    libsuitesparse-dev \
    ros-noetic-navigation \
    ros-noetic-robot-localization \
    ros-noetic-robot-state-publisher \
    && rm -rf /var/lib/apt/lists/*

# GTSAM
RUN add-apt-repository -y ppa:borglab/gtsam-release-4.0 \
    && apt-get update \
    && apt-get install -y libgtsam-dev libgtsam-unstable-dev \
    && rm -rf /var/lib/apt/lists/*

# Helpful OpenGL/X11 packages
RUN apt-get update && apt-get install -y \
    mesa-utils \
    libgl1-mesa-glx \
    libgl1-mesa-dri \
    dbus-x11 \
    && rm -rf /var/lib/apt/lists/*

RUN echo "source /opt/ros/noetic/setup.bash" >> /root/.bashrc

WORKDIR /root/catkin_ws
CMD ["/bin/bash"]
