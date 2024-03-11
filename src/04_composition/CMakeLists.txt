cmake_minimum_required(VERSION 3.8)
project(04_composition)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)

add_library(
  arwo_components SHARED 
  src/heartbeat_pub_component.cpp
  src/heartbeat_sub_component.cpp
  src/listener_component.cpp
  src/lifecycle_talker_component.cpp
)

target_include_directories(
  arwo_components
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(
  arwo_components 
  "rclcpp"
  "rclcpp_lifecycle"
  "rclcpp_components"
  "std_msgs"
)

rclcpp_components_register_nodes(
  arwo_components 
  "arwo::HeartbeatPubComponent"
  "arwo::HeartbeatSubComponent"
  "arwo::ListenerComponent"
  "arwo::LifecycleTalkerComponent"
)

add_executable(manual_listener_composition src/manual_listener_composition.cpp)
ament_target_dependencies(manual_listener_composition rclcpp)
target_link_libraries(manual_listener_composition arwo_components)

add_executable(manual_talker_composition src/manual_talker_composition.cpp)
ament_target_dependencies(manual_talker_composition rclcpp)
target_link_libraries(manual_talker_composition arwo_components)

install(
  TARGETS 
    arwo_components
    manual_listener_composition
    manual_talker_composition
  DESTINATION 
    lib
)

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
