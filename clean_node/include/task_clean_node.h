#ifndef _TASK_CLEAN_NODE_H
#define _TASK_CLEAN_NODE_H
#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <functional>
#include "snow_task_exector.h"
#include "navi/NavigationInterface.h"
#include "geometry_msgs/msg/twist.hpp"

class TaskCleanNode : public rclcpp::Node
{
public:
  TaskCleanNode();
  ~TaskCleanNode();
  void init();

private:
  std::shared_ptr<SnowTaskExector> snow_task_exector_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;

  Pose2D getCurrentPoseCb();
  void moveCb(const double &vel, const double &rev);
};
#endif