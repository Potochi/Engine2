#include "../include/Log_query.h"

namespace LOG
{
    Log_query Make_log_query(std::string name,Log_type type,const char *format,...)
    {
     Log_query q;
     q.name=name;
     q.type=type;

     int n_args=Get_number_of_arguments(format);
     va_list args;
     va_start(args,n_args);

     char buffer[100];
     vsprintf(buffer,format,args);
     q.log=buffer;

     return q;
    }

    int Get_number_of_arguments(const char *format)
    {
     int i=0,ret=0;
     while(format[i]!=NULL)
           {
            if(format[i]=='%')
               ret++;
            i++;
           }
     return ret;
    }
}
