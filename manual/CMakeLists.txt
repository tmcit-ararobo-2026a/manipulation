cmake_minimum_required(VERSION 3.8)
project(manual)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
add_library(joy_to_twist_components SHARED src/joy_to_twist_node.cpp)
ament_target_dependencies(joy_to_twist_components 
rclcpp
rclcpp_components
sensor_msgs
geometry_msgs
)
rclcpp_components_register_node(joy_to_twist_components
  PLUGIN "manual::JoyToTwistNode"
  EXECUTABLE joy_to_twist_node
)
target_include_directories(joy_to_twist_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(TARGETS joy_to_twist_node
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

ament_package()
