#include <time_log.h>
#include <toml/include/cpptoml.h>

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include <unistd.h>


tlog::TimeLog::TimeLog( std::shared_ptr<data::Database> db,
                        std::shared_ptr<ti::TimeTable> time){

    db_descriptor_ = db;

    time_table_ = time; 

    db_descriptor_->ConnectDatabase();

}


tlog::TimeLog::~TimeLog(){
    if ( db_descriptor_ ) db_descriptor_->CloseDatabase();
}


int tlog::TimeLog::LogIn(){

    time_table_->GetCurrentTime();

    std::string tmp{db_descriptor_->GetSelectCommand("*",std::string("date='")
            .append(time_table_->date_raw_time().first).append("'"))};
    
    db_descriptor_->SelectFromTable(tmp);

    size_t query_size{db_descriptor_->query_result_->size()};
    
    if (query_size == 2) return -1;
    
    if (query_size == 0){

        std::vector<std::string> fields{
            //"date", "login"
            *db_descriptor_->table_columns_->get_as<std::string>("column_first"),
            *db_descriptor_->table_columns_->get_as<std::string>("column_second"),
            *db_descriptor_->table_columns_->get_as<std::string>("column_third"),
            *db_descriptor_->table_columns_->get_as<std::string>("column_fourth"),
            *db_descriptor_->table_columns_->get_as<std::string>("column_fifth"),
            *db_descriptor_->table_columns_->get_as<std::string>("column_sixth")
        };

        std::vector<std::string> values{
            time_table_->date_raw_time().first,
            time_table_->date_raw_time().second,
            "0",
            "0",
            "0",
            "IN"
        };

        db_descriptor_->NewEntry(fields,values);
    
        return 0;
    }

    if(db_descriptor_->query_result_->back() != "OUT") {
        std::cerr<<"you're already logged in"<<std::endl;
        return -1;
    };    

    UpdatePause(    time_table_->date_raw_time().second, 
                    db_descriptor_->query_result_->at(2),
                    db_descriptor_->query_result_->at(3) );    
    
    return 0;
}


int tlog::TimeLog::LogOut(){

    time_table_->GetCurrentTime();

    std::string tmp{db_descriptor_->GetSelectCommand("*",std::string("date='")
            .append(time_table_->date_raw_time().first).append("'"))};
    
    db_descriptor_->SelectFromTable(tmp);

    if(db_descriptor_->query_result_->back() != "IN") {
        std::cerr<<"you're not logged in"<<std::endl;
        return -1;
    };

    size_t query_size{db_descriptor_->query_result_->size()};

    if( query_size < 2) return -1;
    
    if( query_size < 3 ){
        std::vector<std::string> fields{*db_descriptor_->table_columns_->get_as<std::string>("column_fourth")};
        
        std::vector<std::string> values{std::string("0")};

        db_descriptor_->UpdateTable(fields, values, std::string("date='")
            .append(time_table_->date_raw_time().first).append("\'"));
    }
    
    std::vector<std::string> fields{
        *db_descriptor_->table_columns_->get_as<std::string>("column_third"),
        *db_descriptor_->table_columns_->get_as<std::string>("column_sixth")
        };

    std::vector<std::string> values{
        time_table_->date_raw_time().second,
        "OUT"
        };

    db_descriptor_->UpdateTable(fields, values, std::string("date='")
            .append(time_table_->date_raw_time().first).append("\'"));

    std::time_t last_logout{time_table_->StringToTime(time_table_->date_raw_time().second)};
    
    WriteWorkTime(db_descriptor_->query_result_, last_logout);
    
    return 0;
}


int tlog::TimeLog::WriteWorkTime(std::vector<std::string> *query, std::time_t &last_logout){

    if ( query->size() < 3 ) return -1;

    std::vector<std::time_t> times;


    for (std::vector<std::string>::iterator it = query->begin(); it != query->begin()+5; ++it){
        times.push_back(time_table_->StringToTime(*it));
    }

    std::vector<std::string> values{std::to_string(last_logout - times.at(1) - times.at(3))};
  
    std::vector<std::string> fields{*db_descriptor_->table_columns_->get_as<std::string>("column_fifth")};

    db_descriptor_->UpdateTable(fields, values, std::string("date='")
            .append(time_table_->date_raw_time().first).append("\'"));
  
    return 0;
    
}


int tlog::TimeLog::UpdatePause( const std::string &current_login,
                                const std::string &last_logout, 
                                const std::string &current_pause){

    std::vector<std::time_t> times{
        time_table_->StringToTime(current_login),
        time_table_->StringToTime(last_logout),
        time_table_->StringToTime(current_pause),
    };

    if ( times.at(0) < times.at(1) ) return -1;

    std::time_t new_pause{
        times.at(0) - times.at(1) + times.at(2)
    };
    
    std::vector<std::string> fields{
        *db_descriptor_->table_columns_->get_as<std::string>("column_fourth"),
        *db_descriptor_->table_columns_->get_as<std::string>("column_sixth")
        };

    std::vector<std::string> values{
        std::to_string(new_pause),
        "IN"
        };

    return db_descriptor_->UpdateTable(fields, values, std::string("date='")
            .append(time_table_->date_raw_time().first).append("\'"));

}
