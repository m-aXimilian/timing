#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <sqlite3/sqlite3.h>
#include <toml/include/cpptoml.h>

#include <string>
#include <vector>

namespace toml = cpptoml;

namespace {
    
    inline char* string_to_char(std::string& conv_string){
        return const_cast<char*>((conv_string).c_str());
    }
    
    /*static int callback(void *NotUsed, int argc, char **argv, char **azColName){
        int i;
        for(i = 0; i<argc; i++) {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }   */
}

namespace data{

    enum data_result{
        SUCCESS,
        FAIL,
        EXISTING
    };

    class Database
    {
    public:
        Database(std::string);
        
        virtual ~Database(){};
        
        int ConnectDatabase();
        
        inline void CloseDatabase(){
            sqlite3_close(db_descriptor_);
        };

        data_result NewDatabaseTable();

        // std::vector< std::vector<std::string> > QueryTable(std::string&);

        int SelectFromTable(std::string&);

        static int QueryCallback(void *output, int count, char **row_data, char **column_name);

        int NewEntry(std::vector<std::string>&, std::vector<std::string>&);

        std::string config_file_;

        sqlite3 *db_descriptor_;
        
        std::shared_ptr<toml::table> table_columns_;

        std::string create_command_;
        
        std::string table_name_;

        std::vector<std::string> *query_result_;

        int db_status_;

    private:
        std::string database_name_;
        
        std::string database_directory_;
        
        int n_cols_;

        std::vector<std::string> query_retainer_;
    };
}

#endif //DATABASE_MANAGER_H