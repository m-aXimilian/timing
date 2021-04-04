cmake_minimum_required(VERSION 3.10)

# project name
project(timing)

# cpp standard
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "-Wall -std=c++17 -lpthread -ldl -lm")

add_subdirectory(${PROJECT_SOURCE_DIR}/sqlite3)
add_subdirectory(${PROJECT_SOURCE_DIR}/toml)

configure_file(${PROJECT_SOURCE_DIR}/config/project_config.toml
                config/project_config.toml)


# generate the executable
add_executable(${PROJECT_NAME}  ${PROJECT_SOURCE_DIR}/main.cc
                                ${PROJECT_SOURCE_DIR}/time_table.cc
                                ${PROJECT_SOURCE_DIR}/database_manager.cc)

target_include_directories(${PROJECT_NAME}  PUBLIC ${PROJECT_SOURCE_DIR}
                                            PUBLIC ${PROJECT_SOURCE_DIR}/sqlite3
                                            PUBLIC ${PROJECT_SOURCE_DIR}/toml
                                            PUBLIC ${PROJECT_SOURCE_DIR}/toml/include)

target_link_libraries(${PROJECT_NAME}   LINK_PUBLIC sqlite3
                                        LINK_PUBLIC cpptoml)


