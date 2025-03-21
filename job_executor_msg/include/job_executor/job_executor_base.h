#ifndef _JOB_EXECUTOR_BASE_H_
#define _JOB_EXECUTOR_BASE_H_
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int8.hpp"
#include "rclcpp/publisher.hpp"
#include "rclcpp/service.hpp"
#include "job_executor_msg/srv/clean_task.h"
#define OnFinishTopic "finish_topic" //所有任务finish上报共用同一个topic，因为理论只有一个任务是在运行中
#define StopJobName  "stopjob" //每个任务各自用自己的name作为service的名称
#define CleanJobName "cleanjob"

//后续在任务节点实现该类，由middleware和任务节点对齐具体哪些任务id下发到哪个name的节点
class JobExecutorBase
{
public:
  JobExecutorBase(const std::shared_ptr<rclcpp::Node> &node, const std::string &name) :node_ptr(node), name_(name)
  {
    service_ = node_ptr->create_service<job_executor_msg::srv::CleanTask>(name, std::bind(&JobExecutorBase::on_service_handle, this, std::placeholders::_1, std::placeholders::_2));
    publisher_ = node_ptr->create_publisher<std_msgs::msg::Int8>(OnFinishTopic, 10);
  }

  virtual ~JobExecutorBase(){}

  std::shared_ptr<rclcpp::Node> node_ptr;
protected:
  void onFinished(int8_t code)
  {
    std_msgs::msg::Int8 msg;
    msg.data = code;
    publisher_->publish(msg);
  } 
private:
  void on_service_handle(const std::shared_ptr<job_executor_msg::srv::CleanTask::Request> request,
                         const std::shared_ptr<job_executor_msg::srv::CleanTask::Response> response)
  {
    if (request->type == 0)
    {
      response->ret = start(request);
    }
    else if (request->type == 1)
    {
      response->ret = pause();
    }
    else if (request->type == 2)
    {
      response->ret = resume();
    }
  }

  virtual bool start(const std::shared_ptr<job_executor_msg::srv::CleanTask::Request> request) = 0;
  virtual bool pause() = 0;
  virtual bool resume() = 0;
  virtual bool cancel() = 0;


  std::string name_;
  rclcpp::Service<job_executor_msg::srv::CleanTask>::SharedPtr service_;
  rclcpp::Publisher<std_msgs::msg::Int8>::SharedPtr publisher_;
};
#endif
