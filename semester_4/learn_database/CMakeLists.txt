cmake_minimum_required(VERSION 3.15)
project(learn_database)

set(CMAKE_CXX_STANDARD 14)

add_executable(learn_database main.cpp ../sqlite3pp-master/headeronly_src/sqlite3pp.h)

target_link_libraries(${PROJECT_NAME} sqlite3)