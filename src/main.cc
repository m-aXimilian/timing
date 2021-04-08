#include <database_manager.h>
#include <time_table.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main(int argc, char *argv[]){
    ti::action act = ti::action::LOG_IN;
    
    // ti::TimeTable time_obj = ti::TimeTable(act);
    std::shared_ptr<ti::TimeTable> time_obj {std::make_shared<ti::TimeTable>(act)};

    std::shared_ptr<data::Database> database {std::make_shared<data::Database>("./config/project_config.toml")};

    int db {database->ConnectDatabase()};

    std::cerr<<"new db status:\t"<<database->NewDatabaseTable()<<std::endl;

    std::vector<std::string> fields{
        *database->table_columns_->get_as<std::string>("column_first"),
        *database->table_columns_->get_as<std::string>("column_second"),
        *database->table_columns_->get_as<std::string>("column_third"),
        //*database->table_columns_->get_as<std::string>("column_fourth"),
        // *database->table_columns_->get_as<std::string>("column_fifth")
    };

    std::vector<std::string> values{
        "2021-4-5",
        "1617624164",
        "1617624199",
        //"0",
        //"0",
    };

    std::cout<<"new entry:\t"<<database->NewEntry(fields, values)<<std::endl;

    std::string q{"SELECT * FROM " + database->table_name_ + ";"};

    std::cout<<q<<std::endl;

    std::vector< std::vector<std::string> > query{database->QueryTable(q)};

    std::cout<<"query dim:\t"<<query.size()<<
    "query_ dim:\t"<<query.at(0).size()<<std::endl;

    /*
    for(auto &element: query) 
        std::cout<<element.at(0)<<std::endl;
    */

    if(db == 0) database->CloseDatabase();

}
