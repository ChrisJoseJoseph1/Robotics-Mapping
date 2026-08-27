FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
SHELL ["/bin/bash", "-c"]

# --- Basics + ROS Noetic setup ---
RUN apt-get update && apt-get install -y --no-install-recommends \
    curl gnupg2 lsb-release ca-certificates \
    build-essential cmake git \
    python3 python3-pip \
    && rm -rf /var/lib/apt/lists/*

RUN echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros1-latest.list \
    && curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add -

RUN apt-get update && apt-get install -y --no-install-recommends \
    ros-noetic-desktop-full \
    python3-rosdep python3-catkin-tools python3-wstool \
    ros-noetic-tf ros-noetic-tf2 ros-noetic-tf2-ros \
    libeigen3-dev libpcl-dev \
    && rm -rf /var/lib/apt/lists/*

RUN rosdep init || true
RUN rosdep update

# --- Workspace location inside container ---
ENV ROS_DISTRO=noetic
RUN echo "source /opt/ros/${ROS_DISTRO}/setup.bash" >> /root/.bashrc

WORKDIR /root/catkin_ws
RUN mkdir -p /root/catkin_ws/src

# --- Install Livox-SDK2 (required by livox_ros_driver2) ---
WORKDIR /tmp
RUN git clone https://github.com/Livox-SDK/Livox-SDK2.git
RUN cd /tmp/Livox-SDK2 && mkdir -p build && cd build \
 && cmake .. \
 && make -j"$(nproc)" \
 && make install \
 && ldconfig

# --- Build livox_ros_driver2 (needed to decode your bag: livox_ros_driver2/CustomMsg) ---
WORKDIR /root/catkin_ws/src
RUN git clone https://github.com/Livox-SDK/livox_ros_driver2.git

WORKDIR /root/catkin_ws/src/livox_ros_driver2
RUN source /opt/ros/${ROS_DISTRO}/setup.bash && ./build.sh ROS1

WORKDIR /root/catkin_ws
#RUN /bin/bash -lc "source /opt/ros/${ROS_DISTRO}/setup.bash && catkin_make"

# Default: interactive shell
CMD ["bash"]
