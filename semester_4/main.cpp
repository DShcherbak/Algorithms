#include "Lab_1/hash_table.h"
#include "Lab_2/Order_Statistic_Tree.h"
#include "Lab_3/Splay_Tree.h"
#include "Lab_4/Optimal_Binary_Tree.h"
#include "Interface/Interface.h"
#include "sqlite3pp-master/headeronly_src/sqlite3pp.h"
//#include "Folder/Folder.h"
#include <iostream>
#include <vector>


using namespace std;

vector <string> databases = {"Exit", "None", "../databases/small_database.db", "../databases/big_database.db"};

int choose_database(){
    cout << "Оберіть базу даних для зчитки: " << endl;
    cout << "(1) Без бази даних\n";
    cout << "(2) Мала база\n";
    cout << "(3) Велика база\n";
    cout << "(0) Повернутися до головного меню\n";
    cout << "Ваш вибір: ";
    char choice;

    cin >> choice;
    int chosen_db;
    if(!isdigit(choice)){
        cout << "Некоректні дані: " << choice << endl;
        chosen_db = -1;
    }
    else
        chosen_db = (int) choice - '0';
    return chosen_db;
}

Information_storage* read_database(const string &database) {
    vector <Folder*> fold = {};
    sqlite3pp::database db(database.c_str());
    sqlite3pp::query qry(db, "SELECT * FROM Folders");
    auto info_stor = new Information_storage();
    int folder_id;
    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
        folder_id = (*i).get<int>(0);
        string name = (*i).get<char const*>(1);
        int size = (*i).get<int>(2);

        sqlite3pp::query qry1(db, "SELECT * FROM Files WHERE folder_id = ?1");
        qry1.bind(1, folder_id);
        vector <shared_ptr<File>> files;
        for (sqlite3pp::query::iterator j = qry1.begin(); j != qry1.end(); ++j) {
            string file_name = (*j).get<char const*>(1);
            int file_size = (*j).get<int>(2);
            File* file = new File(file_name);
            file->size = file_size;
            files.emplace_back(file);
        }
        shared_ptr<Folder> folder(new Folder(name, files));
        auto wrapped_element = new Wrapped_folder;
        wrapped_element->element = folder;
        wrapped_element->included = (*i).get<int>(3);
        wrapped_element->deleted = (*i).get<int>(4);
        info_stor->elements.push_back(wrapped_element);
        if(wrapped_element->included)
            info_stor->included.insert(folder->name);
        else
            info_stor->excluded.insert(folder->name);
        if(wrapped_element->deleted)
            info_stor->deleted.insert(folder->name);
    }
    return info_stor;
}

template <class Data_Structure>
void create_interface_and_perform(Information_storage* info_storage, Data_Structure* data_structure){
    auto interface = new Interface<Data_Structure, Folder>(info_storage, data_structure);
    interface->perform();
    delete interface;
}

void get_data_and_perform(int choice){
    int chosen_db = choose_database();
    Information_storage* info_storage;
    vector <shared_ptr<Folder>> base;
    if(chosen_db < 1)
        return;
    else if(chosen_db > 1){
        string database = databases[chosen_db];
        info_storage = read_database(database);
        for (Wrapped_folder* data_element : info_storage->elements) {
            if (data_element->included) {
                base.emplace_back(data_element->element);
            }
        }
    }
    else{
        info_storage = new Information_storage;
        for (Wrapped_folder* data_element : info_storage->elements) {
            if (data_element->included) {
                base.emplace_back(data_element->element);
            }
        }
    }

    if(choice == 1){
        auto structure = new HashTable<Folder>(base);
        create_interface_and_perform(info_storage, structure);

    }else if(choice == 2){
        auto structure = new Order_Statistic_Tree<Folder>(base);
        create_interface_and_perform(info_storage, structure);
    }else if(choice == 3){
        auto structure = new Splay_Tree<Folder>(base);
        create_interface_and_perform(info_storage, structure);
    }else if(choice == 4){
        auto structure = new Optimal_Binary_Tree<Folder>(base, {}, {});
        create_interface_and_perform(info_storage, structure);
    }
}

int main() {

    std::shared_ptr<Folder> p(std::make_shared<Folder>("Folder 1"));
    while(true){
        cout << "\nВітаю!" << endl;
        cout << "Оберіть лабораторну для тестування: " << endl;
        cout << "(1) HASH TABLE\n";
        cout << "(2) Order-Statistic Tree\n";
        cout << "(3) Splay Tree\n";
        cout << "(4) Optimal Binary Tree\n";
        cout << "(0) Exit\n";
        cout << "Ваш вибір: ";
        char choice;
        cin >> choice;
        if(!isdigit(choice) || choice <= '0' || choice > '9'){
            break;
        }
        int ch = (int) choice - '0';
        get_data_and_perform(ch);
    }
    return 0;
}
