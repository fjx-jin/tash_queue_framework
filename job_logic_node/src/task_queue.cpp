#include "task_queue.h"
#include "log.h"

TaskQueue::TaskQueue(std::string name) : m_name(name), running_(false), paused_(false)
{

}
TaskQueue::~TaskQueue()
{

}

void TaskQueue::add_job(const Job& job)
{
  job_queue_.push(job);
  LOG(INFO, "TaskQueue", "Job %d added.", job.getId());
}
int TaskQueue::get_first_job_id()
{
  if (job_queue_.empty())
  {
    return -1;
  }
  return job_queue_.front().getId();
}
void TaskQueue::clear()
{
  while(!job_queue_.empty())
  {
    job_queue_.pop();
  }
}
void TaskQueue::cancle_first_job()
{
  if (!job_queue_.empty())
  {
    job_queue_.pop();
  }
}
void TaskQueue::start()
{
  LOG(INFO, "TaskQueue", "Start job %d.", job_queue_.front().getId());
  if(on_job_started_callback_ && !job_queue_.empty())
  {
    if(on_job_started_callback_(job_queue_.front()))
    {
      running_ = true;
      paused_ = false;
      LOG(INFO, "TaskQueue", "Job %d started.", job_queue_.front().getId());
    }
  }
}
void TaskQueue::pause()
{
  if(on_job_paused_callback_ && !job_queue_.empty() && running_)
  {
    if(on_job_paused_callback_(job_queue_.front()))
    {
      running_ = false;
      paused_ = true;
      LOG(INFO, "TaskQueue", "Job %d paused.", job_queue_.front().getId());
    }
  }
}
void TaskQueue::resume()
{
  if(on_job_resumed_callback_ && !job_queue_.empty() && paused_)
  {
    if(on_job_resumed_callback_(job_queue_.front()))
    {
      paused_ = false;
      running_ = true;
    }
  }
}
void TaskQueue::onFinished()
{
  LOG(INFO, "TaskQueue", "Job %d finished.", job_queue_.front().getId());
  job_queue_.pop();
  start();//开始下一个任务
}
void TaskQueue::setOnJobStartedCallback(std::function<bool(Job)> callback)
{
  on_job_started_callback_ = callback;
}
void TaskQueue::setOnJobPausedCallback(std::function<bool(Job)> callback)
{
  on_job_paused_callback_ = callback;
}
void TaskQueue::setonJobResumedCallback(std::function<bool(Job)> callback)
{
  on_job_resumed_callback_ = callback;
}