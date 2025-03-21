cmake_minimum_required(VERSION 3.8)
project(job_logic)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic  -std=c++17)
endif()
set(CMAKE_CXX_STANDARD 17)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread)
find_package(job_executor_msg REQUIRED)

# 在 add_executable 之前添加
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_executable(job_logic_node 
src/main.cpp
src/middleware.cpp
src/job_logic_node.cpp
src/ros_converter.cpp
src/task_queue.cpp
src/job_logic_timer.cpp)

ament_target_dependencies(job_logic_node
  rclcpp
  std_msgs
  job_executor_msg
  Boost)

target_include_directories(job_logic_node PUBLIC
  ${rclcpp_INCLUDE_DIRS}
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${CMAKE_SOURCE_DIR}/include)
target_compile_features(job_logic_node PUBLIC c_std_99 cxx_std_17) # Require C99 and C++17


install(TARGETS job_logic_node
  DESTINATION lib/${PROJECT_NAME})

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
