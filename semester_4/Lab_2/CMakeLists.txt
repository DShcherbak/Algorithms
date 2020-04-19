cmake_minimum_required(VERSION 3.15)
project(Lab_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab_2 main.cpp
            Binary_Search_Tree.hpp Binary_Search_Tree.h
            Red_Black_Tree.hpp Red_Black_Tree.h Tree.h
            Order_Statistic_Tree.hpp Order_Statistic_Tree.h
            ../sqlite3pp-master/headeronly_src/sqlite3pp.h
            ../testing/testing.cpp)