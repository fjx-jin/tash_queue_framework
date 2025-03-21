cmake_minimum_required(VERSION 3.8)
project(task_clean)

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
find_package(geometry_msgs REQUIRED)
# find_package(navigation REQUIRED)

# 在 add_executable 之前添加
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  /root/RosRobot/include
)
# link_directories(
#   /root/RosRobot/lib
# )
add_executable(task_clean_node 
src/task_clean_node.cpp
src/snow_task_exector.cpp)

ament_target_dependencies(task_clean_node
  rclcpp
  std_msgs
  job_executor_msg
  geometry_msgs)

target_include_directories(task_clean_node PUBLIC
  ${rclcpp_INCLUDE_DIRS}
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(task_clean_node PUBLIC c_std_99 cxx_std_17) # Require C99 and C++17
# target_link_libraries(task_clean_node
# /root/RosRobot/lib/libnavi.so)

install(TARGETS task_clean_node
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
