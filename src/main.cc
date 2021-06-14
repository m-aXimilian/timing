#include <service_init.h>

//#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main(int argc, char *argv[]){

    if( (argc != 2) ||
        (std::string(argv[1]) != "login" &&
         std::string(argv[1]) != "logout")) {
             std::cout<<"Pass ONE argument: \n \t \"login\" or \n \t \"logout\" \n";
             return -1;
         }
    
    std::shared_ptr<init::Service> service_handler {std::make_shared<init::Service>("./config/project_config.toml")};

    service_handler->DispatchCommand(argv[1]);

}
