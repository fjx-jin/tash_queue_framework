#include "snow_task_exector.h"
#include <rclcpp/logging.hpp>
#include <thread>

SnowTaskExector::SnowTaskExector(const std::shared_ptr<rclcpp::Node> &node_ptr)
:JobExecutorBase(node_ptr, CleanJobName)
{
}

SnowTaskExector::~SnowTaskExector()
{
}

bool SnowTaskExector::start(const std::shared_ptr<job_executor_msg::srv::CleanTask::Request> request)
{
  std::thread([this, request]() {
    RCLCPP_INFO(node_ptr->get_logger(), "start snow task");
    // 执行任务
    std::this_thread::sleep_for(std::chrono::minutes(3)); //模拟耗时任务
    onFinished(0);
  }).detach();
  return true;
}

bool SnowTaskExector::pause()
{
  return true;
}

bool SnowTaskExector::resume()
{
  return true;
}

bool SnowTaskExector::cancel()
{
  return true;
}