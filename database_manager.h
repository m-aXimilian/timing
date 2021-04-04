#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <string>

namespace data{
    class Database
    {
    public:
        Database(std::string);
        virtual ~Database(){};
        std::string config_file_;
    private:
        std::string database_name_;
        std::string database_directory_;
    };
}

#endif //DATABASE_MANAGER_H