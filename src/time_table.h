#ifndef TIME_TABLE_H
#define TIME_TABLE_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <utility>
#include <stdio.h>
#include <string>

namespace ti
{   
    /* belongs to time_log
    enum action{
        LOG_IN,
        LOG_OUT
    };
    */

    class TimeTable{
    public:
        TimeTable();

        virtual ~TimeTable(){};
        
        std::time_t GetCurrentTime();
        
        inline std::pair<std::string, std::string> date_raw_time(){
            return date_raw_time_;
        }

        inline std::time_t StringToTime(const std::string &string_time){
            
            if (string_time.size() != 10) return -1;

            std::string::size_type sz;
            return (std::time_t) std::stol(string_time,&sz);
        }
        
    private:        
        std::time_t current_time_raw_;
        
        struct tm *current_time_tm_;

        std::pair<std::string,std::string> date_raw_time_;
    };
} // namespace ti

#endif // TIME_TABLE_H