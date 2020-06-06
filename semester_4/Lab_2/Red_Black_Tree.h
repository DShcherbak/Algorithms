#ifndef LAB_2_RED_BLACK_TREE_H
#define LAB_2_RED_BLACK_TREE_H


#include "../Tree/Tree.h"


template <class T>
struct RBNode : private Node<T>{
    T value;
    RBNode<T>* parent = nullptr;
    RBNode<T>* left = nullptr;
    RBNode<T>* right = nullptr;
    bool black = true;

    explicit RBNode(T _value) : Node<T>(_value){
        value = _value;
        black = true;
    }

    RBNode(){
        black = true;
    }

};

template <class T>
class Red_Black_Tree : public Binary_Search_Tree<T> {
private:
    RBNode<T>* root;
    RBNode<T>* nil;

    void delete_node(RBNode<T>* cur);

    void transplant_tree(RBNode<T>* old_node, RBNode<T>* new_node);

    RBNode<T>* minimum(RBNode<T>* cur);

    void print_node(RBNode<T>* cur, int depth = 0, bool left = false, vector<bool> draw = {});
    void delete_subtree(RBNode<T> *cur);

    void left_rotate(RBNode<T>* cur);
    void right_rotate(RBNode<T> *cur);

    void insert_fix(RBNode<T> *cur);
    void delete_fix(RBNode<T> *cur);

    template <class N>
    bool find_node(RBNode<T>* cur, const N& value);

public:

    Red_Black_Tree();

    ~Red_Black_Tree();

    void insert_element(const T& new_elem);

    bool find_element(const T& elem);

    void delete_element(const T& elem);


    void print_tree();
};


#include "Red_Black_Tree.hpp"
#endif //LAB_2_RED_BLACK_TREE_H

