#include "hash_table.h"
#include "../sqlite3pp-master/headeronly_src/sqlite3pp.h"
#include "Folder.h"
#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <random>

using namespace std;

const char* db_file = "lab1.db";

int randomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

vector<Folder*> read_folders_from_database(const string &inc){
    vector <Folder*> fold = {};
    sqlite3pp::database db("lab1.db");
    sqlite3pp::query qry(db, "SELECT name FROM Folders WHERE included = ?1");
    qry.bind(1, inc, sqlite3pp::nocopy);
    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
        for (int j = 0; j < qry.column_count(); ++j) {
            string a =(*i).get<char const*>(j);
            auto new_folder = new Folder(a);
            fold.push_back(new_folder);
            sqlite3pp::query qry(db, "SELECT name FROM Files WHERE folder_name = ?1");
            qry.bind(1, a, sqlite3pp::nocopy);
            for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
                for (int j = 0; j < qry.column_count(); ++j) {
                    string b =(*i).get<char const*>(j);
                    File* new_file = new File(b);
                    new_folder->files.push_back(new_file);
                }
            }
        }
    }
    return fold;
}

void print_folders(const vector <Folder*> &included, const vector <Folder*> &excluded){
    cout << "INCLUDED\n";
    for(auto inc : included){
        cout << inc->name << ":\n";
        for(auto f : inc->files){
            cout << "\t" << f->name << "\n";
        }
    }
    cout << "EXCLUDED\n";
    for(auto inc : excluded){
        cout << inc->name << ":\n";
        for(auto f : inc->files){
            cout << "\t" << f->name << "\n";
        }
    }
}


bool test_for_correct_folders(HashTable<Folder*>* HT, const vector<Folder*>& included, const vector<Folder*>& excluded, const set<Folder*> &deleted = {}){
    for(auto fold : included)
        if(!deleted.count(fold)  && !HT->search_element(fold)){
            cout << "A" << endl;
            return false;
        }
        else if(deleted.count(fold) && HT->search_element(fold)){
            cout << "B" << endl;
            return false;
        }
    for(auto fold : excluded)
        if(HT->search_element(fold)){
            cout << "C" << endl;
            return false;
        }
    return true;
}

int main() {

    vector <Folder*> included = read_folders_from_database("included");
    vector <Folder*> excluded = read_folders_from_database("excluded");
    //print_folders(included, excluded);
    auto HT = new HashTable<Folder*>;
    for(auto & fold : included)
        HT->insert_element(fold);
    assert(test_for_correct_folders(HT, included, excluded) && cout << "Test for insertion passed.\nTest for search passed\n");
    set <Folder*> deleted;
    for(auto & fold : included){
        if(randomInt(1,6) == 6){
            HT->delete_element(fold);
            deleted.insert(fold);
        }
    }
    assert(test_for_correct_folders(HT, included, excluded, deleted) && cout << "Test for deletion passed.\n");



    return 0;
}

/*cmake_minimum_required(VERSION 3.15)
project(Lab_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab_1 main.cpp ../sqlite3pp-master/headeronly_src/sqlite3pp.h
                hash_table.hpp hash_table.h
                Folder.cpp Folder.h)

target_link_libraries(${PROJECT_NAME} sqlite3)*/
