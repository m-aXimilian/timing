#ifndef TIME_LOG_H
#define TIME_LOG_H

#include <database_manager.h>
#include <time_table.h>

#include <memory>


namespace tlog{

    class TimeLog
    {
    public:
        TimeLog(std::shared_ptr<data::Database>,
                std::shared_ptr<ti::TimeTable> );
        virtual ~TimeLog();

        int LogIn();

        int LogOut();

        int UpdatePause(const std::string&, const std::string&, const std::string&);

        int WriteWorkTime(std::vector<std::string>*, std::time_t&);
        
    private:
        std::shared_ptr<data::Database> db_descriptor_;

        std::shared_ptr<ti::TimeTable> time_table_;

    };
    
} //tlog

#endif // TIME_LOG_H