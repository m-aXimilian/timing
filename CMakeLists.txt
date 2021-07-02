cmake_minimum_required(VERSION 3.10)

# project name
project(timing)

# cpp standard
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17 -lpthread -ldl -lm")

add_subdirectory(${PROJECT_SOURCE_DIR}/sqlite3)
add_subdirectory(${PROJECT_SOURCE_DIR}/toml)

configure_file(${PROJECT_SOURCE_DIR}/config/project_config.toml
                config/project_config.toml)

# generate the executable
add_executable(${PROJECT_NAME}  ${PROJECT_SOURCE_DIR}/src/main.cc
                                ${PROJECT_SOURCE_DIR}/src/time_log.cc
                                ${PROJECT_SOURCE_DIR}/src/time_table.cc
                                ${PROJECT_SOURCE_DIR}/src/database_manager.cc
                                ${PROJECT_SOURCE_DIR}/src/service_init.cc)
                                
add_executable(test ${PROJECT_SOURCE_DIR}/src/test.cc
                    ${PROJECT_SOURCE_DIR}/src/time_table.cc)

target_include_directories(test  PUBLIC ${PROJECT_SOURCE_DIR}
                    PUBLIC ${PROJECT_SOURCE_DIR}/src
                    PUBLIC ${PROJECT_SOURCE_DIR}/sqlite3
                    PUBLIC ${PROJECT_SOURCE_DIR}/toml
                    PUBLIC ${PROJECT_SOURCE_DIR}/toml/include)                    
                    
target_include_directories(${PROJECT_NAME}  PUBLIC ${PROJECT_SOURCE_DIR}
                                            PUBLIC ${PROJECT_SOURCE_DIR}/src
                                            PUBLIC ${PROJECT_SOURCE_DIR}/sqlite3
                                            PUBLIC ${PROJECT_SOURCE_DIR}/toml
                                            PUBLIC ${PROJECT_SOURCE_DIR}/toml/include)

target_link_libraries(${PROJECT_NAME}   LINK_PUBLIC sqlite3
                                        LINK_PUBLIC cpptoml)


