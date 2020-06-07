#ifndef SEMESTER_4_SPLAY_TREE_H
#define SEMESTER_4_SPLAY_TREE_H

#include "../Tree/Tree.h"
#include <cassert>
#include <memory>
#include <random>

using namespace std;

template <class T>
class Splay_Tree : public TreeInterface<T> {
private:
    Node<T>* root;

    void delete_node(Node<T>* cur);

    void transplant_tree(Node<T>* old_node, Node<T>* new_node);

    Node<T>* minimum(Node<T>* cur);

    Node<T>* left_rotate(Node<T>* cur);
    Node<T>* right_rotate(Node<T> *cur);

    Node<T>* splay(Node<T>* cur, shared_ptr<T> value);

public:
    Splay_Tree() = default;

    explicit Splay_Tree(const vector <shared_ptr<T>>& included);

    ~Splay_Tree();

    bool insert_element(shared_ptr<T> new_elem);

    bool find_element(shared_ptr<T> elem);

    void delete_element(shared_ptr<T> elem);

    void perform(const string& command);

    void print();

};

#include "Splay_Tree.hpp"


#endif //SEMESTER_4_SPLAY_TREE_H
