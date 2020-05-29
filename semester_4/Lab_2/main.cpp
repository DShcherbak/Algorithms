#include <iostream>
#include "Binary_Search_Tree.h"
#include "Red_Black_Tree.h"
#include "Tree.h"
//#include "../Folder.h"
#include "Order_Statistic_Tree.h"
#include <cassert>
#include "../sqlite3pp-master/headeronly_src/sqlite3pp.h"
#include <vector>
#include <set>



const char* db_file = "lab2.db";

vector<Folder*> read_folders_from_database(const string &inc){
    vector <Folder*> fold = {};
    sqlite3pp::database db("lab2.db");
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

template <class T>
bool test_for_rank_folders(T* Struct, const vector<Folder*>& included, const vector<Folder*>& excluded, const set<Folder*> &deleted = {}){
    int size = Struct->get_size();
    for(int i = 1; i <= size; i++){
        auto fold = Struct->get_element(i);
        if(deleted.count(fold)  || !Struct->find_element(fold))
            return false;
    }
    for(auto fold : excluded)
        if(Struct->get_element_rank(fold) != -1)
            return false;
    return true;
}




int main() {
    vector <Folder*> included = read_folders_from_database("included");
    vector <Folder*> excluded = read_folders_from_database("excluded");
    print_folders(included, excluded);
    auto OST = new Order_Statistic_Tree<Folder*>;
    for(auto & fold : included)
        OST->insert_element(fold);
    assert(test_for_correct_folders(OST, included, excluded) && cout << "Test for insertion passed.\nTest for search passed\n");

    set <Folder*> deleted;
    OST->print_tree();
    for(auto & fold : included){
        if(randomInt(1,6) == 6){
            OST->delete_element(fold);
            deleted.insert(fold);
        }
    }

    assert(test_for_correct_folders(OST, included, excluded, deleted) && cout << "Test for deletion passed.\n");
    assert(test_for_rank_folders(OST, included, excluded, deleted) && cout << "Test for ranking passed.\n");
    return 0;
}
