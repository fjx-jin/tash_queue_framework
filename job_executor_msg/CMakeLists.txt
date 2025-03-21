cmake_minimum_required(VERSION 3.8)
project(job_executor_msg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic  -std=c++17)
endif()
set(CMAKE_CXX_STANDARD 17)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
include_directories(
  include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/CleanTask.srv"  # 替换为你的服务文件路径
)
install(
  DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)
ament_export_include_directories(include)
# 确保生成的接口头文件可以被其他包使用
rosidl_get_typesupport_target(cpp_typesupport_target "${PROJECT_NAME}" "rosidl_typesupport_cpp")
add_library(${PROJECT_NAME}_headers INTERFACE)
target_include_directories(${PROJECT_NAME}_headers INTERFACE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)
install(TARGETS ${PROJECT_NAME}_headers
  EXPORT ${PROJECT_NAME}_headers
)
ament_export_targets(${PROJECT_NAME}_headers)

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
