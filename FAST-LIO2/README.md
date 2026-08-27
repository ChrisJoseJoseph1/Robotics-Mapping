# FAST-LIO2 Implementation #

## Implementation Steps ##
Once the container is set up, open 4 terminals and attach them to the container using ```docker exec -it {docker-container-name} bash```. Source the environment using the command given below.

### Sourcing environments ###

```
source /opt/ros/noetic/setup.bash &&
source /root/livox_ws/devel/setup.bash &&
source /root/catkin_ws/devel/setup.bash
```

Steps to implement FAST-LIO2 are given below:

### Terminal A ###
```
roscore
```

### Terminal B ###
```
roslaunch fast_lio mapping_mid360.launch
```

### Terminal C ###
```
rosrun pcl_ros pointcloud_to_pcd input:=/Laser_map _prefix:=/root/catkin_ws/src/FAST_LIO/PCD_Map/global_map_
```

### Terminal D ###
```
rosparam set use_sim_time true
rosbag play /root/rosbags/input/mid360/livoxmap.bag --clock
```

### Note ###
While running the mapping using large files, I recommend using the following launch command
```
roslaunch --sigint-timeout=480 --sigterm-timeout=480 fast_lio mapping_mid360.launch
```
as well as killing the mapping terminal using 
```
rosnode kill /laserMapping
```


## Acknowledgements ##
Original Repository: https://github.com/hku-mars/FAST_LIO
