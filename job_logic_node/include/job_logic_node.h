#ifndef _JOB_LOGIC_NODE_H
#define _JOB_LOGIC_NODE_H
#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <functional>
#include "message.h"
#include "job_logic_timer.h"
class TaskQueue;
class RosConverter;
class Middleware;
class JobLogic : public rclcpp::Node, public JobLogicTimer
{
public:
  JobLogic();
  ~JobLogic();
  void init();
  //void add_task(const int &id);
  void send_message(const std::string &message);

private:
  void process_message(Message& message);

  void on_received_start_plan(Message& message);

  void on_timer_test();

private:
  std::shared_ptr<TaskQueue> m_job_queue;
  std::shared_ptr<RosConverter> m_ros_converter;
  std::shared_ptr<Middleware> m_middleware;
};
#endif