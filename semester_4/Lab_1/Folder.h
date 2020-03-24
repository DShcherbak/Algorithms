#ifndef LAB_1_FOLDER_H
#define LAB_1_FOLDER_H

#include <string>
#include <vector>

using namespace std;


struct File{
    string name;

    explicit File(const string &_name){
        name = _name;
    }
};

struct Folder {
    string name;
    vector <File*> files;

    explicit Folder(const string& _name, const vector<File*>& _files = {}){
        name = _name;
        files = _files;
    }
};


#endif //LAB_1_FOLDER_H
