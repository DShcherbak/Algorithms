
#include "Red_Black_Tree.h"

using namespace std;


template <class T>
Red_Black_Tree<T>::Red_Black_Tree(){
    nil = new RBNode<T>();
    root = nil;
}


template <class T>
Red_Black_Tree<T>::~Red_Black_Tree(){
    if(root == nil)
        delete root;
    else{
        Red_Black_Tree<T>::delete_subtree(root);
        delete nil;
    }
}

template <class T>
void Red_Black_Tree<T>::delete_subtree(RBNode<T>* cur) {
    if(cur == nil)
        return;
    delete_subtree(cur->left);
    delete_subtree(cur->right);
    delete cur;
}

template <class T>
void Red_Black_Tree<T>::insert_element(const T& new_elem){
    RBNode<T>* cur = root;
    auto prev = cur;
    auto new_node = new RBNode<T>(new_elem);
    new_node->left = nil;
    new_node->right = nil;
    while(cur != nil){
        prev = cur;
        if(cur->value == new_elem){
            if(cur->left == nil)
                cur = cur->left;
            else if(cur->right == nil)
                cur = cur->right;
            else{
                int ran = randomInt(0,1);
                if(ran)
                    cur = cur->left;
                else
                    cur = cur->right;
            }
        }
        else if(cur->value < new_elem)
            cur = cur->right;
        else
            cur = cur->left;

    }
    new_node->parent = prev;
    if(cur == root){
        root = new_node;
        root->parent = nil;
    }else if(new_node->value < prev->value)
        prev->left = new_node;
    else
        prev->right = new_node;
    new_node->black = false;
    fix_tree(new_node);
} //for now BST

template <class T>
void Red_Black_Tree<T>::fix_tree(RBNode<T>* cur){
    while(!cur->parent->black){
        if(cur->parent == cur->parent->parent->left){
            auto uncle = cur->parent->parent->right;
            if(!uncle->black){
                cur->parent->black = true;
                uncle->black = true;
                uncle->parent->black = false;
                cur = uncle->parent;
            }else {
                if(cur->parent->right == cur){
                    cur = cur->parent;
                    left_rotate(cur);
                } // 2 -> 3
                cur->parent->black = true;
                cur->parent->parent->black = false;
                right_rotate(cur->parent->parent);
            }
        }else{
            auto uncle = cur->parent->parent->left;
            if(!uncle->black){
                cur->parent->black = true;
                uncle->black = true;
                uncle->parent->black = false;
                cur = uncle->parent;
            }else {
                if(cur->parent->left == cur){
                    cur = cur->parent;
                    right_rotate(cur);
                } // 2 -> 3
                cur->parent->black = true;
                cur->parent->parent->black = false;
                left_rotate(cur->parent->parent);
            }
        }
    }
    root->black = true;
}

template <class T>
void Red_Black_Tree<T>::print_tree(){
    if(root == nil)
        std::cout << "Tree is empty!\n";
    else
        Red_Black_Tree<T>::print_node(root);
    cout << "-------------------------------\n";
}

template <class T>
void Red_Black_Tree<T>::print_node(RBNode<T>* cur, int depth, bool left, vector<bool> draw) {
    if(cur == nil)
            return;
    vector <bool> new_draw = draw;
    new_draw.push_back(false);
    if(depth > 0) new_draw[depth-1] = left;
    print_node(cur->right, depth + 1, false, new_draw);

    for(int i = 0; i < depth-1; i++){
        cout << (draw[i] ? "|" : " ") << "\t";
    }
    if(depth > 0){
        if(cur->black)
            cout << "|B--";
        else
            cout << "|R--";
    }
    cout << cur->value << std::endl;

    if(depth > 0) new_draw[depth-1] = !left;
    print_node(cur->left, depth + 1, true, new_draw);


}

template <class T>
bool Red_Black_Tree<T>::find_element(const T& elem){
    return TreeInterface<T>::find_node(root, elem);
}


template <class T>
void Red_Black_Tree<T>::delete_node(RBNode<T>* cur){
    RBNode<T>* new_cur = nullptr;
    if(cur->left == nil)
        new_cur = cur->right;
    else if(cur->right == nil)
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

    if(new_cur != nil)
        new_cur->parent = cur->parent;
    if(cur->parent == nil)
        root = new_cur;
    else if(cur->parent->left == cur)
        cur->parent->left = new_cur;
    else
        cur->parent->right = new_cur;
    delete cur;
}

template <class T>
void Red_Black_Tree<T>::transplant_tree(RBNode<T>* old_node, RBNode<T>* new_node){
    if(old_node->parent == nil)
        root = new_node;
    else if(old_node->parent->left == old_node)
        old_node->parent->left = new_node;
    else
        old_node->parent->right = new_node;
    if(new_node != nil){
        new_node->parent = old_node->parent;
    }

}

template <class T>
RBNode<T>* Red_Black_Tree<T>::minimum(RBNode<T>* cur){
    while(cur->left != nil)
        cur = cur->left;
    return cur;
}

template <class T>
void Red_Black_Tree<T>::delete_element(const T& elem){
    RBNode<T>* cur = root;
    while(cur != nil){
        if(cur->value == elem){
            delete_node(cur);
            return;
        }else if(cur->value < elem){
            if(!cur->right)
                return;
            else
                cur = cur->right;
        }else{
            if(cur->left == nil)
                return;
            else
                cur = cur->left;
        }
    }
}

template<class T>
void Red_Black_Tree<T>::left_rotate(RBNode<T> *cur) {
    if(cur->right == nil)
        return;
    auto next = cur->right;
    if(cur->parent == nil)
        root = next;
    else if(cur->parent->left == cur)
        cur->parent->left = next;
    else
        cur->parent->right = next;
    next->parent = cur->parent;
    cur->right = next->left;
    if(next->left != nil)
        next->left->parent = cur;

    next->left = cur;
    cur->parent = next;
}

template<class T>
void Red_Black_Tree<T>::right_rotate(RBNode<T> *cur) {
    if(cur->left == nil)
        return;
    auto next = cur->left;
    if(cur->parent == nil)
        root = next;
    else if(cur->parent->right == cur)
        cur->parent->right = next;
    else
        cur->parent->left = next;
    next->parent = cur->parent;
    cur->left = next->right;
    if(next->right != nil)
        next->right->parent = cur;

    next->right = cur;
    cur->parent = next;
}


