#ifndef LOGGER_H
#define LOGGER_H

#include "Color.h"
#include "Specialized_logger.h"
#include "Log_query.h"
#include "CTimer.h"

#include <vector>
#include <unordered_map>
#include <queue>
#include <thread>
#include <mutex>

namespace LOG {
    const int QUEUE_SIZE = 1024;

    class Logger {
    private:
        Console_painter console_painter;
        std::unordered_map<std::string, Specialized_logger *> loggers;
        static Logger *instance;
        int number_of_loggers = 0;
        std::queue<Log_query> log_queue;
        std::thread *thread;
        std::mutex end_mutex, print_mutex;
        bool end = false;
        long long printing_interval_ms = 0;

    private:
        void Print_queue();

        void Timer_checker();

    public:
        static Logger *Get_instance();

        void Init();

        void Add_logger(std::string name, FILE *out = NULL, bool file_and_console = false);

        Specialized_logger *Get_logger(std::string name);

        void Close();

        void Start_thread();

        void Delete_thread();

        void Set_printing_interval_ms(long long _time_ms);

        void Add_to_queue(Log_query query);

    protected:
        Logger() {}
    };

    ///For User
    void Init();

    void Close();

    void Add_logger(std::string name, std::string filename, bool file_and_console = false);

    void Add_logger(std::string name, FILE *out = NULL, bool file_and_console = false);

    void Set_printing_interval_ms(long long _time_ms);

    void Start_thread();

    void Stop_thread();
};

//#define LOG_INFO(name,format,...)     LOG::Logger::Get_instance()->Add_to_queue(LOG::Make_log_query(name,LOG::LT_INFO,format, ##__VA_ARGS__))
//#define LOG_WARNING(name,format,...)  LOG::Logger::Get_instance()->Add_to_queue(LOG::Make_log_query(name,LOG::LT_WARNING,format, ##__VA_ARGS__))
//#define LOG_ERROR(name,format,...)    LOG::Logger::Get_instance()->Add_to_queue(LOG::Make_log_query(name,LOG::LT_ERROR,format, ##__VA_ARGS__))
//#define LOG_CRITICAL(name,format,...) LOG::Logger::Get_instance()->Add_to_queue(LOG::Make_log_query(name,LOG::LT_CRITICAL,format, ##__VA_ARGS__))

// TODO Refactor macros to be less retarded and cross_platform compatible
#define LOG_INFO(name, format, ...)     printf("\u001b[36m"); printf(format, ##__VA_ARGS__); printf("\n"); printf("\u001b[0m");
#define LOG_WARNING(name, format, ...)  printf("\u001b[33m"); printf(format, ##__VA_ARGS__); printf("\n") ;printf("\u001b[0m");
#define LOG_ERROR(name, format, ...)    printf("\u001b[33;1m"); printf(format, ##__VA_ARGS__); printf("\n"); printf("\u001b[0m");
#define LOG_CRITICAL(name, format, ...) printf("\u001b[31;1m"); printf(format, ##__VA_ARGS__); printf("\n") ;printf("\u001b[0m");


#endif // LOGGER_H
