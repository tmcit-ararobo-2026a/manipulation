cmake_minimum_required(VERSION 3.8)
project(manual)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
add_executable(three_wheel_node src/three_wheel_node.cpp)
ament_target_dependencies(three_wheel_node 
rclcpp
sensor_msgs
)

target_include_directories(three_wheel_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

  install(TARGETS
  three_wheel_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
