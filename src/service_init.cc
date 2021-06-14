#include <service_init.h>
#include <time_log.h>
#include <time_table.h>

#include <cstdlib>
#include <memory>
#include <string>

init::Service::Service(const std::string& path_to_conf){

    time_table_ = std::make_shared<ti::TimeTable>();

    database_ = std::make_shared<data::Database>(path_to_conf);

    time_log_ = std::make_shared<tlog::TimeLog>(database_, time_table_);
}

int init::Service::DispatchCommand(const std::string& cmd){

    if (cmd != "login" && cmd != "logout") return -1;

    if (cmd == "login") {
        time_log_->LogIn();
        return 0;
    }

    time_log_->LogOut();

    return 0;
    
}