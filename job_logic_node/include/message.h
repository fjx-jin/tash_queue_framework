#ifndef _MESSAGE_H
#define _MESSAGE_H
#include <iostream>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include <typeindex>

enum MessageType
{
  HEARTBEAT_100ms,
  START_PLAN,
  CANCEL_PLAN,
};

#include <memory>
#include <typeindex>
#include <typeinfo>

class Message {
private:
    std::shared_ptr<void> data;  // 使用 shared_ptr 管理内存
    std::type_index dataType;

public:
    MessageType messageType;

    // Constructor initializes data to null and dataType to void
    Message() : data(nullptr), dataType(typeid(void)) {}

    // Create and store data of type T
    template <typename T>
    void makeData(T value) {
        data = std::make_shared<T>(std::move(value)); // 使用 shared_ptr 管理对象
        dataType = typeid(T);
    }

    // Retrieve data as a pointer of type T
    template <typename T>
    std::shared_ptr<T> getData() {
        if (dataType != typeid(T)) {
            return nullptr; // 如果类型不匹配，返回 nullptr
        }
        return std::static_pointer_cast<T>(data);
    }

    // Check if data is of type T
    template <typename T>
    bool isDataType() const {
        return dataType == typeid(T);
    }

    // Copy constructor
    Message(const Message& other) : data(other.data), dataType(other.dataType) {
        // shared_ptr 会自动处理拷贝操作
    }

    // Copy assignment operator
    Message& operator=(const Message& other) {
        if (this != &other) {  // 防止自赋值
            data = other.data;
            dataType = other.dataType;
        }
        return *this;
    }

    // Move constructor
    Message(Message&& other) noexcept : data(std::move(other.data)), dataType(std::move(other.dataType)) {
        // 将所有权转移
    }

    // Move assignment operator
    Message& operator=(Message&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            dataType = std::move(other.dataType);
        }
        return *this;
    }
};
#endif