#include <database_manager.h>
#include <time_table.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main(int argc, char *argv[]){

    init::Service service_handler {init::Service("./config/project_config.toml")};

    Service

    /*
    if( (argc != 2) ||
        (std::string(argv[1]) != "login" &&
         std::string(argv[1]) != "logout")) {
             std::cout<<"Pass ONE argument: \n \t \"login\" or \n \t \"logout\" \n";
             return -1;
         }
    
    // ti::TimeTable time_obj = ti::TimeTable(act);
    std::shared_ptr<ti::TimeTable> time_obj {std::make_shared<ti::TimeTable>(act)};
=======

    if( (argc != 2) ||
        (std::string(argv[1]) != "login" &&
         std::string(argv[1]) != "logout")) {
             std::cout<<"Pass ONE argument: \n \t \"login\" or \n \t \"logout\" \n";
             return -1;
         }
    
    std::shared_ptr<ti::TimeTable> time_obj {std::make_shared<ti::TimeTable>()};
>>>>>>> Stashed changes

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

    int query{database->SelectFromTable(q)};

    for(auto i{0}; i < database->query_result_->size(); i++) 
        std::cout<<database->query_result_->at(i);
    std::cout<<std::endl;
    
    /*
    for(auto &element: query) 
        std::cout<<element.at(0)<<std::endl;
    */

    std::cout<<time_log->LogOut()<<std::endl;
    */


    return 0;

}
