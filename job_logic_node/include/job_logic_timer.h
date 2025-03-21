#ifndef _JOB_LOGIC_TIMER_H_
#define _JOB_LOGIC_TIMER_H_
#include "timer_manager.h"
using Callback = std::function<void()>;
class JobLogicTimer
{
public:
  JobLogicTimer();
  ~JobLogicTimer(){}

  void addTimer(const std::string &timer_name, uint64_t timer_period_ms, Callback callback);
  void removeTimer(const std::string &timer_name);
  void startTimer(const std::string &timer_name);
  void stopTimer(const std::string &timer_name);

protected:
  void update_timers();
private:
      struct Timer {
        std::string name;
        uint64_t interval_ms;  // 间隔时间（毫秒）
        uint64_t elapsed_ms;   // 已经过去的时间
        bool is_running;       // 定时器是否在运行
        std::function<void()> callback;
        
        Timer(const std::string& n, uint32_t i, std::function<void()> cb)
            : name(n), interval_ms(i), elapsed_ms(0), is_running(true), callback(cb) {}
    };

    std::vector<Timer> m_timers;
};

#endif