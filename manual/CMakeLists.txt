cmake_minimum_required(VERSION 3.8)
project(manual)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
add_executable(joy_to_twist_node src/joy_to_twist_node.cpp)
ament_target_dependencies(joy_to_twist_node 
rclcpp
sensor_msgs
geometry_msgs
)
add_executable(button src/button.cpp)
ament_target_dependencies(button rclcpp sensor_msgs std_msgs) 

target_include_directories(joy_to_twist_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)


target_include_directories(button PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(TARGETS
joy_to_twist_node
button
DESTINATION lib/${PROJECT_NAME}
)

ament_package()