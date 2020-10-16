#include "logger.h"

int Log::next_id = 0;

Log* main_log = nullptr;
Log* debug_log = nullptr;

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
    unseen_message_index_.push(message_log_.size() - 1);
}

std::string Log::GetMessage() {
    std::string message = "";
    if (unseen_message_index_.size() > 0) {
        message = message_log_[unseen_message_index_.front()];
        unseen_message_index_.pop();
    }
    return message;
}

int Log::GetUnreads() {
    return unseen_message_index_.size();
}

std::string Log::GetName() {
    return name_;
}
