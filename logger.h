#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <vector>
#include <queue>

class Log {
    public:
        Log();
        Log(std::string);

        static int next_id;

        void AddMessage(std::string);
        std::string GetMessage();
        int GetUnreads();
    private:
        std::string name_;
        int id_;
        std::queue<std::string*> unseen_messages_;
        std::vector<std::string> message_log_;
};

extern Log* main_log;

#endif
