#include <service_init.h>
#include <time_log.h>
#include <time_table.h>

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string>


#include <iostream>
#include <stdio.h>

init::Service::Service(const std::string& path_to_conf){

    time_table_ = std::make_shared<ti::TimeTable>();

    database_ = std::make_shared<data::Database>(path_to_conf);

    time_log_ = std::make_shared<tlog::TimeLog>(database_, time_table_);

    auto conf{toml::parse_file(path_to_conf.c_str())};

    config_file_ = conf;

    SetValidCommands();

}


void init::Service::SetValidCommands(){

    auto arguments {config_file_->get_table("arguments")->get_array_of<std::string>("first_arguments")};

    for (const auto& val : *arguments) valid_arguments_.push_back(val);
}


int init::Service::ValidateArgument(const std::string& command){
    
    auto f {
        std::find(valid_arguments_.begin(), valid_arguments_.end(), command)
    };

    if ( f == valid_arguments_.end()) return -1;

    return 0;
}


int init::Service::DispatchCommand(char *cmd[]){

    //if (cmd != "login" && cmd != "logout") return -1;

    if ( ValidateArgument(cmd[1]) != 0 ) return -1;

    if (std::string(cmd[1]) == "login") {
        time_log_->LogIn();
        return 0;
    }

    time_log_->LogOut();

    return 0;
    
}