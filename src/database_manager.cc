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

    query_result_ = &query_retainer_;

}


int data::Database::ConnectDatabase(){

    std::string gen = database_directory_ + "/" + database_name_;

    char *tmp = string_to_char(gen);

    gen.empty();

    db_status_ = sqlite3_open(tmp,&db_descriptor_);

    auto conf{toml::parse_file(config_file_.c_str())};

    auto table{conf->get_table("create_table")};

    table_columns_ = table;

    table_name_ = *table->get_as<std::string>("table_name");

    std::string cols{*table_columns_->get_as<std::string>("number_column")};

    n_cols_ = std::stoi(cols, nullptr, 0);

    NewDatabaseTable();

    return db_status_;
}


data::data_result data::Database::NewDatabaseTable(){

    auto create_command{
        *table_columns_->get_as<std::string>("create_command") + " " + \
        *table_columns_->get_as<std::string>("table_name") + " (\n" + \
        *table_columns_->get_as<std::string>("column_first") + " " + \
        *table_columns_->get_as<std::string>("column_first_type") + ",\n" + \
        *table_columns_->get_as<std::string>("column_second") + " " + \
        *table_columns_->get_as<std::string>("column_second_type") + ",\n" + \
        *table_columns_->get_as<std::string>("column_third") + " " + \
        *table_columns_->get_as<std::string>("column_third_type") + ",\n" + \
        *table_columns_->get_as<std::string>("column_fourth") + " " + \
        *table_columns_->get_as<std::string>("column_fourth_type") + ",\n" + \
        *table_columns_->get_as<std::string>("column_fifth") + " " + \
        *table_columns_->get_as<std::string>("column_fifth_type") + ",\n" +\
        *table_columns_->get_as<std::string>("column_sixth") + " " + \
        *table_columns_->get_as<std::string>("column_sixth_type") + ");"
    };

    create_command_ = std::move(create_command);

    char *tmp = string_to_char(create_command_);

    char *sqlerr{0};

    int e = sqlite3_exec(db_descriptor_, tmp, NULL, 0, &sqlerr);

    return (e==0) ? data::data_result::SUCCESS : data::data_result::FAIL;
}


int data::Database::SelectFromTable(std::string &query_command){
    
    std::string tmp{query_command.back()};

    std::string term{";"};

    if (tmp.compare(term) != 0) return -1;

    query_result_->clear();
    
    void *tmp_res = (void*) query_result_;

    char *sqlerr{0};
    
    char *tmp_command{string_to_char(query_command)};
    
    sqlite3_exec(db_descriptor_, tmp_command, data::Database::QueryCallback, tmp_res, &sqlerr);
    
    return 0;
}


int data::Database::QueryCallback(void *exec_relay, int count, char **row_data, char **column_name){
    
    std::vector<std::string> *res = (std::vector<std::string>*) exec_relay;

    std::vector<std::string> data_conversion;

    int i{0};

    while(row_data[i] != NULL){
        data_conversion.push_back(row_data[i]);
        i++;
    }

    if (row_data[5] != NULL)
        data_conversion.push_back(row_data[5]);

    for(auto &e: data_conversion)
        res->push_back(e);
    
    return 0;
} 


int data::Database::NewEntry(std::vector<std::string> &fields, 
        std::vector<std::string> &values){

    std::string insert_command{"INSERT INTO " + table_name_ + " ("};

    if( fields.size() != values.size() ||
        fields.size() > (size_t) n_cols_ ||
        values.size() > (size_t) n_cols_ )

        return -1;
    
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


int data::Database::UpdateTable(std::vector<std::string> &fields, 
        std::vector<std::string> &values,
        const std::string &condition){



    if( fields.size() != values.size() ||
        fields.size() > (size_t) n_cols_ ||
        values.size() > (size_t) n_cols_  ||
        condition.empty()) return -1;

    std::string update_command{"UPDATE " + table_name_ + " SET "};

    
    for(size_t i = 0; i < fields.size(); i++){
        update_command.append(fields.at(i))
            .append("=")
            .append("\'")
            .append(values.at(i))
            .append("\', ");
    } 
    
    update_command.erase(update_command.end()-2, update_command.end());
    update_command.append(" WHERE ").append(condition).append(";");
  
    char *tmp{string_to_char(update_command)};

    char *sqlerr{0};

    return sqlite3_exec(db_descriptor_, tmp, NULL, 0, &sqlerr);

    return 0;
}


std::string data::Database::GetSelectCommand(const std::string &select,
        const std::string &condition){
    
    std::string ret{std::string("SELECT ").append(select).append(" FROM ").append(table_name_)};

    if(condition.empty())
        return ret.append(";");

    return ret.append(" WHERE ").append(condition).append(";");
}