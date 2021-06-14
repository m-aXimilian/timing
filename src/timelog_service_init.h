#ifndef TIMELOG_SERVICE_INIT
#define TIMELOG_SERVICE_INIT

#include <database_manager.h>
#include <time_table.h>
#include <time_log.h>

#include <memory>
#include <string>

namespace init {
  class Service{
  public:
    Service();
    virtual ~Service(){};

    int CommandDispatch(const std::string&);

  private:
    std::shared_ptr<ti::TimeTable> time_table_;
    std::shared_ptr<data::Database> database_;
    std::shared_ptr<tlog::TimeLog> time_log_;
};
  
} // init

#endif //TIMELOG_SERVICE_INIT
