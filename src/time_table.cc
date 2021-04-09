/*
ToDos:
[ ] write back to database
[ ] log out must be after log in -> separate file
[ ] multiple login/logouts add up to the break field
[ ] work time computes as end-start-break
[ ] day and year comparison of the time flags
*/

#include <time_table.h>

ti::TimeTable::TimeTable(){
    GetCurrentTime();

}

std::time_t ti::TimeTable::GetCurrentTime(){
    
    current_time_raw_ = std::time(nullptr);
    
    current_time_tm_ = gmtime(&current_time_raw_);

    date_raw_time_.first = std::to_string(current_time_tm_->tm_year+1900).append("-")
        .append(std::to_string(current_time_tm_->tm_mon+1)).append("-")
        .append(std::to_string(current_time_tm_->tm_mday));
    
    date_raw_time_.second = std::to_string(current_time_raw_);
    
    return current_time_raw_;
}