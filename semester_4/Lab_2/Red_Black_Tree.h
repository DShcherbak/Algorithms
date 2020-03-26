
#ifndef LAB_2_RED_BLACK_TREE_H
#define LAB_2_RED_BLACK_TREE_H

#include <random>


template <class T>
struct Node {
    T value;
    Node<T>* parent = nullptr;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    bool black = true;

    explicit Node(T _value){
        value = _value;
    }
};

template <class T>
class Red_Black_Tree {
private:
    Node<T>* head;

    void delete_node(Node<T>* cur);

    void transplant_tree(Node<T>* old, Node<T>* to);

    void next_value(Node<T>* cur);
public:
    void insert_element(T new_elem);

    bool find_element(T elem);

    void delete_element(T elem);
};

#include "Red_Black_Tree.hpp"
#endif //LAB_2_RED_BLACK_TREE_H
