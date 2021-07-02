#include <time_table.h>

#include <iostream>
#include <memory>
#include <string>

int main(){
    ti::TimeTable m_table {ti::TimeTable()};

    auto in = m_table.StringToTime("1625551074");

    std::cout<<m_table.FormatTimeToHHMM(in,2)<<std::endl;

    return 0;
}