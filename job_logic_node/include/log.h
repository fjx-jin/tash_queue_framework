#ifndef _LOG_H
#define _LOG_H
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/logger.hpp>
inline std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time_t_now));
    return std::string(buffer) + "." + std::to_string(ms.count());
}

// 定义一个带时间戳、文件名、行号、函数名的日志宏
#define LOG(level, logger, fmt, ...)                                  \
    RCLCPP_##level(rclcpp::get_logger(logger),                        \
                   "[%s] [%s:%d] %s: " fmt,                           \
                   get_current_time().c_str(), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)


#endif