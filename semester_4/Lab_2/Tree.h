#ifndef LAB_2_TREE_H
#define LAB_2_TREE_H

#include <iostream>
#include <vector>

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
class TreeInterface // interface of a binary_tree
{
public:
    template <typename N>
    static void delete_subtree(N cur);

    virtual ~TreeInterface() = default;

    virtual void insert_element(const T& elem) = 0;

    virtual void delete_element(const T& elem) = 0;

    template <typename N>
    static bool find_node(N cur, const T& value);
    virtual bool find_element(const T& elem) = 0;

    template <typename N>
    static void print_node(N cur, int depth = 0, bool left = false, vector<bool> draw = {});
    virtual void print_tree() = 0;
};


template <class T>
template <typename N>
void TreeInterface<T>::delete_subtree(N cur) {
    if(cur == nullptr)
        return;
    delete_subtree(cur->left);
    delete_subtree(cur->right);
    delete cur;
}

template <class T>
template <typename N>
void TreeInterface<T>::print_node(N cur, int depth, bool left, vector<bool> draw){
    if(cur == nullptr)
        return;
    vector <bool> new_draw = draw;
    new_draw.push_back(false);
    if(depth > 0) new_draw[depth-1] = left;
    print_node(cur->right, depth + 1, false, new_draw);

    for(int i = 0; i < depth-1; i++){
        cout << (draw[i] ? "|" : " ") << "\t";
    }
    cout << (depth > 0 ? "|---" : "") << cur->value << std::endl;

    if(depth > 0) new_draw[depth-1] = !left;
    print_node(cur->left, depth + 1, true, new_draw);

}

template <class T>
template <typename N>
bool TreeInterface<T>::find_node(N cur, const T& value){
    if(!cur)
        return false;
    if(cur->value == value)
        return true;
    else if(cur->value > value)
        return find_node(cur->left, value);
    else
        return find_node(cur->right, value);
}



#endif //LAB_2_TREE_H
