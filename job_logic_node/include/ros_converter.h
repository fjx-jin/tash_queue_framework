#ifndef _ROS_CONVERTER_H
#define _ROS_CONVERTER_H
#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <functional>
#include <std_msgs/msg/string.hpp>
#include "message.h"
class RosConverter
{
public:
  RosConverter(const std::shared_ptr<rclcpp::Node> node);
  ~RosConverter();

  void send(const std::string &message);
  void setSendMessageCallback(std::function<void(Message&)> callback);
  void on_received_heartbeat();

  // void on_received_start_plan(const action_plan::msg::PlanGoal::SharedPtr msg);
private:
  std::shared_ptr<rclcpp::Node> node_;
  // rclcpp::Subscription<action_plan::msg::PlanGoal>::SharedPtr start_plan_subscriber_;
  std::function<void(Message&)> send_message_callback_;
};
#endif