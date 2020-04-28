#ifndef LAB_1_HASH_TABLE_H
#define LAB_1_HASH_TABLE_H

#include "../Folder.h"
#include <vector>
#include <map>


using namespace std;


template <class T>
        struct Node{
    Node<T>* next;
    Node<T>* prev;
    T value;

    explicit Node(T _val){
        value = _val;
        next = nullptr;
        prev = nullptr;
    }
};

template <class T>
class HashTable {
private:

    vector <vector<Node<T>*>> table;
    vector <int> a, b, m;
    int A = 42, B = 713, M = 30;

    int first_level_hash(T& elem);

    int second_level_hash(T& elem, int first_hash);

public:
   // void insert_element(T new_elem);

    bool find_element(T elem);

    void delete_element(T);

    explicit HashTable(vector <T> included);

};


#include "hash_table.hpp"
#endif //LAB_1_HASH_TABLE_H
