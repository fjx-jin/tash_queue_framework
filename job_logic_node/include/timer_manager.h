#ifndef _TIMER_MANAGER_H_
#define _TIMER_MANAGER_H_
#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

class TimerManager
{
public:
  using Callback = std::function<void()>;

  class Timer
  {
  public:
    Timer(std::chrono::milliseconds timeout, Callback callback)
        : elapsed_time_ms_(0), timeout_ms_(timeout.count()), callback_(std::move(callback)), running_(false) {}

    void on_timer()
    {
      if (!running_)
        return;
      elapsed_time_ms_ += 100; // 每次心跳增加 100ms
      if (elapsed_time_ms_ >= timeout_ms_)
      {
        elapsed_time_ms_ = 0; // 重置计时
        if (callback_)
        {
          callback_(); // 触发回调
        }
      }
    }

    void start()
    {
      elapsed_time_ms_ = 0;
      running_ = true;
    }

    void stop()
    {
      running_ = false;
      elapsed_time_ms_ = 0;
    }

    bool isRunning() const
    {
      return running_;
    }

  private:
    int elapsed_time_ms_; // 已经经过的时间（ms）
    int timeout_ms_;      // 超时时间（ms）
    Callback callback_;   // 超时回调函数
    bool running_;        // 定时器是否运行
  };

  TimerManager() = default;

  // 添加一个定时器
  void addTimer(const std::string &name, std::chrono::milliseconds timeout, Callback callback)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    timers_[name] = std::make_shared<Timer>(timeout, callback);
  }

  // 删除一个定时器
  void removeTimer(const std::string &name)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    timers_.erase(name);
  }

  // 启动指定定时器
  void startTimer(const std::string &name)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = timers_.find(name);
    if (it != timers_.end())
    {
      it->second->start();
    }
  }

  // 停止指定定时器
  void stopTimer(const std::string &name)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = timers_.find(name);
    if (it != timers_.end())
    {
      it->second->stop();
    }
  }

  // 收到心跳信号，更新所有定时器
  void step()
  {
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto &[name, timer] : timers_)
    {
      timer->on_timer();
    }
  }

private:
  std::unordered_map<std::string, std::shared_ptr<Timer>> timers_; // 定时器容器
  std::mutex mutex_;                                               // 保护定时器容器
};
#endif