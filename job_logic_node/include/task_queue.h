#ifndef _TASK_QUEUE_H_
#define _TASK_QUEUE_H_
#include <memory>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <functional>
#include <string>
#include "job.h"

class TaskQueue {
public:
  TaskQueue(std::string name);
  ~TaskQueue();
  TaskQueue(const TaskQueue&) = delete;
  TaskQueue& operator=(const TaskQueue&) = delete;

  void add_job(const Job& job);
  int get_first_job_id();
  void clear();
  void cancle_first_job();
  void start();
  void pause();
  void resume();
  void onFinished();

  void setOnJobStartedCallback(std::function<bool(Job)> callback);
  void setOnJobPausedCallback(std::function<bool(Job)> callback);
  void setonJobResumedCallback(std::function<bool(Job)> callback);

private:
  std::string m_name;
  std::condition_variable condition_;
  std::queue<Job> job_queue_;
  bool running_;
  bool paused_;
  std::function<bool(Job)> on_job_started_callback_;
  std::function<bool(Job)> on_job_paused_callback_;
  std::function<bool(Job)> on_job_resumed_callback_;
};
#endif