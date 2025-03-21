#include <rclcpp/rclcpp.hpp>
#include "job_logic_node.h"

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<JobLogic>();
  node->init();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}