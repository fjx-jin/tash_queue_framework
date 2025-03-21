#include "log.h"
#include "ros_converter.h"
#include <std_msgs/msg/string.hpp>
RosConverter::RosConverter(const std::shared_ptr<rclcpp::Node> node)
    : node_(node)
{
  // start_plan_subscriber_ = node->create_subscription<action_plan::msg::PlanGoal>(
  //     CMDTopic::START_PLAN, 10, std::bind(&RosConverter::on_received_start_plan, this, std::placeholders::_1));
}
RosConverter::~RosConverter(){}
void RosConverter::send(const std::string &message)
{
  auto msg = std_msgs::msg::String();
  msg.data = message;
  //publisher_->publish(msg);
}

void RosConverter::setSendMessageCallback(std::function<void(Message&)> callback)
{
  send_message_callback_ = callback;
}

void RosConverter::on_received_heartbeat()
{
  Message message_;
  message_.messageType = MessageType::HEARTBEAT_100ms;
  send_message_callback_(message_); // 上报100ms
}

// void RosConverter::on_received_start_plan(const action_plan::msg::PlanGoal::SharedPtr msg)
// {
//   LOG(INFO, "RosConverter", "received start plan");
//   Message message_;
//   message_.messageType = MessageType::START_PLAN;
//   message_.makeData(*msg);  // 使用 makeData 模板方法存储整个 PlanGoal 消息
//   send_message_callback_(message_);
// }