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

    db->ConnectDatabase();
    std::cerr<<"new table:\t"<<db->NewDatabaseTable()<<std::endl;

    std::vector<std::string> fields{
        *db->table_columns_->get_as<std::string>("column_first"),
        *db->table_columns_->get_as<std::string>("column_second"),
        *db->table_columns_->get_as<std::string>("column_third"),
        //*database->table_columns_->get_as<std::string>("column_fourth"),
        // *database->table_columns_->get_as<std::string>("column_fifth")
    };

    std::vector<std::string> values{
        "2021-4-5",
        "1617977468",
        "1617977569",
        //"0",
        //"0",
    };

    std::cout<<"new entry:\t"<<db->NewEntry(fields, values)<<std::endl;

    std::string condition{"date='2021-4-5'"};
    std::string q{db->GetSelectCommand("*",condition)};

    std::cout<<q<<std::endl;
    
    db->SelectFromTable(q);

    for(auto i{0}; i < (int) db->query_result_->size(); i++) 
        std::cout<<db->query_result_->at(i)<<std::endl;
    
    LogIn();

    usleep(10000000);

    LogOut();
}


int tlog::TimeLog::LogIn(){

    time_table_->GetCurrentTime();

    std::string tmp{db_descriptor_->GetSelectCommand("*",std::string("date='")
            .append(time_table_->date_raw_time().first).append("'"))};
    
    db_descriptor_->SelectFromTable(tmp);

    size_t query_size{db_descriptor_->query_result_->size()};
    
    if (query_size == 2 ||
        last_action_ == tlog::action::LOG_IN) return -1;
    
    if (query_size == 0){
        std::vector<std::string> fields{
            *db_descriptor_->table_columns_->get_as<std::string>("column_first"),
            *db_descriptor_->table_columns_->get_as<std::string>("column_second"),
        };
        
        std::vector<std::string> values{
            time_table_->date_raw_time().first,
            time_table_->date_raw_time().second,
        };

        db_descriptor_->NewEntry(fields,values);

        last_action_ = tlog::action::LOG_IN;
    
        return 0;
    }

    UpdatePause(    time_table_->date_raw_time().second, 
                    db_descriptor_->query_result_->at(2),
                    db_descriptor_->query_result_->at(3) );

    last_action_ = tlog::action::LOG_IN;
    
    return 0;
}


int tlog::TimeLog::LogOut(){

    time_table_->GetCurrentTime();

    std::string tmp{db_descriptor_->GetSelectCommand("*",std::string("date='")
            .append(time_table_->date_raw_time().first).append("'"))};
    
    db_descriptor_->SelectFromTable(tmp);

    size_t query_size{db_descriptor_->query_result_->size()};

    if( query_size < 2 ||
        last_action_ == tlog::action::LOG_OUT) return -1;
    
    if( query_size < 3 ){
        std::vector<std::string> fields{*db_descriptor_->table_columns_->get_as<std::string>("column_fourth")};
        
        std::vector<std::string> values{std::string("0")};

        db_descriptor_->UpdateTable(fields, values, std::string("date='")
            .append(time_table_->date_raw_time().first).append("\'"));
    }
    
    std::vector<std::string> fields{*db_descriptor_->table_columns_->get_as<std::string>("column_third")};

    std::vector<std::string> values{time_table_->date_raw_time().second};

    db_descriptor_->UpdateTable(fields, values, std::string("date='")
            .append(time_table_->date_raw_time().first).append("\'"));

    last_action_ = tlog::action::LOG_OUT;

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
    
    std::vector<std::string> fields{*db_descriptor_->table_columns_->get_as<std::string>("column_fourth")};

    std::vector<std::string> values{std::to_string(new_pause)};

    return db_descriptor_->UpdateTable(fields, values, std::string("date='")
            .append(time_table_->date_raw_time().first).append("\'"));

}
