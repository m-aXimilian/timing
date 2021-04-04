#include <database_manager.h>

#include <sqlite3/sqlite3.h>
#include <toml/include/cpptoml.h>

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

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

int data::Database::ConnectDatabase(){
    std::string gen = database_directory_ + "/" + database_name_;

    char *tmp = string_to_char(gen);

    gen.empty();

    return sqlite3_open(tmp,&db_descriptor_);
}

data::data_result data::Database::NewDatabaseTable(){
    auto conf{toml::parse_file(config_file_.c_str())};

    auto table{conf->get_table("create_table")};

    auto create_command{
        *table->get_as<std::string>("create_command") + " " + \
        *table->get_as<std::string>("table_name") + " (\n" + \
        *table->get_as<std::string>("column_first") + ",\n" + \
        *table->get_as<std::string>("column_second") + ",\n" + \
        *table->get_as<std::string>("column_third") + ",\n" + \
        *table->get_as<std::string>("column_fourth") + ",\n" + \
        *table->get_as<std::string>("column_fifth") + ");"  
    };

    create_command_ = std::move(create_command);

    char *tmp = string_to_char(create_command_);

    char *sqlerr{0};
    int e = sqlite3_exec(db_descriptor_, tmp, callback, 0, &sqlerr);

    return (e==0) ? data::data_result::SUCCESS : data::data_result::FAIL;
}