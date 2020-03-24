const int mod = 1e9+7;

int hash_element(int elem){
    int result = elem;
    while(result < 0) result += mod;
    return result % mod;
}

int hash_element(Folder* elem){
    long long result = 0, temp = 0;
    for(int i = 0, n = elem->name.size(); i < n; i++){
        temp = (int) elem->name[i];
        result = (result * temp) % mod;
    }
    int int_result = (int) (result % mod);
    return int_result;

}

template <class T>
void HashTable<T>::insert_element(T new_elem) {
    if(search_element(new_elem))
        return;
    auto new_node = new Node<T>(new_elem);
    int hash_code = hash_element(new_elem);
    if(table.find(hash_code) == table.end()){
        table[hash_code] = new_node;
    }else{
        auto head = table[hash_code];
        head->prev = new_node;
        new_node->next = head;
        table[hash_code] = new_node;
    }
}

template <class T>
bool HashTable<T>::search_element(T elem) {
    int hash_code = hash_element(elem);
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

template <class T>
void HashTable<T>::delete_element(T elem) {
    if(!search_element(elem))
        return;
    int hash_code = hash_element(elem);
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