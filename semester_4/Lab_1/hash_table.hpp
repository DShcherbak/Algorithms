
#include <random>
#include "hash_table.h"

const int mod = 1e9+7;

int convert_to_int(int elem){
    int result = elem;
    while(result < 0) result += mod;
    return result % mod;
}

int convert_to_int(Folder* elem){
    long long result = 1, temp = 0;
    for(char letter : elem->name){
        temp = (int) letter;
        result = (result * temp) % mod;
    }
    int int_result = (int) (result % mod);
    return int_result;
}

int random_int(int min, int max)
{
    static std::random_device rd;
    static std::seed_seq seed { rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_real_distribution<double> dist(min, max);
    return int(dist(gen));
}

template<class T>
int HashTable<T>::first_level_hash(T& elem) {
    int int_elem = convert_to_int(elem);
    int hash = ((A*int_elem + B) % mod ) % M;
    return hash;
}

template<class T>
int HashTable<T>::second_level_hash(T& elem, int first_hash) {
    int int_elem = convert_to_int(elem);
    int hash = ((a[first_hash]*int_elem + b[first_hash]) % mod ) % m[first_hash];
    return hash;
}

/*
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
*/

template <class T>
bool HashTable<T>::find_element(T elem) {
    int cur_hash = first_level_hash(elem);
    int cur_id = second_level_hash(elem, cur_hash);
    if(table[cur_hash][cur_id] == nullptr){
        return false;
    } else
        return elem == table[cur_hash][cur_id]->value;
}


template <class T>
void HashTable<T>::delete_element(T elem) {
    if(!find_element(elem))
        return;
    int cur_hash = first_level_hash(elem);
    int cur_id = second_level_hash(elem, cur_hash);
    delete table[cur_hash][cur_id];
}


template <class T>
HashTable<T>::HashTable(vector<T> included){
    vector <pair <T, int>> hashes;
    table.assign(M, {});
    a.assign(M,0);
    b.assign(M,0);
    m.assign(M,0);
    vector <int> count(M, 0);
    for(T elem : included){
        int cur_hash = first_level_hash(elem);
        count[cur_hash]++;
        table[cur_hash].push_back(new Node<T>(elem));
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
                a[i] = random_int(0, mod-1);
                b[i] = random_int(0, mod-2);
                collisions = false;
                for(Node<T>* node : table[i]){
                    int id = second_level_hash(node->value, i);
                    if(is_hashed[id]){
                        collisions = true;
                        break;
                    }
                    is_hashed[id] = true;
                }
            }
            for(Node<T>* node : table[i])
                delete node;
        }
    }
    for(T& elem : included){
        int cur_hash = first_level_hash(elem);
        int cur_id = second_level_hash(elem, cur_hash);
        auto new_node = new Node<T>(elem);
        table[cur_hash][cur_id] = new_node;
    }
}