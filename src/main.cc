#include <service_init.h>

#include <iostream>
#include <memory>


int main(int argc, char *argv[]){

    if (argc < 2) {
        std::cout<<"insufficient number of argumets\n";
        return -1;
    }
    
    std::shared_ptr<init::Service> service_handler {std::make_shared<init::Service>("./config/project_config.toml")};

    service_handler->DispatchCommand(argv);
    
}
