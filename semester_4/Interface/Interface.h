#ifndef SEMESTER_4_INTERFACE_H
#define SEMESTER_4_INTERFACE_H

#include "../sqlite3pp-master/headeronly_src/sqlite3pp.h"
#include "../Folder/Folder.h"
#include <set>

struct Wrapped_folder{
    Folder* element;
    bool included = 0;
    bool deleted = 0;

    ~Wrapped_folder(){
        delete element;
    }
};

struct Information_storage{
    vector <Wrapped_folder*> elements = {};
    set<string> included = {};
    set<string> excluded = {};
    set<string> deleted = {};

    ~Information_storage(){
/*        for(auto wr : elements){
            if(!wr->included || wr->deleted) delete wr;
        }(*/
    }
};

template <class Data_Structure, class Elem>
class Interface {
private:
    Data_Structure* data_structure;
    Information_storage* info_storage;



public:
    Interface(Information_storage* _info_storage, Data_Structure* _Structure){
        data_structure = _Structure;
        info_storage = _info_storage;
    }
    ~Interface();
    void perform();

    void perform_command(int command_code);

    void check_state();
};

#include "Interface.hpp"


#endif //SEMESTER_4_INTERFACE_H
