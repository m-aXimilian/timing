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

    db_status_ = sqlite3_open(tmp,&db_descriptor_);

    return db_status_;
}


data::data_result data::Database::NewDatabaseTable(){
    auto conf{toml::parse_file(config_file_.c_str())};

    auto table{conf->get_table("create_table")};

    table_columns_ = table;

    table_name_ = *table->get_as<std::string>("table_name");
    std::string cols{*table->get_as<std::string>("number_column")};
    n_cols_ = std::stoi(cols, nullptr, 0);

    auto create_command{
        *table->get_as<std::string>("create_command") + " " + \
        *table->get_as<std::string>("table_name") + " (\n" + \
        *table->get_as<std::string>("column_first") + " " + \
        *table->get_as<std::string>("column_first_type") + ",\n" + \
        *table->get_as<std::string>("column_second") + " " + \
        *table->get_as<std::string>("column_second_type") + ",\n" + \
        *table->get_as<std::string>("column_third") + " " + \
        *table->get_as<std::string>("column_third_type") + ",\n" + \
        *table->get_as<std::string>("column_fourth") + " " + \
        *table->get_as<std::string>("column_fourth_type") + ",\n" + \
        *table->get_as<std::string>("column_fifth") + " " + \
        *table->get_as<std::string>("column_fifth_type") + ");"
    };

    create_command_ = std::move(create_command);

    char *tmp = string_to_char(create_command_);

    char *sqlerr{0};
    int e = sqlite3_exec(db_descriptor_, tmp, NULL, 0, &sqlerr);

    return (e==0) ? data::data_result::SUCCESS : data::data_result::FAIL;
}


std::vector< std::vector<std::string> > data::Database::QueryTable(std::string &query_command){
    // char *query = string_to_char(query_command);
    std::vector< std::vector<std::string> > result(n_cols_, std::vector<std::string>());

    sqlite3_stmt *stmt;

    if (db_status_ == SQLITE_OK){
        
        sqlite3_prepare(db_descriptor_, string_to_char(query_command), -1, &stmt, NULL);

        while (sqlite3_column_text(stmt,0)){
            for (auto i{0}; i < n_cols_; i++)
                result.at(i).push_back(std::string((char *)sqlite3_column_text(stmt, i)));

            sqlite3_step(stmt);
        }

    }

    return result;
}


std::vector<std::string> QueryCallback(void *NotUsed, int argc, char **argv, char **azColName){
    
    std::vector<std::string> result;
    
    std::string tmp;

    for(int i = 0; i < argc; i++) {
        
        tmp = (std::string) azColName[i] + (std::string) argv[i];
        std::cout << azColName[i] << ": " << argv[i] << std::endl;
    
    }
}


int data::Database::NewEntry(std::vector<std::string> &fields, \
        std::vector<std::string> &values){


    std::string insert_command{"INSERT INTO " + table_name_ + " ("};

    if( fields.size() != values.size() ||
        fields.size() > (size_t) n_cols_ ||
        values.size() > (size_t) n_cols_ )
        return data::data_result::FAIL;
    
    for(std::vector<std::string>::iterator it = fields.begin(); it != fields.end(); it++){
        insert_command.append("\'").append(*it).append("\',");
    }
    insert_command.replace(insert_command.end()-1,insert_command.end(),")");

    insert_command.append(" VALUES (");

    for(std::vector<std::string>::iterator it = values.begin(); it != values.end(); it++){
        insert_command.append("\'").append(*it).append("\',");
    }
    insert_command.replace(insert_command.end()-1,insert_command.end(),")");
    char *tmp{string_to_char(insert_command)};

    char *sqlerr{0};
    int insertion_status{sqlite3_exec(db_descriptor_, tmp, NULL, 0, &sqlerr)};

    return insertion_status;
}
