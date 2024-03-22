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

add_library(heartbeat_pub_component 
  SHARED src/heartbeat_pub_component.cpp)
target_include_directories(heartbeat_pub_component 
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
ament_target_dependencies(heartbeat_pub_component 
  "rclcpp" "rclcpp_lifecycle" "rclcpp_components" "std_msgs")
rclcpp_components_register_nodes(heartbeat_pub_component 
  "arwo::HeartbeatPubComponent")

add_library(heartbeat_sub_component 
  SHARED src/heartbeat_sub_component.cpp)
target_include_directories(heartbeat_sub_component 
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
ament_target_dependencies(heartbeat_sub_component 
  "rclcpp" "rclcpp_lifecycle" "rclcpp_components" "std_msgs")
rclcpp_components_register_nodes(heartbeat_sub_component
  "arwo::HeartbeatSubComponent")

add_library(listener_component 
  SHARED src/listener_component.cpp)
target_include_directories(listener_component 
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
ament_target_dependencies(listener_component 
  "rclcpp" "rclcpp_lifecycle" "rclcpp_components" "std_msgs")
rclcpp_components_register_nodes(listener_component
  "arwo::ListenerComponent")

add_library(lifecycle_talker_component 
  SHARED src/lifecycle_talker_component.cpp)
target_include_directories(lifecycle_talker_component 
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
ament_target_dependencies(lifecycle_talker_component 
  "rclcpp" "rclcpp_lifecycle" "rclcpp_components" "std_msgs")
rclcpp_components_register_nodes(lifecycle_talker_component
  "arwo::LifecycleTalkerComponent")

add_executable(manual_listener_composition src/manual_listener_composition.cpp)
target_link_libraries(manual_listener_composition heartbeat_sub_component listener_component)
ament_target_dependencies(manual_listener_composition rclcpp)

add_executable(manual_talker_composition src/manual_talker_composition.cpp)
target_link_libraries(manual_talker_composition heartbeat_pub_component lifecycle_talker_component)
ament_target_dependencies(manual_talker_composition rclcpp)

add_executable(linktime_listener_composition src/linktime_composition.cpp)
target_link_libraries(linktime_listener_composition heartbeat_sub_component listener_component)
ament_target_dependencies(linktime_listener_composition class_loader rclcpp rclcpp_components)

add_executable(linktime_talker_composition src/linktime_composition.cpp)
target_link_libraries(linktime_talker_composition heartbeat_pub_component lifecycle_talker_component)
ament_target_dependencies(linktime_talker_composition class_loader rclcpp rclcpp_components)

add_executable(dlopen_composition src/dlopen_composition.cpp)
ament_target_dependencies(dlopen_composition class_loader rclcpp rclcpp_components)

install(
  TARGETS arwo_components
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  TARGETS
    manual_listener_composition
    manual_talker_composition
    linktime_listener_composition
    linktime_talker_composition
    dlopen_listener_composition
    dlopen_talker_composition
  DESTINATION lib/${PROJECT_NAME}
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
