cmake_minimum_required(VERSION 3.0.2)
project(lio_livox_map_saver)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  pcl_ros
  pcl_conversions
)

find_package(PCL REQUIRED)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_executable(lio_livox_map_saver src/map_saver.cpp)

target_link_libraries(lio_livox_map_saver
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
)