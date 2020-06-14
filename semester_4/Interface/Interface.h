#ifndef SEMESTER_4_INTERFACE_H
#define SEMESTER_4_INTERFACE_H

#include "../sqlite3pp-master/headeronly_src/sqlite3pp.h"
#include "../Folder/Folder.h"
#include <set>

struct Wrapped_folder{
    shared_ptr<Folder> element;
    bool included = false;
    bool deleted = false;

    ~Wrapped_folder() = default;
};

struct Information_storage{
    vector <Wrapped_folder*> elements = {};
    set<string> included = {};
    set<string> excluded = {};
    set<string> deleted = {};

    ~Information_storage(){
        for(auto wf : elements){
            delete wf;
        }
    }
};

template <class Data_Structure, class Elem>
class Interface {
private:
    Data_Structure* data_structure;
    Information_storage* info_storage;
    int structure_type = 0;
    vector<pair <string, bool>> special_commands = {
            {"Для цієї структури даних не передбачено жодних спеціальних команд.\n", false},
            {"Для цієї структури даних не передбачено жодних спеціальних команд.\n", false},
            {"choose", true},
            {"Для цієї структури даних не передбачено жодних спеціальних команд.\n", false},
            {"Для цієї структури даних не передбачено жодних спеціальних команд.\n", false},
            {"history", true},
            {"Для цієї структури даних не передбачено жодних спеціальних команд.\n", false},
            {"pop", true}
    };



public:
    Interface(Information_storage* _info_storage, Data_Structure* _Structure, int _type = 0){
        data_structure = _Structure;
        info_storage = _info_storage;
        structure_type = _type;
    }


    ~Interface();
    void perform();

    void perform_command(int command_code);

    void check_state();

    pair<string, bool> special_command();
};

#include "Interface.hpp"


#endif //SEMESTER_4_INTERFACE_H
