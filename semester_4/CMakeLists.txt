cmake_minimum_required(VERSION 3.15)
project(semester_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(semester_4 main.cpp
        Interface/Interface.hpp Interface/Interface.h
        Folder/Folder.h Folder/Folder.cpp
        Lab_1/hash_table.h Lab_1/hash_table.hpp
        Lab_2/Order_Statistic_Tree.h Lab_2/Order_Statistic_Tree.hpp
        Lab_3/Splay_Tree.hpp Lab_3/Splay_Tree.h
        Lab_4/Optimal_Binary_Tree.hpp Lab_4/Optimal_Binary_Tree.h
        Lab_5/Persistent_Tree.hpp Lab_5/Persistent_Tree.h)

target_link_libraries(${PROJECT_NAME} sqlite3)