xhost +local:root

docker run -it \
  --name fast_lio2_test \
  --net=host --ipc=host --privileged \
  -e DISPLAY=$DISPLAY \
  -e QT_X11_NO_MITSHM=1 \
  -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
  -v /home/chris/catkin_ws:/root/catkin_ws \
  -v /home/chris/rosbags:/root/rosbags \
  fastlio2_noetic_mid360