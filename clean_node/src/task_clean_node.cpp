#include "task_clean_node.h"
#include <vector>
#include <iostream>
using namespace NavigationInterface;
using namespace std;

TaskCleanNode::TaskCleanNode() : Node("task_clean_node") {
  snow_task_exector_ = nullptr;
}

void TaskCleanNode::init() {
  // 获取节点指针
  auto node_ptr = std::dynamic_pointer_cast<rclcpp::Node>(shared_from_this());
  snow_task_exector_ = std::make_shared<SnowTaskExector>(node_ptr);
  registerPoseUpdateCallback(std::bind(&TaskCleanNode::getCurrentPoseCb, this));
  registerVehicleControlCallback(std::bind(&TaskCleanNode::moveCb, this,
                                          std::placeholders::_1,
                                          std::placeholders::_2));
  // cmd_vel_publisher_ = node_ptr->create_publisher<geometry_msgs::msg::Twist>(
  //     CMDTopic::CMD_VEL, QOSType::default_qos());
}

TaskCleanNode::~TaskCleanNode() {
}

Pose2D TaskCleanNode::getCurrentPoseCb() {
  // state_interface::msg::StatePos pos;
  // state_client_->getStatePos(pos);
  // return Pose2D{pos.x, pos.y, pos.phi};
}

void TaskCleanNode::moveCb(const double &vel, const double &rev) {
  // geometry_msgs::msg::Twist d;
  // d.linear.x = vel;
  // d.angular.z = rev;
  // cmd_vel_publisher_->publish(d);
  // std::cout << "PlanPublisher下发速度: (" << vel << ", " << rev << ")" << std::endl;
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TaskCleanNode>();
  node->init();
  rclcpp::spin(node);
  rclcpp::shutdown();
}