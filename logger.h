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

        std::string GetName();
    private:
        std::string name_;
        int id_;
        std::queue<int> unseen_message_index_;
        std::vector<std::string> message_log_;
};

extern Log* main_log;
extern Log* debug_log;

#endif
