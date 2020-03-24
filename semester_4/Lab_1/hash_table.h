#ifndef LAB_1_HASH_TABLE_H
#define LAB_1_HASH_TABLE_H
#include <map>

using namespace std;

const int mod = 1e9+7;

template <class T>
        struct Node{
    Node<T> next;
    Node<T> prev;
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
    map <int, Node<T>*> table;
public:
    void insert_element(T new_elem);

    bool search_element(T elem);

    void delete_element(T);

};

template <class T>
int hash_element(T elem);


#endif //LAB_1_HASH_TABLE_H