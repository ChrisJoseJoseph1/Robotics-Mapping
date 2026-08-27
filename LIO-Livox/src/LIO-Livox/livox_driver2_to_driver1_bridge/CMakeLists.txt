cmake_minimum_required(VERSION 3.0.2)
project(livox_driver2_to_driver1_bridge)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  livox_ros_driver
  livox_ros_driver2
)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs livox_ros_driver livox_ros_driver2
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(livox_driver2_to_driver1_bridge src/bridge.cpp)

add_dependencies(livox_driver2_to_driver1_bridge
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(livox_driver2_to_driver1_bridge
  ${catkin_LIBRARIES}
)