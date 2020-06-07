//
// Created by sadoffnick on 05.06.20.
//

#ifndef SEMESTER_4_OPTIMAL_BINARY_TREE_H
#define SEMESTER_4_OPTIMAL_BINARY_TREE_H

#include "../Tree/Tree.h"
#include <algorithm>


template  <class T>
class Optimal_Binary_Tree : TreeInterface<T> {
private:
    Node<T>* root;
    vector <vector<double>> DP;
    vector <double> _partial_sum;
    vector <double> _partial_error_sum;
    vector <double> _values_probabilities;
    vector <double> _miss_probabilities;
    vector <vector<int>> _root;

    Node<T>* build_optimal_tree(const vector<shared_ptr<T>> &included, int left, int right);

    Node<T>* minimum(Node<T>* cur);

    double go(int i, int j);

    double sum(int i, int j);

    void print_node(Node<T>* cur, int depth = 0, bool left = false, vector<bool> draw = {});

public:
    explicit Optimal_Binary_Tree(const vector <shared_ptr<T>>& included,
            std::vector <double> value_probabilities = {},
            std::vector <double> miss_value_probabilities = {});

    ~Optimal_Binary_Tree();

    bool insert_element(shared_ptr<T> elem);
    void delete_element(shared_ptr<T> elem);

    bool find_element(shared_ptr<T> elem);

    void perform(const string& command);

    void print();


};

#include "Optimal_Binary_Tree.hpp"


#endif //SEMESTER_4_OPTIMAL_BINARY_TREE_H
