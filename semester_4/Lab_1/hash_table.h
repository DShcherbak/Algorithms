#ifndef LAB_1_HASH_TABLE_H
#define LAB_1_HASH_TABLE_H


#include "../Folder/Folder.h"
#include <vector>
#include <memory>
#include <map>


using namespace std;


template <class T>
struct HashNode{
    shared_ptr<T> value;

    explicit HashNode(shared_ptr<T> _val){
        value = _val;
    }

    ~HashNode() = default;
};

template <class T>
class HashTable {
private:

    vector <vector<HashNode<T>*>> table;
    vector <int> a, b, m;
    int A = 42, B = 713, M = 30;

    int first_level_hash(shared_ptr<T> elem);

    int second_level_hash(shared_ptr<T> elem, int first_hash);

public:
    explicit HashTable(vector <shared_ptr<T>> included);

    ~HashTable();

    bool insert_element(shared_ptr<T> new_elem);

    bool find_element(shared_ptr<T> elem);

    void print();

    void delete_element(shared_ptr<T>);

};


#include "hash_table.hpp"
#endif //LAB_1_HASH_TABLE_H
