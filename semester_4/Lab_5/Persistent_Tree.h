//
// Created by sadoffnick on 07.06.20.
//

#ifndef SEMESTER_4_PERSISTENT_TREE_H
#define SEMESTER_4_PERSISTENT_TREE_H


#include "../Tree/Tree.h"
#include "../Lab_2/Red_Black_Tree.h"
template <class T>
class Persistent_Tree : public TreeInterface<T> {
private:
    vector<RBNode<T>*> roots;
    int current = 0;
    RBNode<T>* nil;

    void delete_node(RBNode<T>* cur);

    void transplant_tree(RBNode<T>* old_node, RBNode<T>* new_node);

    RBNode<T>* minimum(RBNode<T>* cur);

    void print_node(RBNode<T>* cur, int depth = 0, bool left = false, vector<bool> draw = {});
    void delete_subtree(RBNode<T> *cur);

    void left_rotate(RBNode<T>* cur);
    void right_rotate(RBNode<T> *cur);

    void insert_fix(RBNode<T> *cur);
    void insert_fix_free(RBNode<T> *cur);
    void free_insert(shared_ptr<T> elem);
    void delete_fix(RBNode<T> *cur);

    bool find_node(RBNode<T>* cur, shared_ptr<T> value);

public:

    Persistent_Tree();
    explicit Persistent_Tree(vector <shared_ptr<T>> included);

    ~Persistent_Tree();

    bool insert_element(shared_ptr<T> new_elem);

    bool find_element(shared_ptr<T> elem);

    void delete_element(shared_ptr<T> elem);


    void print();
};


#include "Persistent_Tree.hpp"




#endif //SEMESTER_4_PERSISTENT_TREE_H
