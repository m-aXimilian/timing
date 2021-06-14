#include <timelog_service_init>

#include <stdio.h>

init::Service::Service(const std::string& path_to_config){

  time_table_ = std::make_shared<ti::TimeTable>();

  database_ = std::make_shared<data::Database>(path_to_config);

  time_log_ = std::make_shared<tlog::TimeLog>(database_, time_table_);

}

int init::Service::CommandDispatch(const std::string& commmand){

  if (command != "login" && command != "logout") {
    std::cerr<<""Pass ONE argument: \n \t \"login\" or \n \t \"logout\" \n";

    return -1;
  }
  
  command == "login" ? time_log_->LogIn() : time_log_->LogOut();

  return 0;

}
