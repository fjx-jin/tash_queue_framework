#ifndef _MIDDLEWARE_H
#define _MIDDLEWARE_H
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/int8.hpp>
#include <rclcpp/subscription.hpp>
#include <memory>
#include <functional>
#include "job.h"
#include "job_executor_msg/srv/clean_task.hpp"
class TaskQueue;
class Middleware
{
public:
  Middleware(const std::shared_ptr<rclcpp::Node> node);
  ~Middleware();

  void addJobQueue(std::shared_ptr<TaskQueue> job_queue);
  void set_heartbeat_callback(std::function<void()> callback);
  void send_heartbeat();

  bool on_job_executed(Job job);
  bool on_job_paused(Job job);
  bool on_job_resumed(Job job);
  void on_job_finished(std_msgs::msg::Int8::SharedPtr msg);
  void setonJobFinishedCallback(std::function<void()> callback);

private:
  std::vector<std::shared_ptr<TaskQueue>> job_queues_;
  std::shared_ptr<rclcpp::Node> node_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::function<void()> send_heartbeat_callback_;
  std::function<void()> on_job_finished_callback_;
  rclcpp::Client<job_executor_msg::srv::CleanTask>::SharedPtr client_;
  rclcpp::Subscription<std_msgs::msg::Int8>::SharedPtr subscription_;
};
#endif