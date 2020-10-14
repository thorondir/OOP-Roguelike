#include "logger.h"

int Log::next_id = 0;

Log* main_log = nullptr;

Log::Log() {
    id_ = next_id++;
    name_ = std::string("Log ").append(std::to_string(id_));
}

Log::Log(std::string name) {
    id_ = next_id++;
    name_ = name;
}

void Log::AddMessage(std::string message) {
    message_log_.push_back(message);
    unseen_messages_.push(&message_log_.back());
}

std::string Log::GetMessage() {
    std::string message = "";
    if (unseen_messages_.size() > 0) {
        message = *(unseen_messages_.front());
        unseen_messages_.pop();
    }
    return message;
}

int Log::GetUnreads() {
    return unseen_messages_.size();
}
