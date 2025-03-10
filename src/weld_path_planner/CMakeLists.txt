cmake_minimum_required(VERSION 3.8)
project(weld_path_planner)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(waypoint_executor src/waypoint_executor.cpp)
target_include_directories(waypoint_executor PRIVATE
  include
)
ament_target_dependencies(waypoint_executor
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
)

install(TARGETS waypoint_executor
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY config launch
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)
ament_package()
