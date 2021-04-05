#ifndef TIME_TABLE_H
#define TIME_TABLE_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <stdio.h>


namespace ti
{   
    enum action{
        LOG_IN,
        LOG_OUT
    };

    class TimeTable{
    public:
        TimeTable(action &action);
        virtual ~TimeTable(){};
    private:
        int my_int;
        std::time_t current_time_raw_;
        struct tm *ptm;
        std::time_t get_time();
    };
} // namespace ti

#endif // TIME_TABLE_H