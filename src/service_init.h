#ifndef SERVICE_INIT_H
#define SERVICE_INIT_H

#include <database_manager.h>
#include <time_log.h>
#include <time_table.h>
#include <toml/include/cpptoml.h>

#include <cstdlib>
#include <memory>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace toml = cpptoml;

namespace init{

class Service{
    public:
        Service(const std::string&);

        virtual ~Service(){};

        int DispatchCommand(char *cmd[]);

        int ChangeDatabaseEntry(const std::string&, const std::string&);
        
        std::shared_ptr<toml::table> config_file_;

        std::unordered_map< std::string, std::function<void()> > function_map_; 
        
    private:
        void SetValidCommands();

        int ValidateArgument(const std::string&);

        std::vector<std::string> valid_arguments_;

        std::shared_ptr<ti::TimeTable> time_table_;

        std::shared_ptr<tlog::TimeLog> time_log_;

        std::shared_ptr<data::Database> database_;

};



} // init

#endif //SERVICE_INIT_H
