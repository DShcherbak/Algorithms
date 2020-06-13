
#include <random>
#include <iostream>
#include "hash_table.h"

const int mod = 1e9+7;

int convert_to_int(int* elem, int modulo){
    int result = *elem;
    while(result < 0) result += modulo;
    return result % modulo;
}

string convert_to_string(int* elem){
    return to_string(*elem);
}

int random_int(int min, int max)
{
    static random_device rd;
    static seed_seq seed { rd(), static_cast<unsigned int>(time(nullptr))};
    static mt19937_64 gen(seed);
    uniform_real_distribution<double> dist(min, max);
    return int(dist(gen));
}

template<class T>
int HashTable<T>::first_level_hash(shared_ptr<T> elem) {
    int int_elem = convert_to_int(elem, mod);
    int hash = ((A*int_elem + B) % mod ) % M;
    while(hash < 0) hash += M;
    return hash % M;
}

template<class T>
int HashTable<T>::second_level_hash(shared_ptr<T> elem, int first_hash) {
    int int_elem = convert_to_int(elem, mod);
    int hash = ((a[first_hash]*int_elem + b[first_hash]) % mod ) % m[first_hash];
    while(hash < 0) hash += m[first_hash];
    return hash % m[first_hash];
}

/*
template <class T>
void HashTable<T>::insert_element(T new_elem) {
    if(find_element(new_elem))
        return;
    auto new_HashNode = new HashNode<T>(new_elem);
    int hash_code = convert_to_int(new_elem);
    if(table.find(hash_code) == table.end()){
        table[hash_code] = new_HashNode;
    }else{
        auto head = table[hash_code];
        head->prev = new_HashNode;
        new_HashNode->next = head;
        table[hash_code] = new_HashNode;
    }
}
*/


template <class T>
bool HashTable<T>::find_element(shared_ptr<T> elem) {
    int cur_hash = first_level_hash(elem);
    if(table[cur_hash].size() == 0)
        return false;
    int cur_id = second_level_hash(elem, cur_hash);
    if(table[cur_hash][cur_id] == nullptr){
        return false;
    } else{
        T folder_a = *elem;
        T folder_b = *table[cur_hash][cur_id]->value;
        return folder_a == folder_b;
    }
        //return (*elem) == (*table[cur_hash][cur_id]->value);//(*elem) == (*table[cur_hash][cur_id]->value);
}

template <class T>
bool HashTable<T>::insert_element(shared_ptr<T> new_elem) {
    std::cout << "Не можна вставляти елементи при універсальному хешуванні, таблиця має бути статичною." << endl;
    return false;
}


template <class T>
void HashTable<T>::delete_element(shared_ptr<T> elem) {
    if(!find_element(elem))
        return;
    int cur_hash = first_level_hash(elem);
    int cur_id = second_level_hash(elem, cur_hash);
    delete table[cur_hash][cur_id];
    table[cur_hash][cur_id] = nullptr;

}


template <class T>
HashTable<T>::HashTable(vector<shared_ptr<T>> included){
    vector <pair <HashNode<T>*, int>> hashes;
    M = included.size();
    table.assign(M, {});
    vector <vector<shared_ptr<T>>> pre_table(M);
    a.assign(M,0);
    b.assign(M,0);
    m.assign(M,0);
    vector <int> count(M, 0);
    for(auto elem : included){
        int cur_hash = first_level_hash(elem);
        count[cur_hash]++;
        pre_table[cur_hash].push_back(elem);
    }
    for(int i = 0; i < M; i++){
        if(count[i] == 0){
            a[i] = 0;
            b[i] = 0;
            m[i] = 0;
        }
        else{
            m[i] = count[i] * count[i];

                bool collisions = true;
            while(collisions){
                vector <bool> is_hashed(m[i],0);
                a[i] = random_int(1, mod-1);
                b[i] = random_int(0, mod-2);
                collisions = false;
                for(auto elem : pre_table[i]){
                    int id = second_level_hash(elem, i);
                    if(is_hashed[id]){
                        collisions = true;
                        break;
                    }
                    is_hashed[id] = true;
                }


            }
            for(auto HashNode : table[i]){
                delete HashNode;

            }
            table[i].resize(m[i]);

        }
    }
    for(auto elem : included){
        int cur_hash = first_level_hash(elem);
        int cur_id = second_level_hash(elem, cur_hash);
        auto new_HashNode = new HashNode<T>(elem);
        table[cur_hash][cur_id] = new_HashNode;
    }

}

template <class T>
void HashTable<T>::print(){
    for(int i = 0; i < M; i++){
        cout << "[" << i  << "] ";
        cout << "(" << table[i].size() << ") ";
        for(int j = 0, n = table[i].size(); j < n; j++){
            cout << (table[i][j] ? convert_to_string(table[i][j]->value) : ".") << "|";
        }
        if(table[i].size() == 0)
            cout << "---------------------------------------\n";
        else
            cout << endl;
    }
}

template <class T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < M; i++) {
        for (auto HashNode : table[i])
            if(HashNode)
                delete HashNode;
    }
}

template <class T>
void HashTable<T>::perform(const string &command) {

}