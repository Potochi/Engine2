#ifndef SPECIALIZED_LOGGER_H
#define SPECIALIZED_LOGGER_H

#include "Color.h"
#include "Log_query.h"

#include <cstdio>
#include <string>
#include <cstdarg>
#include <ctime>
#include <sys/time.h>
#include <algorithm>
#include <queue>
#include <string>

namespace LOG
{
    class Specialized_logger
    {
     private:
     FILE *out=NULL;
     std::string name;
     Console_painter *console_painter;
     bool print_in_both;
     static int longest_name_length;
     int name_color;
     static const int NUMBER_OF_NAME_COLORS=16;
     static const int name_colors[NUMBER_OF_NAME_COLORS];

     public:
     Specialized_logger(std::string _name,Console_painter *_cp,FILE *_out=NULL,bool _file_and_console=false,int _name_color=0):
                        name(_name),console_painter(_cp),out(_out),print_in_both(_file_and_console),name_color(_name_color)
     {
      longest_name_length=std::max(longest_name_length,(int)name.length());
      name_color%=NUMBER_OF_NAME_COLORS;
     }

     void Log(Log_query *query);
     static void Reset_longest_name_length();

     private:
     void Print_query(Log_query *query);
     void Get_current_time(char *ret);
     int Get_number_of_arguments(const char *format);
    };
}

#endif // SPECIALIZED_LOGGER_H
