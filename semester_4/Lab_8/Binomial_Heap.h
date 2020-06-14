//
// Created by sadoffnick on 13.06.20.
//
#include <memory>
#include <vector>

using namespace std;

#ifndef SEMESTER_4_BINOMAIL_HEAP_H
#define SEMESTER_4_BINOMAIL_HEAP_H

template <typename T>
struct Binomial_Node {
    shared_ptr<T> key;
    shared_ptr<Binomial_Node<T>> parent;
    shared_ptr<Binomial_Node<T>> child;
    shared_ptr<Binomial_Node<T>> brother;
    int size;
    Binomial_Node()= default;
    explicit Binomial_Node(shared_ptr<T> _key,
                  shared_ptr<Binomial_Node<T>> _parent = nullptr,
                  shared_ptr<Binomial_Node<T>> _child = nullptr,
                  shared_ptr<Binomial_Node<T>> _brother = nullptr,
                  int _size = 0){
        parent = _parent;
        key = _key;
        child = _child;
        brother = _brother;
        size = _size;
    }

};



template <class T>

class Binomial_Heap {
private:
    shared_ptr<Binomial_Node<T>> head;

    void connect(shared_ptr<Binomial_Node<T>> a, shared_ptr<Binomial_Node<T>> b);

    shared_ptr<Binomial_Node<T>> convert_tree_to_heap(shared_ptr<Binomial_Node<T>> cur);

    shared_ptr<Binomial_Node<T>> fix_heap(shared_ptr<Binomial_Node<T>> root);

    bool find_element_in_tree(shared_ptr<Binomial_Node<T>> root, shared_ptr<T> element);

public:
    shared_ptr<Binomial_Node<T>> find_min_node();

    explicit Binomial_Heap(vector<shared_ptr<T>> heap_base = {});

    ~Binomial_Heap() = default;

    bool insert_element(shared_ptr<T> element);

    shared_ptr<Binomial_Node<T>> get_head();

    bool find_element(shared_ptr<T> element);

    void delete_element(shared_ptr<T> element);

    void print(shared_ptr<Binomial_Node<T>> cur = nullptr, int depth = 0);

    shared_ptr<T> find_minimum();

    bool decrease_key(shared_ptr<Binomial_Node<T>> node, T k);

    void extract_minimum();

    void merge_heap(shared_ptr<Binomial_Node<T>> second_heap);

    void perform(std::string command);
};


#include "Binomial_Heap.hpp"


#endif //SEMESTER_4_BINOMAIL_HEAP_H
