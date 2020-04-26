
#include "hash_table.h"

const int mod = 1e9+7;

int convert_to_int(int elem){
    int result = elem;
    while(result < 0) result += mod;
    return result % mod;
}

int convert_to_int(Folder* elem){
    long long result = 0, temp = 0;
    for(int i = 0, n = elem->name.size(); i < n; i++){
        temp = (int) elem->name[i];
        result = (result * temp) % mod;
    }
    int int_result = (int) (result % mod);
    return int_result;
}

template<class T>
int HashTable<T>::first_level_hash(T elem) {
    int int_elem = convert_to_int(elem);
    int hash = ((A*int_elem + B) % mod ) % M;
    return hash;
}

template<class T>
int HashTable<T>::second_level_hash(int elem, int first_hash) {
    int hash = ((a[first_hash]*elem + b[first_hash]) % mod ) % m[first_hash];l
    return hash;
}


template <class T>
void HashTable<T>::insert_element(T new_elem) {
    if(find_element(new_elem))
        return;
    auto new_node = new Node<T>(new_elem);
    int hash_code = convert_to_int(new_elem);
    if(table.find(hash_code) == table.end()){
        table[hash_code] = new_node;
    }else{
        auto head = table[hash_code];
        head->prev = new_node;
        new_node->next = head;
        table[hash_code] = new_node;
    }
}
//FIXME

template <class T>
bool HashTable<T>::find_element(T elem) {
    int hash_code = convert_to_int(elem);
    if(table.find(hash_code) == table.end()){
        return false;
    }else{
        auto head = table[hash_code];
        while(head){
            if(head->value == elem)
                return true;
            head = head->next;
        }
    }
}
//FIXME


template <class T>
void HashTable<T>::delete_element(T elem) {
    if(!find_element(elem))
        return;
    int hash_code = convert_to_int(elem);
    auto head = table[hash_code];
    if(head->value == elem){
        table[hash_code] = head->next;
        delete head;
        return;
    }
    while(head){
        if(head->value == elem) {
            if(head->next)
                head->next->prev = head->prev;
            if(head->prev)
                head->prev->next = head->next;
            delete head;
            return;
        }
        head = head->next;
    }
}




//FIXME