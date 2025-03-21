#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include "job_logic_node.h"
#include "log.h"
#include "ros_converter.h"
#include "middleware.h"
#include "task_queue.h"
#include <rclcpp/node.hpp>

JobLogic::JobLogic() 
  : Node("job_logic_node")
  , JobLogicTimer()
{
}
JobLogic::~JobLogic(){}
// void JobLogic::add_task(const int &id)
// {
//   Job job(id);
//   m_job_queue->add_job(job);
// }
void JobLogic::init()
{
  m_job_queue = std::make_shared<TaskQueue>("test");
  
  auto node_ptr = std::dynamic_pointer_cast<rclcpp::Node>(shared_from_this());
  
  m_middleware = std::make_shared<Middleware>(node_ptr);
  m_ros_converter = std::make_shared<RosConverter>(node_ptr);
  
  m_middleware->addJobQueue(m_job_queue);
  m_middleware->set_heartbeat_callback(std::bind(&RosConverter::on_received_heartbeat, m_ros_converter));
  m_ros_converter->setSendMessageCallback(std::bind(&JobLogic::process_message, this, std::placeholders::_1));

  addTimer("test", 1000, std::bind(&JobLogic::on_timer_test, this));
  // 添加一个每500毫秒执行一次的定时器
  addTimer("fast_timer", 500, []() { 
    LOG(INFO, "JobLogic", "Fast timer triggered"); 
  });
}

void JobLogic::send_message(const std::string &message)
{
  m_ros_converter->send(message);
}

void JobLogic::process_message(Message& message)
  {
    switch (message.messageType)
    {
    case MessageType::HEARTBEAT_100ms:
      //做一些定时器相关的
      update_timers();
      break;
    case MessageType::START_PLAN:
      // 处理 START_PLAN 消息
      on_received_start_plan(message);
      break;
    default:
      break;
    }
    if (message.messageType != MessageType::HEARTBEAT_100ms)
      LOG(INFO, "JobLogic", "Received message: %d", message.messageType);
}

void JobLogic::on_received_start_plan(Message& message)
{
//   if (message.isDataType<action_plan::msg::PlanGoal>()) {
//     auto planGoal = message.getData<action_plan::msg::PlanGoal>();
//     if (planGoal) {
//         // 使用 planGoal 中的数据
//     }
// }
  m_job_queue->add_job(Job(JobId::AutoSnow));
  // m_job_queue->add_job(Job(JobId::Return));
  m_job_queue->add_job(Job(JobId::Stop));
  m_job_queue->start();
  LOG(INFO, "JobLogic", "Received start plan");
}

void JobLogic::on_timer_test()
{
  LOG(INFO, "JobLogic", "test timer");
}
