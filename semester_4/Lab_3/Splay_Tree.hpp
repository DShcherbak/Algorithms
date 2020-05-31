#include "Splay_Tree.h"

template <class T>
Splay_Tree<T>::Splay_Tree(const vector <shared_ptr<T>>& included){
    for(auto elem : included){
        insert_element(elem);
    }
}

template <class T>
Splay_Tree<T>::~Splay_Tree(){
    TreeInterface<T>::delete_subtree(root);
}

template <class T>
bool Splay_Tree<T>::insert_element(const shared_ptr<T> new_elem){
    auto new_node = new Node<T>(new_elem);
    if(!root) {
        root = new_node;
        return root;
    }
    root = splay(root, new_elem);

    if((*root->value) == (*new_elem))
        return true;
    else if((*root->value) < (*new_elem)){
        new_node->left = root;
        new_node->right = root->right;
        root->right = nullptr;
        root = new_node;
        return true;
    }else{
        new_node->right = root;
        new_node->left = root->left;
        root->left = nullptr;
        root = new_node;
        return true;
    }
}

template <class T>
void Splay_Tree<T>::print(){
    if(!root)
        std::cout << "Tree is empty!\n";
    else
        TreeInterface<T>::print_node(root);
}


template <class T>
bool Splay_Tree<T>::find_element(const shared_ptr<T> elem){
    return splay(root, elem);
}


template <class T>
void Splay_Tree<T>::delete_node(Node<T>* cur){
    Node<T>* new_cur = nullptr;
    if(cur->left == nullptr)
        new_cur = cur->right;
    else if(cur->right == nullptr)
        new_cur = cur->left;
    else{
        new_cur = minimum(cur->right);
        if(new_cur->parent != cur){
            transplant_tree(new_cur, new_cur->right);
            new_cur->right = cur->right;
            new_cur->right->parent = new_cur;
        }
        new_cur->left = cur->left;
        new_cur->left->parent = new_cur;
    }

    if(new_cur)
        new_cur->parent = cur->parent;
    if(!cur->parent)
        root = new_cur;
    else if(cur->parent->left == cur)
        cur->parent->left = new_cur;
    else
        cur->parent->right = new_cur;
    delete cur;
}

template <class T>
void Splay_Tree<T>::transplant_tree(Node<T>* old_node, Node<T>* new_node){
    if(!old_node->parent)
        root = new_node;
    else if(old_node->parent->left == old_node)
        old_node->parent->left = new_node;
    else
        old_node->parent->right = new_node;
    if(new_node){
        new_node->parent = old_node->parent;
    }

}

template <class T>
Node<T>* Splay_Tree<T>::minimum(Node<T>* cur){
    while(cur->left)
        cur = cur->left;
    return cur;
}


template <class T>
void Splay_Tree<T>::delete_element(const shared_ptr<T> elem){
    Node<T>* cur = root;
    while(cur){
        if((*cur->value) == (*elem)){
            delete_node(cur);
            return;
        }else if((*cur->value) < (*elem)){
            if(!cur->right)
                return;
            else
                cur = cur->right;
        }else{
            if(!cur->left)
                return;
            else
                cur = cur->left;
        }
    }
}



template<class T>
Node<T> *Splay_Tree<T>::left_rotate(Node<T> *cur) {
    auto next = cur->right;
    cur->right = next->left;
    next->left = cur;
    return next;
}

template<class T>
Node<T> *Splay_Tree<T>::right_rotate(Node<T> *cur) {
    auto next = cur->left;
    cur->left = next->right;
    next->right = cur;
    return next;
}

template<class T>
Node<T> *Splay_Tree<T>::splay(Node<T> *cur, shared_ptr<T> value) {
    if(!cur || (*cur->value) == (*value))
        return cur;
    else if((*cur->value) < (*value)){
        if(!cur->right)
            return cur;
        if((*cur->right->value) < (*value)){
            cur->right->right = splay(cur->right->right, value);
            cur = left_rotate(cur);
        }
        else if((*cur->right->value) > (*value)){
            cur->right->left = splay(cur->right->left, value);
            if(cur->right->left)
                cur->right = right_rotate(cur->right);
        }
        if(cur->right)
            cur = left_rotate(cur);
        return cur;
    }else{
        if(!cur->left)
            return cur;
        if((*cur->left->value) > (*value)){
            cur->left->left = splay(cur->left->left, value);
            cur = right_rotate(cur);
        }
        else if((*cur->left->value) < (*value)){
            cur->left->right = splay(cur->left->right, value);
            if(cur->left->right)
                cur->left = left_rotate(cur->left);
        }
        if(cur->left != nullptr)
            cur = right_rotate(cur);
        return cur;
    }
}


