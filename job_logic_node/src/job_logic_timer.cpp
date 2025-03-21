#include "job_logic_timer.h"

JobLogicTimer::JobLogicTimer() {
}

void JobLogicTimer::addTimer(const std::string &name, uint64_t interval_ms,
                             Callback callback) {
  m_timers.emplace_back(name, interval_ms, callback);
}

void JobLogicTimer::removeTimer(const std::string &name) {
  m_timers.erase(
    std::remove_if(m_timers.begin(), m_timers.end(),
        [&name](const Timer& timer) {
    return timer.name == name; }),
    m_timers.end()
  );
}

void JobLogicTimer::startTimer(const std::string &name) {
  auto it =
      std::find_if(m_timers.begin(),
                   m_timers.end(),
                   [&name](const Timer &timer) { return timer.name == name; });
  if (it != m_timers.end()) {
    it->is_running = true;
  }
}

void JobLogicTimer::stopTimer(const std::string &name) {
  auto it =
      std::find_if(m_timers.begin(),
                   m_timers.end(),
                   [&name](const Timer &timer) { return timer.name == name; });
  if (it != m_timers.end()) {
    it->is_running = false;
    it->elapsed_ms = 0;
  }
}

void JobLogicTimer::update_timers() {
  for (auto &timer : m_timers) {
    if (!timer.is_running)
      continue;

    timer.elapsed_ms += 100;  // HEARTBEAT 间隔为100ms

    if (timer.elapsed_ms >= timer.interval_ms) {
      timer.callback();
      timer.elapsed_ms = 0;  // 重置计时
    }
  }
}