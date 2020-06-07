//
// Created by sadoffnick on 07.06.20.
//

#ifndef SEMESTER_4_PERSISTENT_TREE_H
#define SEMESTER_4_PERSISTENT_TREE_H


#include "../Tree/Tree.h"
#include "../Lab_2/Red_Black_Tree.h"

template <class T>
struct PNode : private Node<T>{
    shared_ptr<T> value;
    shared_ptr<PNode<T>> parent = nullptr;
    shared_ptr<PNode<T>> left = nullptr;
    shared_ptr<PNode<T>> right = nullptr;
    bool black = true;

    explicit PNode(shared_ptr<T> _value) : Node<T>(_value){
        value = _value;
        black = true;
    }

    PNode(){

    }


};

template <class T>
class Persistent_Tree : public TreeInterface<T> {
private:
    vector<shared_ptr<PNode<T>>> roots;
    int current = 0;
    int last = 0;
    shared_ptr<PNode<T>> nil;

    void delete_node(shared_ptr<PNode<T>> cur);

    void transplant_tree(shared_ptr<PNode<T>> old_node, shared_ptr<PNode<T>> new_node);

    shared_ptr<PNode<T>> minimum(shared_ptr<PNode<T>> cur);

    void print_node(shared_ptr<PNode<T>> cur, int depth = 0, bool left = false, vector<bool> draw = {});
    void delete_subtree(shared_ptr<PNode<T>> cur);

    void left_rotate(shared_ptr<PNode<T>> cur);
    void right_rotate(shared_ptr<PNode<T>> cur);

    void insert_fix(shared_ptr<PNode<T>> cur);
    void insert_fix_free(shared_ptr<PNode<T>> cur);
    void free_insert(shared_ptr<T> elem);
    void delete_fix(shared_ptr<PNode<T>> cur);

    bool find_node(shared_ptr<PNode<T>> cur, shared_ptr<T> value);

    void fully_reconnect(shared_ptr<PNode<T>> new_node, shared_ptr<PNode<T>> father = nullptr, bool left = true);

public:

    Persistent_Tree();
    explicit Persistent_Tree(vector <shared_ptr<T>> included);

    ~Persistent_Tree();

    bool insert_element(shared_ptr<T> new_elem);

    bool find_element(shared_ptr<T> elem);

    void delete_element(shared_ptr<T> elem);

    void history();

    void perform(const string& command);

    void print();
};


#include "Persistent_Tree.hpp"




#endif //SEMESTER_4_PERSISTENT_TREE_H
