
#ifndef LAB_2_BINARY_SEARCH_TREE_H
#define LAB_2_BINARY_SEARCH_TREE_H

#include "../Tree/Tree.h"
#include <random>

using namespace std;


template <class T>
class Binary_Search_Tree : private TreeInterface<T>{
private:
    Node<T>* root;

    void delete_node(Node<T>* cur);

    void transplant_tree(Node<T>* old_node, Node<T>* new_node);

    Node<T>* minimum(Node<T>* cur);

public:
    ~Binary_Search_Tree();

    void insert_element(const T* new_elem);

    bool find_element(const T* elem);

    void delete_element(const T* elem);

    void print_tree();
};

#include "Binary_Search_Tree.hpp"
#endif //LAB_2_BINARY_SEARCH_TREE_H
