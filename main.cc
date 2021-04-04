#include <database_manager.h>
#include <time_table.h>

#include <cstdlib>
#include <memory>

int main(int argc, char *argv[]){
    ti::action act = ti::action::LOG_IN;
    
    // ti::TimeTable time_obj = ti::TimeTable(act);
    std::shared_ptr<ti::TimeTable> time_obj {std::make_shared<ti::TimeTable>(act)};

    std::shared_ptr<data::Database> database {std::make_shared<data::Database>("./config/project_config.toml")};
}
