//
// Created by sadoffnick on 13.06.20.
//

#include <iostream>
#include "Binomial_Heap.h"

template <class T>
Binomial_Heap<T>::Binomial_Heap(vector<shared_ptr<T>> heap_base){
    head = nullptr;
    int n = heap_base.size();
    if(n == 0)
        return;
    auto header = make_shared<Binomial_Node<T>>(heap_base[0]);
    head = header;
    for(int i = 1; i < n; i++){
        auto add_heap = make_shared<Binomial_Node<T>>(heap_base[i]);
        merge_heap(add_heap);
    }
}


template <class T>
bool Binomial_Heap<T>::insert_element(shared_ptr<T> element){
    auto new_heap_head = make_shared<Binomial_Node<T>>(element);
    merge_heap(new_heap_head);
}

template <class T>
shared_ptr<Binomial_Node<T>> Binomial_Heap<T>::find_min_node() {
    auto min_node = head;
    if (min_node == nullptr)
        return min_node;
    auto next = min_node;
    while (next != nullptr) {
        if ((*next->key) < (*min_node->key))
            min_node = next;
        next = next->brother;
    }
    return min_node;
}

template <class T>
void Binomial_Heap<T>::connect(shared_ptr<Binomial_Node<T>> a, shared_ptr<Binomial_Node<T>> b){
    a->parent = b;
    a->brother = b->child;
    b->child = a;
    b->size++;
}

template <class T>
void Binomial_Heap<T>::merge_heap(shared_ptr<Binomial_Node<T>> next) {
    shared_ptr<Binomial_Node<T>> cur = nullptr;
    shared_ptr<Binomial_Node<T>> new_head = nullptr;
    auto head1 = head;
    auto head2 = next;
    while (head1 != nullptr || head2 != nullptr) {
        if (head1 == nullptr ||( (head2 != nullptr)  && (head2->size < head1->size))) {
            if (cur == nullptr) {
                cur = head2;
                new_head = cur;
            }
            else {
                cur->brother = head2;
                cur = cur->brother;
            }
            head2 = head2->brother;
        }
        else {
            if (cur == nullptr) {
                cur = head1;
                new_head = cur;
            }
            else {
                cur->brother = head1;
                cur = cur->brother;
            }
            head1 = head1->brother;
        }
    }
    new_head = fix_heap(new_head);
    head = new_head;
}

template <class T>
shared_ptr<Binomial_Node<T>> Binomial_Heap<T>::fix_heap(shared_ptr<Binomial_Node<T>> root){

    if (root == nullptr)
        return nullptr;
    shared_ptr<Binomial_Node<T>> prev = nullptr;
    shared_ptr<Binomial_Node<T>> cur = root;
    shared_ptr<Binomial_Node<T>> next = cur->brother;
    while (next != nullptr) {
        if (cur->size != next->size || (next->brother != nullptr && next->size == next->brother->size)) {
            prev = cur;
            cur = next;
        } else if ((*cur->key) < (*next->key)) {
            cur->brother = next->brother;
            connect(next, cur);
        } else {
            if (prev == nullptr) {
                root = next;
            } else {
                prev->brother = next;
            }
            connect(cur, next);
            cur = next;
        }
        next = next->brother;
    }
    return root;
}


template <class T>
void Binomial_Heap<T>::print(shared_ptr<Binomial_Node<T>> cur, int depth) {
    if(cur == nullptr)
        cur = head;
    if(depth == 0){
        int cur_size = 1 << cur->size;
        cout << "SIZE: " << cur_size << endl;
    }
    if (cur->child != nullptr) {
        std::cout << convert_to_string(cur->key)  << " V " << convert_to_string(cur->child->key) << "\n";
        print(cur->child, depth + 1);
       // std::cout << convert_to_string(cur->child->key)  << " /\\ " << convert_to_string(cur->key) << "\n";
    }
    if (cur->brother != nullptr) {
        std::cout << convert_to_string(cur->key) << " -> " << convert_to_string(cur->brother->key) << "\n";
        print(cur->brother, depth);
    }
}


template <class T>
shared_ptr<Binomial_Node<T>> Binomial_Heap<T>::convert_tree_to_heap(shared_ptr<Binomial_Node<T>> cur) {
    cur->parent = nullptr;
    shared_ptr<Binomial_Node<T>> prev = nullptr;
    while (cur != nullptr) {
        auto temp = cur->brother;
        cur->brother = prev;
        prev = cur;
        cur = temp;
    }
    return prev;
}

template <class T>
void Binomial_Heap<T>::extract_minimum(){
    auto  min_node = find_min_node();
    if (min_node == nullptr)
        return;
    shared_ptr<Binomial_Node<T>> prev = nullptr;
    auto  cur = head;
    while (cur != min_node) {
        prev = cur;
        cur = cur->brother;
    }
    if (prev == nullptr)
        head = cur->brother;
    else {
        prev->brother = cur->brother;
    }
    if (min_node->child == nullptr)
        return;
    auto head1 = convert_tree_to_heap(min_node->child);
    merge_heap(head1);
    //delete min_node;
}

template <class T>
bool Binomial_Heap<T>::decrease_key(shared_ptr<Binomial_Node<T>> node, T k) {
    if ((*node->key) < k)
        return false;
    node->key = k;
    while (node->parent != nullptr && node->parent->key > k)  {
        T temp = node->key;
        node->key = node->parent->key;
        node->parent->key = temp;
        node = node->parent;
    }
}

template<class T>
shared_ptr<T> Binomial_Heap<T>::find_minimum() {
    auto v = find_min_node();
    return v->key;
}

template<class T>
shared_ptr<Binomial_Node<T>> Binomial_Heap<T>::get_head() {
    return head;
}

template<class T>
bool Binomial_Heap<T>::find_element(shared_ptr<T> element) {
    return find_element_in_tree(head, element);
}

template<class T>
bool Binomial_Heap<T>::find_element_in_tree(shared_ptr<Binomial_Node<T>> root, shared_ptr<T> element) {
    if(root == nullptr)
        return false;
    if((*root->key) == (*element)){
        return true;
    }
    return find_element_in_tree(root->child, element) || find_element_in_tree(root->brother, element);
}

template<class T>
void Binomial_Heap<T>::delete_element(shared_ptr<T> element) {
    std::cout << "Не можна видаляти елементи з біноміальної купи.\n";
    std::cout << "Скористайтеся видаленням мінімального елементу." << endl;
}
/*
template<class T>
void Binomial_Heap<T>::perform(std::string command) {
    if(command == "pop"){
        extract_minimum();
    }
}*/

template<class T>
void Binomial_Heap<T>::perform(std::string command) {
    if(command == "pop"){
        cout << "Введіть 0, щоб видалити найменший елемент, і 1, щоб його вивести\n";
        char ch;
        cin >> ch;
        if(ch == '0'){
            extract_minimum();
        }else if(ch == '1'){
            auto val = find_minimum();
            cout << convert_to_string(val) << endl;
        }
    }
}

