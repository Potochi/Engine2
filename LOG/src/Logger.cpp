#include "../include/Logger.h"

namespace LOG {
    void Logger::Init() {
//     console_painter.Init();
        number_of_loggers = 0;
    }

    void Logger::Add_logger(std::string name, FILE *out, bool file_and_console) {
        if (loggers.count(name) == 0) {
            loggers[name] = new Specialized_logger(name, &console_painter, out, file_and_console, number_of_loggers++);
        }
    }

    Specialized_logger *Logger::Get_logger(std::string name) {
        if (loggers.count(name))
            return loggers[name];
        else
            return NULL;
    }

    void Logger::Close() {
        Delete_thread();
        for (auto &logger : loggers) {
            delete logger.second;
        }
        loggers.clear();
        Specialized_logger::Reset_longest_name_length();
        number_of_loggers = 0;
    }

    Logger *Logger::instance;

    Logger *Logger::Get_instance() {
        if (instance == nullptr)
            instance = new Logger();
        return instance;
    }

    void Logger::Add_to_queue(Log_query query) {
        if (!loggers.count(query.name))
            return;
        log_queue.push(query);
        if (log_queue.size() == QUEUE_SIZE || printing_interval_ms == 0)
            Print_queue();
        else
            Start_thread();
    }

    void Logger::Print_queue() {
        print_mutex.lock();
        while (!log_queue.empty()) {
            Get_logger(log_queue.front().name)->Log(&(log_queue.front()));
            log_queue.pop();
        }
        print_mutex.unlock();
    }

    void Logger::Start_thread() {
        if (thread != NULL) {
            end_mutex.lock();
            bool e = end;
            end_mutex.unlock();
            if (e)
                Delete_thread();
            else
                return;
        }
        thread = new std::thread(&Logger::Timer_checker, Logger::Get_instance());
    }

    void Logger::Delete_thread() {
        if (thread == NULL)
            return;
        thread->join();
        end = false;
        delete thread;
        thread = NULL;
    }

    void Logger::Timer_checker() {
        std::this_thread::sleep_for(std::chrono::milliseconds(printing_interval_ms));
        Print_queue();
        end_mutex.lock();
        end = true;
        end_mutex.unlock();
    }

    void Logger::Set_printing_interval_ms(long long _time_ms) {
        printing_interval_ms = _time_ms;
    }

    ///For User

    void Init() {
        Logger::Get_instance()->Init();
    }

    void Close() {
        Logger::Get_instance()->Close();
    }

    void Add_logger(std::string name, std::string filename, bool file_and_console) {
        FILE *out = fopen(filename.c_str(), "a");
        Add_logger(name, out, file_and_console);
    }

    void Add_logger(std::string name, FILE *out, bool file_and_console) {
        Logger::Get_instance()->Add_logger(name, out, file_and_console);
    }

    void Set_printing_interval_ms(long long _time_ms) {
        Logger::Get_instance()->Set_printing_interval_ms(_time_ms);
    }

    void Start_thread() {
        Logger::Get_instance()->Start_thread();
    }
}
