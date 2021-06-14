#include <time_table.h>

ti::TimeTable::TimeTable(ti::action &action){
    std::cout<<"TimeTable was called with "<<action<<" at "<<this->get_time()<<std::endl<<
    "corresponding UTC:\t"<<std::put_time(std::gmtime(&this->current_time_raw_), "%c %Z")<<std::endl<<
    "and local:\t\t"<<std::put_time(std::localtime(&this->current_time_raw_), "%c %Z")<<std::endl<<
    "the day:\t\t"<<ptm->tm_yday<<std::endl<<
    "and year:\t\t"<<ptm->tm_year+1900<<std::endl<<
    "table formatted:\t"<<ptm->tm_year+1900<<"-"<<ptm->tm_mon+1<<"-"<<ptm->tm_mday<<std::endl;
    
}

std::time_t ti::TimeTable::get_time(){
    current_time_raw_ = std::time(nullptr);
    ptm = gmtime(&current_time_raw_);
    return current_time_raw_;
}
