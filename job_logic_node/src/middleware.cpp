#include "middleware.h"
#include "task_queue.h"
#include "log.h"
#include "job_executor_msg/job_executor/job_executor_base.h"

Middleware::Middleware(const std::shared_ptr<rclcpp::Node> node) : node_(node)
{
  client_ = node_->create_client<job_executor_msg::srv::CleanTask>(CleanJobName);
  subscription_ = node_->create_subscription<std_msgs::msg::Int8>(
      OnFinishTopic, 10,
      std::bind(&Middleware::on_job_finished, this, std::placeholders::_1));
  timer_ = node_->create_wall_timer(std::chrono::milliseconds(100),
                                    std::bind(&Middleware::send_heartbeat, this));
}
Middleware::~Middleware() {}
void Middleware::addJobQueue(std::shared_ptr<TaskQueue> job_queue)
{
  job_queue->setOnJobStartedCallback(std::bind(&Middleware::on_job_executed, this, std::placeholders::_1));
  job_queue->setOnJobPausedCallback(std::bind(&Middleware::on_job_paused, this, std::placeholders::_1));
  job_queue->setonJobResumedCallback(std::bind(&Middleware::on_job_resumed, this, std::placeholders::_1));
  job_queues_.push_back(job_queue);
}
void Middleware::set_heartbeat_callback(std::function<void()> callback)
{
  send_heartbeat_callback_ = callback;
}

void Middleware::send_heartbeat()
{
  if (send_heartbeat_callback_)
  {
    send_heartbeat_callback_();
  }
}

bool Middleware::on_job_executed(Job job)
{
  LOG(INFO, "Middleware", "Job %d executed.", job.getId());
  if (job.getId() == JobId::Stop)
  {
    
  }
  else if (job.getId() == JobId::AutoSnow)
  {
    auto request = std::make_shared<job_executor_msg::srv::CleanTask::Request>();
    request->type = 0; // start
    client_->async_send_request(request);
  }
  return true;
}

bool Middleware::on_job_paused(Job job)
{
  LOG(INFO, "Middleware", "Job %d paused.", job.getId());
  if (job.getId() == 0)
  {
    auto request = std::make_shared<job_executor_msg::srv::CleanTask::Request>();
    request->type = 1; // pause
    client_->async_send_request(request);
  }
  return true;
}
bool Middleware::on_job_resumed(Job job)
{
  LOG(INFO, "Middleware", "Job %d resumed.", job.getId());
  return true;
}
void Middleware::on_job_finished(std_msgs::msg::Int8::SharedPtr msg)
{
  LOG(INFO, "Middleware", "Job %d finished.", msg->data);
  job_queues_.front()->onFinished();
}
void Middleware::setonJobFinishedCallback(std::function<void()> callback)
{
  on_job_finished_callback_ = callback;
}