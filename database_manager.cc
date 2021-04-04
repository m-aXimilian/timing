#include <database_manager.h>

#include <sqlite3/sqlite3.h>
#include <toml/include/cpptoml.h>

#include <iostream>
#include <string.h>

namespace toml = cpptoml;

data::Database::Database(std::string config_file){
    config_file_ = config_file; // save given string
    
    auto conf{toml::parse_file(config_file_.c_str())}; // parse the config file

    auto filename_tmp{*conf->get_qualified_as<std::string>("database.name")};
    auto filepath_tmp{*conf->get_qualified_as<std::string>("database.path")};

    database_name_ = std::move(filename_tmp);
    database_directory_ = std::move(filepath_tmp);

    std::cout<<"name:\t"<<database_name_<<"\ndir:\t"<<database_directory_<<std::endl;
}