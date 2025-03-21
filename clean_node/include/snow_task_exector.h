#ifndef _SNOW_TASK_EXECTOR_H
#define _SNOW_TASK_EXECTOR_H
#include "job_executor_msg/srv/clean_task.hpp"
#include "job_executor_msg/job_executor/job_executor_base.h"
#include "rclcpp/rclcpp.hpp"
// #include "plan_action_server/plan_base_controller.h"
class SnowTaskExector : public JobExecutorBase
{
public:
  SnowTaskExector(const std::shared_ptr<rclcpp::Node> &node_ptr);
  ~SnowTaskExector();

private:
  bool start(const std::shared_ptr<job_executor_msg::srv::CleanTask::Request> request);
  bool pause();
  bool resume();
  bool cancel();

  void on_job_finished();
};

#endif
