//
// Created by sadoffnick on 07.06.20.
//

#ifndef SEMESTER_4_B_TREE_H
#define SEMESTER_4_B_TREE_H

#include "../Tree/Tree.h"
#include "../Folder/Folder.h"

#define node shared_ptr<B_Node<T>>

template <class T>
struct B_Node : private Node<T>{

    bool is_leaf;
    int number;
    vector<string> keys;
    node parent;
    node left;
    node right;
    vector <node> children;
    vector<shared_ptr<T>> info;


    B_Node(){

    }


};

template <class T>
class B_Tree : public TreeInterface<T> {
private:
    shared_ptr<B_Node<T>> root;

    void print_node(B_Node<T>* cur, int depth = 0, bool left = false, vector<bool> draw = {});

    node find_leaf(node cur, shared_ptr<T> elem);
public:

    B_Tree();

    ~B_Tree();

    bool insert_element(shared_ptr<T> new_elem);

    bool find_element(shared_ptr<T> elem);

    void delete_element(shared_ptr<T> elem);

    void print();

    void perform(const string &command);
};


#include "B_Tree.hpp"
#endif //SEMESTER_4_B_TREE_H
