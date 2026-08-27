### LIO-Livox Implementation
___UNFINISHED README PAGE___
Create container from image: bash ~/catkin_ws/src/docker/run_container.sh

xhost +local:docker

docker start -ai lio_livox_test

docker exec -it lio_livox_test bash

----------------------------------------------------------------------------------------
Sourcing: source /opt/ros/melodic/setup.bash && source /root/catkin_ws/devel/setup.bash
----------------------------------------------------------------------------------------

Terminal 1:
    roscore

Terminal 2:
    rosrun livox_driver2_to_driver1_bridge livox_driver2_to_driver1_bridge

Terminal 3:
    roslaunch lio_livox mid360.launch

Terminal 4:
    rosrun lio_livox_map_saver lio_livox_map_saver \
    _input_topic:=/livox_full_cloud_mapped \
    _output_pcd:=/root/rosbags/lio_livox_mid360_map.pcd \
    _voxel_leaf_size:=0.05

Terminal 5:
    rosbag play /root/dataset/input/mid360/20260417Test/April17_1.bag \
    /livox/lidar:=/livox/lidar_raw_driver2 \
    --clock
