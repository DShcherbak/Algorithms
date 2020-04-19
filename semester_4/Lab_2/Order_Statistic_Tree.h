#ifndef LAB_2_ORDER_STATISTIC_TREE_H
#define LAB_2_ORDER_STATISTIC_TREE_H

#include "Binary_Search_Tree.h"
#include "Tree.h"


template <class T>
struct OSNode : private Node<T>{
    T value;
    OSNode<T>* parent = nullptr;
    OSNode<T>* left = nullptr;
    OSNode<T>* right = nullptr;
    bool black = true;
    int size = 0;

    explicit OSNode(T _value) : Node<T>(_value){
        value = _value;
        black = true;
        size = 1;
    }

    OSNode(){
        black = true;
        size = 1;
    }

};

template <class T>
class Order_Statistic_Tree : public Binary_Search_Tree<T> {
private:
    OSNode<T>* root;
    OSNode<T>* nil;

    void delete_node(OSNode<T>* cur);

    void transplant_tree(OSNode<T>* old_node, OSNode<T>* new_node);

    OSNode<T>* minimum(OSNode<T>* cur);

    void print_node(OSNode<T>* cur, int depth = 0, bool left = false, vector<bool> draw = {});
    void delete_subtree(OSNode<T> *cur);

    void left_rotate(OSNode<T>* cur);
    void right_rotate(OSNode<T> *cur);

    void insert_fix(OSNode<T> *cur);
    void delete_fix(OSNode<T> *cur);

    OSNode<T>* get_node(OSNode<T>* cur, int number);
    int get_rank(OSNode<T>* cur);
    void recount_size(OSNode<T>* cur);

    bool find_node(OSNode<T>* cur, const T& value);

public:

    Order_Statistic_Tree();

    ~Order_Statistic_Tree();

    T get_element(int number);

    void insert_element(const T& new_elem);

    bool find_element(const T& elem);

    void delete_element(const T& elem);


    void print_tree();
};


#include "Order_Statistic_Tree.hpp"


#endif //LAB_2_ORDER_STATISTIC_TREE_H
