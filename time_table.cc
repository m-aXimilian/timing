/*
ToDos:
database:
        | day x | day x+1 | ...
start   |       |         | ...
end     |       |         | ...
break   |       |         | ...
[ ] write back to database
[ ] log out must be after log in
[ ] multiple login/logouts add up to the break field
[ ] work time computes as end-start-break
[ ] day and year comparison of the time flags
*/

#include <time_table.h>

ti::TimeTable::TimeTable(ti::action &action){
    std::cout<<"TimeTable was called with "<<action<<" at "<<this->get_time()<<std::endl<<
    "corresponding UTC:\t"<<std::put_time(std::gmtime(&this->current_time_raw_), "%c %Z")<<std::endl<<
    "and local:\t\t"<<std::put_time(std::localtime(&this->current_time_raw_), "%c %Z")<<std::endl<<
    "the day:\t\t"<<ptm->tm_yday<<std::endl<<
    "and year:\t\t"<<ptm->tm_year+1900<<std::endl;
    
}

std::time_t ti::TimeTable::get_time(){
    current_time_raw_ = std::time(nullptr);
    ptm = gmtime(&current_time_raw_);
    return current_time_raw_;
}