# LIO-SAM Implementation #

## Implementation Steps ##

### Docker Setup ###
Docker files provided in ```/docker``` folder. To build the docker image from the dockerfile, run these commands in your terminal:

```
cd ~/catkin_ws/docker
docker build -t liosam:noetic -f Dockerfile .
```

Build the docker container from the image using:
```
cd ~/catkin_ws
xhost +local:root
docker run -it \
  --name liosam_mid360_noetic \
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
  liosam:noetic
```

### Workspace Setup ###
To build the workspace, enter the container and run the following commands:
```
source /opt/ros/noetic/setup.bash
cd /root/catkin_ws
catkin_make
source /root/catkin_ws/devel/setup.bash
```

## Mapping using LIO-SAM ##
Once the workspace is built, open a total of 3 terminals and attach them to the container using the ```docker exec -it <docker-container-name> bash``` command. Source the environment in each terminal using
```
source /opt/ros/noetic/setup.bash &&
source /root/catkin_ws/devel/setup.bash
```
The steps to implement LIO-SAM mapping after environment sourcing in each terminal is done is provided below.

### Terminal A ###
```
roscore
```

### Terminal B ###
```
roslaunch lio_sam run6axis.launch
```

### Terminal C ###
```
rosbag play --clock /root/rosbags/input/mid360/yeyu_livox.bag
```
