#ifndef _JOB_H_
#define _JOB_H_

#include <stdio.h>
#include <any>
#include <optional>

enum JobId {  // 改用enum class以获得更好的类型安全性
    Stop = 1,
    AutoSnow = 2,
    AutoMower = 3,
    Return = 4
};

class Job {
public:
    // 构造函数允许可选地传入数据
    explicit Job(int id) : _id(id) {}
    Job(int id, const std::any& data) : _id(id), _data(data) {}

    // Getter方法
    int getId() const { return _id; }
    
    // 获取数据的模板方法
    template<typename T>
    T getData() const {
        return std::any_cast<T>(_data);
    }

    // 检查是否包含数据
    bool hasData() const {
        return _data.has_value();
    }

    // 设置数据
    void setData(const std::any& data) {
        _data = data;
    }

private:
    int _id;
    std::any _data;  // 用于存储任意类型的数据
};

#endif