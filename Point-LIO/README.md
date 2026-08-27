# Point-LIO Implementation #

## Implementation Steps ##

Download Livox ROS Driver2 and Livox SDK2
```
cd /home/chris/catkin_ws/src
git clone https://github.com/Livox-SDK/Livox-SDK2.git
git clone https://github.com/Livox-SDK/livox_ros_driver2.git

cd ..
```

### Docker Setup ###

Build the Docker Image using the following command:
```
cd /home/chris/catkin_ws
docker build -t pointlio:noetic -f Dockerfile.pointlio .
```

Build the container using the image:
```
xhost +local:root
docker run -itd \
  --name pointlio_noetic \
  --net=host \
  --ipc=host \
  --privileged \
  --device /dev/dri \
  -e DISPLAY=$DISPLAY \
  -e QT_X11_NO_MITSHM=1 \
  -e LIBGL_ALWAYS_SOFTWARE=1 \
  -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
  -v /home/chris/catkin_ws:/root/catkin_ws \
  -v /home/chris/rosbags:/root/rosbags \
  pointlio:noetic
```

To attach a terminal to the Docker container, run:
```
docker exec -it pointlio_noetic bash
```
### Workspace Setup ###
Inside the container, run the following commands:
```
source /opt/ros/noetic/setup.bash

cd /root/catkin_ws/src/Livox-SDK2
mkdir -p build
cd build
cmake .. && make -j$(nproc)
make install

cd /root/catkin_ws
catkin_make -j$(nproc)
source devel/setup.bash
```

### Mapping Steps ###
