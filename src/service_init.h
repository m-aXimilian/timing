#ifndef SERVICE_INIT_H
#define SERVICE_INIT_H

#include <database_manager.h>
#include <time_log.h>
#include <time_table.h>

#include <cstdlib>
#include <memory>
#include <string>

namespace init{

class Service{
    public:
        Service(const std::string&);
        virtual ~Service(){};

        int DispatchCommand(const std::string&);
    private:
        std::shared_ptr<ti::TimeTable> time_table_;
        std::shared_ptr<tlog::TimeLog> time_log_;
        std::shared_ptr<data::Database> database_;

};



} // init

#endif //SERVICE_INIT_H
