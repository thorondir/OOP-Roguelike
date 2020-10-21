#include "logger.h"

// static int for next log id
int Log::next_id = 0;

// initialise global logs to nothing
Log* main_log = nullptr;
Log* debug_log = nullptr;

// a log with no name gets a name based on its id
Log::Log() {
    id_ = next_id++;
    name_ = std::string("Log ").append(std::to_string(id_));
}

// create a log with a name
Log::Log(std::string name) {
    id_ = next_id++;
    name_ = name;
}

// add a message to the log, and add the message to the unseen queue
void Log::AddMessage(std::string message) {
    message_log_.push_back(message);
    unseen_message_index_.push(message_log_.size() - 1);
}

// get a message off the top of the queue
std::string Log::GetMessage() {
    std::string message = "";
    // if there are unseen messages, get those, otherwise return nothing
    if (unseen_message_index_.size() > 0) {
        message = message_log_[unseen_message_index_.front()];
        unseen_message_index_.pop();
    }
    return message;
}

// return the number of unread messages
int Log::GetUnreads() {
    return unseen_message_index_.size();
}

// get the name of the log
std::string Log::GetName() {
    return name_;
}
