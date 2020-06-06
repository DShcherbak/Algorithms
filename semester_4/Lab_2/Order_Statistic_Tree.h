#ifndef LAB_2_ORDER_STATISTIC_TREE_H
#define LAB_2_ORDER_STATISTIC_TREE_H

#include "Binary_Search_Tree.h"
#include "../Tree/Tree.h"
#include <cassert>


template <class T>
struct OSNode : private Node<T>{
    shared_ptr<T> value;
    OSNode<T>* parent = nullptr;
    OSNode<T>* left = nullptr;
    OSNode<T>* right = nullptr;
    bool black = true;
    int size = 0;

    explicit OSNode(shared_ptr<T> _value) {
        value = _value;
        black = true;
        size = 1;
    }


};

template <class T>
class Order_Statistic_Tree : public TreeInterface<T> {
private:
    OSNode<T>* root;
    OSNode<T>* nil;


    void delete_node(OSNode<T>* cur);

    void transplant_tree(OSNode<T>* old_node, OSNode<T>* new_node);

    OSNode<T>* minimum(OSNode<T>* cur);

    void print_node(OSNode<T>* cur, int depth = 0, bool left = false, vector<bool> draw = {false});
    void delete_subtree(OSNode<T> *cur);

    void left_rotate(OSNode<T>* cur);
    void right_rotate(OSNode<T> *cur);

    void insert_fix(OSNode<T> *cur);
    void delete_fix(OSNode<T> *cur);

    OSNode<T>* get_node_by_number(OSNode<T>* cur, int number);

    int get_rank(OSNode<T>* cur);
    void recount_size(OSNode<T>* cur);

    bool find_node(OSNode<T>* cur, shared_ptr<T> value);
    OSNode<T>* get_node_by_value(OSNode<T>* cur, shared_ptr<T> value);

public:

    Order_Statistic_Tree();

    explicit Order_Statistic_Tree(vector<shared_ptr<T>> included);

    ~Order_Statistic_Tree();

    bool insert_element(shared_ptr<T> new_elem);

    bool find_element(shared_ptr<T> elem);

    void delete_element(shared_ptr<T> elem);

    void print();

    string get_element(int number);

    int get_element_rank(shared_ptr<T> elem);


    int get_size();
};


#include "Order_Statistic_Tree.hpp"


#endif //LAB_2_ORDER_STATISTIC_TREE_H
