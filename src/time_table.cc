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

std::string ti::TimeTable::FormatTimeToHHMM(std::time_t &intime, int GMT){
    struct tm *tmp = gmtime(&intime);
    
    auto minutes {tmp->tm_min};
    auto hours {(tmp->tm_hour+GMT)%24};
    
    std::string lead_zeros_min {ti::TimeTable::LeadingZeros(minutes)};
    std::string lead_zeros_hours {ti::TimeTable::LeadingZeros(hours)};
    
    return lead_zeros_hours
        .append(std::to_string(hours))
        .append(":")
        .append(lead_zeros_min)
        .append(std::to_string(minutes));
}

std::string ti::TimeTable::FormatSecondsToHHMM(std::time_t &intime){
    auto remainder {intime % 3600};
    auto minutes {remainder / 60};
    auto hours {(intime - remainder) / 3600};

    std::string lead_zeros_min {ti::TimeTable::LeadingZeros(minutes)};
    std::string lead_zeros_hours {ti::TimeTable::LeadingZeros(hours)};
    
    return (
        lead_zeros_hours.append(
        std::to_string( (intime - remainder) / 3600 ))
        .append(":")
        .append(lead_zeros_min)
        .append(std::to_string(remainder / 60)) 
        );
}
