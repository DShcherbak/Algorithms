//
// Created by sadoffnick on 19.04.20.
//
#include "../sqlite3pp-master/headeronly_src/sqlite3pp.h"
#include "../Folder.h"
#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

const char* db_file = "lab1.db";

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

template <class T>
bool test_for_correct_folders(T* Struct, const vector<Folder*>& included, const vector<Folder*>& excluded, const set<Folder*> &deleted = {}){
    for(auto fold : included)
        if(!deleted.count(fold)  && !Struct->find_element(fold))
            return false;
        else if(deleted.count(fold) && Struct->find_element(fold))
            return false;
    for(auto fold : excluded)
        if(Struct->find_element(fold))
            return false;
    return true;
}

