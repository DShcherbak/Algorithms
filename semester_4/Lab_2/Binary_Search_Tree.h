
#ifndef LAB_2_BINARY_SEARCH_TREE_H
#define LAB_2_BINARY_SEARCH_TREE_H

#include <random>

using namespace std;

template <class T>
struct Node {
    T value;
    Node<T>* parent = nullptr;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;

    explicit Node(T _value){
        value = _value;
    }
};

template <class T>
class Binary_Search_Tree {
private:
    Node<T>* head;

    void delete_node(Node<T>* cur);

    void transplant_tree(Node<T>* old_node, Node<T>* new_node);

    void print_node(Node<T> *cur, int depth = 0, bool left = false, const vector<bool> &draw = {});

    Node<T>* minimum(Node<T>* cur);
public:
    void insert_element(T new_elem);

    bool find_element(T elem);

    void delete_element(T elem);

    void print_tree();
};

#include "Binary_Search_Tree.hpp"
#endif //LAB_2_BINARY_SEARCH_TREE_H
