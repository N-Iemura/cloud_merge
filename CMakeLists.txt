cmake_minimum_required(VERSION 3.5)
project(cloud_merge)

set(CMAKE_CXX_STANDARD 14)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(PCL REQUIRED)

include_directories(include ${PCL_INCLUDE_DIRS})

add_executable(cloud_merge_node src/cloud_merge.cpp)

ament_target_dependencies(cloud_merge_node
  rclcpp
  sensor_msgs
  pcl_conversions
  PCL
)

install(TARGETS
  cloud_merge_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
