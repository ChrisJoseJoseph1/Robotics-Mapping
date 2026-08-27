xhost +local:docker

docker run -it \
  --name lio_livox_test \
  --net=host \
  --privileged \
  -e DISPLAY=$DISPLAY \
  -e QT_X11_NO_MITSHM=1 \
  -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
  -v /home/chris/catkin_ws:/root/catkin_ws \
  -v /home/chris/rosbags:/root/rosbags \
  lio_livox:melodic