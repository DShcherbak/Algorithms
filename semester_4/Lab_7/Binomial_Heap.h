//
// Created by sadoffnick on 13.06.20.
//
#include <memory>
#include <vector>

using namespace std;

#ifndef SEMESTER_4_BINOMAIL_HEAP_H
#define SEMESTER_4_BINOMAIL_HEAP_H

template <class T>
struct Binomial_Node{
    shared_ptr<T> value;
    shared_ptr<Binomial_Node> parent;
    shared_ptr<Binomial_Node> brother;
    shared_ptr<Binomial_Node> son;
    //vector<shared_ptr<Binomial_Node>> children;  do I need this?

    explicit Binomial_Node(shared_ptr<T> _value){
        value = _value;
        parent = nullptr;
        brother = nullptr;
        son = nullptr;
    }
};



template <class T>
class Binomial_Heap {
private:
    shared_ptr<Binomial_Node<T>> head;
    int mask = 0;

public:
    Binomial_Heap(vector<shared_ptr<T>> heap_base = {});

    ~Binomial_Heap() = default;

    bool insert_element(shared_ptr<T> element);

    bool find_element(shared_ptr<T> element);

    void delete_element(shared_ptr<T> element);

    void print_head();

    shared_ptr<T> find_minimum();

    void merge_heap(shared_ptr<Binomial_Node<T>> second_heap);
};

#include "Binomial_Heap.hpp"


#endif //SEMESTER_4_BINOMAIL_HEAP_H
