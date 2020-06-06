#include "Interface.h"

#include <memory>


// Обрати базу даних для виконання (мала, велика, ніякої)
// ВИконати зчитку з бази
// Надати можливість
// --створити об'єкт (додавши чи не додавши в базу)
// -- знайти об'єкт за ім'ям чи іншим параметром
// -- видалити об'єкт зі структури
// -- виконати кастомну команду
//повернутися в головне меню

template <class Data_Structure, class Elem>
Interface<Data_Structure, Elem>::~Interface(){
    delete info_storage;
    delete data_structure;
}

string convert_KB(int KB){
    if(KB <= 0){
        return "0 KB";
    }
    int GB = 0, MB = 0, rest = 0;
    if(KB < 1024)
        return to_string(KB) + " KB";
    else if (KB > 1024*1024){
        GB = KB / (1024*1024);
        rest = (KB*10 / (1024*1024))%10;
        return to_string(GB) + (rest > 0 ? ","+to_string(rest) : "") + " GB";
    }
    else{
        MB = KB / (1024);
        rest = (KB*10 / (1024))%10;
        return to_string(MB) + (rest > 0 ? ","+to_string(rest) : "") + " MB";
    }
}

string element_full_info(Wrapped_folder* wrapped_folder, bool OK){
    string result;
    string temp = wrapped_folder->element->name;
    result += temp;
    int len = 20-result.length();
    for(int i = 0; i < len; i++) result += " ";
    temp = convert_KB(wrapped_folder->element->size);
    result += temp;
    len = 10-temp.length();
    for(int i = 0; i < len; i++) result += " ";
    result += to_string(wrapped_folder->included) + "         ";
    result += to_string(wrapped_folder->deleted) + "         ";
    result += (OK ? "[OK]" : "[Fail]");
    result += "\n";
    for(const shared_ptr<File>& file : wrapped_folder->element->files){
        result += " |--- " + file->name;
        len = 14-file->name.length();
        for(int i = 0; i < len; i++) result += " ";
        result += convert_KB(file->size);
        result += "\n";
    }
    return result;

}

template <class Data_Structure, class Elem>
void Interface<Data_Structure, Elem>::check_state(){
    if(!info_storage) {
        cout << "Reading error!\n";
        return;
    }
    cout << "Folder name         Size      Included  Deleted   Status\n";
    cout << "----------------------------------------------------------\n";
    for (auto data_element : info_storage->elements){
        bool OK = false;
        shared_ptr<Folder> folder = data_element->element;
        if(data_element->included){
            OK = data_structure->find_element(folder);
        }
        else{
            OK = !data_structure->find_element(folder);
        }
        string full_info = element_full_info(data_element, OK);
        cout << full_info << endl;
    }
    cout << "----------------------------------------------------------" << endl;
    cout << "----------------------------------------------------------\n";
    cout << "----------------------------------------------------------\n";
}

template <class Data_Structure, class Elem>
void Interface<Data_Structure, Elem>::perform() {
    check_state();
    while(true){
        cout << "Оберіть наступну команду: " << endl;
        cout << "(1) Вставка елемента"  << endl;
        cout << "(2) Пошук елемента"  << endl;
        cout << "(3) Вивести структуру в консоль"  << endl;
        cout << "(4) Видалити елемент"  << endl;
        cout << "(0) Exit"  << endl;
        cout << "Ваш вибір: ";
        char choice;
        cin >> choice;
        int chosen_command;
        if(!isdigit(choice)){
            cout << "Некоректні дані: " << choice << endl;
            continue;
        }
        else{
            chosen_command = (int) choice - '0';
            if(chosen_command == 0)
                return;
            perform_command(chosen_command);
        }
    }
}

template <class Data_Structure, class Elem>
void Interface<Data_Structure, Elem>::perform_command(int command_code) {
    string name;
    shared_ptr<Folder> new_folder;
    bool OK;
    switch(command_code){
        case 1:
            cout << "Enter new folder name to insert: ";
            cin >> name;
            new_folder = std::make_shared<Folder>(name);
            OK = data_structure->insert_element(new_folder);

            break;
        case 2:
            cout << "Enter new folder name to find: ";
            cin >> name;
            new_folder = std::make_shared<Folder>(name);
            OK = data_structure->find_element(new_folder);
            std::cout << (OK ? "Found " : "Not found ") << "\"" << name << "\"" << " in data structure!"<< std::endl;
            break;
        case 3:
            data_structure->print();
            break;
        case 4:
            cout << "Enter new folder name to delete: ";
            cin >> name;
            new_folder = std::make_shared<Folder>(name);
            data_structure->delete_element(new_folder);
            break;
        default:
            break;
    }
}


