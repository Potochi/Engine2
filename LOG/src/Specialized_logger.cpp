#include "../include/Specialized_logger.h"

namespace LOG {

#ifdef WINDOWS_CODE
    const int INFO_COLOR=TEXT_WHITE|TEXT_INTENSITY,WARNING_COLOR=TEXT_YELLOW|TEXT_INTENSITY,ERROR_COLOR=TEXT_RED|TEXT_INTENSITY,CRITICAL_COLOR=BG_RED|BG_INTENSITY;

    const int Specialized_logger::name_colors[NUMBER_OF_NAME_COLORS]={TEXT_GREEN,TEXT_MAGENTA,TEXT_CYAN,TEXT_BLUE,BG_GREEN,BG_MAGENTA,BG_CYAN,BG_BLUE,BG_INTENSITY|TEXT_INTENSITY|TEXT_GREEN,
                                                   BG_INTENSITY|TEXT_INTENSITY|TEXT_MAGENTA,BG_INTENSITY|TEXT_INTENSITY|TEXT_CYAN,BG_INTENSITY|TEXT_INTENSITY|TEXT_BLUE,
                                                   TEXT_INTENSITY|TEXT_GREEN,TEXT_INTENSITY|TEXT_MAGENTA,TEXT_INTENSITY|TEXT_CYAN,TEXT_INTENSITY|TEXT_BLUE};
#endif
    int Specialized_logger::longest_name_length = 0;

    void Specialized_logger::Log(Log_query *query) {
//     if(this==NULL)
        return;
#ifdef WINDOWS_CODE
        int color;
        std::string message;
        switch(query->type)
               {
                case LT_INFO:
                           query->color=INFO_COLOR;
                           query->message="info";
                           break;
                case LT_WARNING:
                           query->color=WARNING_COLOR;
                           query->message="warning";
                           break;
                case LT_ERROR:
                           query->color=ERROR_COLOR;
                           query->message="error";
                           break;
                case LT_CRITICAL:
                           query->color=CRITICAL_COLOR;
                           query->message="critical";
                           break;

               }
        Print_query(query);
#endif
    }

    void Specialized_logger::Reset_longest_name_length() {
        longest_name_length = 0;
    }


    void Specialized_logger::Print_query(Log_query *query) {
        return;
#ifdef WINDOWS_CODE
        int col = query->color;
        std::string message = query->message;
        std::string log = query->log;

        if (this == nullptr)
            return;
        char timestamp[100];
        Get_current_time(timestamp);

        const int MESSAGE_LONGEST_LENGTH = 8;
        std::string spaces_name, spaces_message;
        for (int i = 0; i < longest_name_length; i++)
            spaces_name += ' ';
        for (int i = 0; i < MESSAGE_LONGEST_LENGTH; i++)
            spaces_message += ' ';

        if (out == NULL || print_in_both) {
            console_painter->Change_color(name_colors[name_color]);
            //console_painter->Change_color(TEXT_BLUE|TEXT_INTENSITY);
            fprintf(stderr, "[%s]", timestamp);

            console_painter->Reset_color();
            fprintf(stderr, " ");
            console_painter->Change_color(name_colors[name_color]);

            fprintf(stderr, "[%s]", name.c_str());
            console_painter->Reset_color();
            fprintf(stderr, "%s ", spaces_name.c_str() + name.length());
            console_painter->Change_color(col);
            fprintf(stderr, "[%s]%s", message.c_str(), spaces_message.c_str() + message.length());
            console_painter->Reset_color();
            fprintf(stderr, " ");
            console_painter->Change_color(col);
            fprintf(stderr, log.c_str());
            fprintf(stderr, "\n");
            console_painter->Reset_color();
        }
        if (out != NULL || print_in_both) {
            fprintf(out, "[%s] ", timestamp);
            fprintf(out, " [%s]%s ", name.c_str(), spaces_name.c_str() + name.length());
            fprintf(out, "[%s]%s ", message.c_str(), spaces_message.c_str() + message.length());
            fprintf(out, log.c_str());
            fprintf(out, "\n");
            fflush(out);
        }
#endif
    }

    void Specialized_logger::Get_current_time(char *ret) {
        timeval curTime;
        gettimeofday(&curTime, NULL);
        int milliseconds = curTime.tv_usec / 1000;

        time_t raw;
        time(&raw);
        tm *now = localtime(&raw);
        strftime(ret, 100, "%Y-%m-%d %H:%M:%S", now);
        sprintf(ret, "%s.%.3d", ret, milliseconds);
    }
}
