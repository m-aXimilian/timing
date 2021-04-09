#include <database_manager.h>
#include <time_table.h>
#include <time_log.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


int main(int argc, char *argv[]){
    // ti::TimeTable time_obj = ti::TimeTable(act);
    std::shared_ptr<ti::TimeTable> time_obj {std::make_shared<ti::TimeTable>()};

    std::shared_ptr<data::Database> database {std::make_shared<data::Database>("./config/project_config.toml")};

    std::shared_ptr<tlog::TimeLog> time_log {std::make_shared<tlog::TimeLog>(database, time_obj)};

    if(database->db_status_ == 0) database->CloseDatabase();

}
