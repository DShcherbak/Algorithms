#include <cassert>

using namespace std;


template <class T>
Order_Statistic_Tree<T>::Order_Statistic_Tree(){
    nil = new OSNode<T>();
    nil->size = 0;
    root = nil;
}

template <class T>
Order_Statistic_Tree<T>::~Order_Statistic_Tree(){
    if(root == nil)
        delete root;
    else{
        Order_Statistic_Tree<T>::delete_subtree(root);
        delete nil;
    }
}

template <class T>
OSNode<T>* Order_Statistic_Tree<T>::get_node(OSNode<T> *cur, int number) {
    int cur_number = cur->left->size + 1;
    if(cur_number == number)
        return cur;
    else if(cur_number > number)
        return get_node(cur->left, number);
    else
        return get_node(cur->right, number-cur_number);
}

template <class T>
void Order_Statistic_Tree<T>::delete_subtree(OSNode<T>* cur) {
    if(cur == nil)
        return;
    delete_subtree(cur->left);
    delete_subtree(cur->right);
    delete cur;
}

template <class T>
void Order_Statistic_Tree<T>::insert_element(const T& new_elem){
    OSNode<T>* cur = root;
    auto prev = cur;
    auto new_node = new OSNode<T>(new_elem);
    new_node->left = nil;
    new_node->right = nil;
    while(cur != nil){
        cur->size++;
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
    insert_fix(new_node);
} //for now BST

template <class T>
void Order_Statistic_Tree<T>::insert_fix(OSNode<T>* cur){
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
void Order_Statistic_Tree<T>::delete_fix(OSNode<T>* cur) {
    OSNode<T>* brother;
    while(cur != root && cur->black){
        if(cur == cur->parent->left){
            brother= cur->parent->right;
            if(!brother->black){
                brother->black = true;
                cur->black = false;
                left_rotate(cur->parent);
                brother = cur->parent->right;
            }
            if(brother->left->black && brother->right->black){
                brother->black = false;
                cur = cur->parent;
            }else {
                if(brother->right->black){
                    brother->left->black = true;
                    brother->black = false;
                    right_rotate(brother);
                    brother = cur->parent->right;
                }
                brother->black = cur->parent->black;
                cur->parent->black = true;
                brother->right->black = true;
                left_rotate(cur->parent);
                cur = root;
            }
        }else {
            if (cur == cur->parent->right) {
                brother = cur->parent->left;
                if (!brother->black) {
                    brother->black = true;
                    cur->black = false;
                    right_rotate(cur->parent);
                    brother = cur->parent->left;
                }
                if (brother->right->black && brother->left->black) {
                    brother->black = false;
                    cur = cur->parent;

                } else {
                    if (brother->left->black) {
                        brother->right->black = true;
                        brother->black = false;
                        left_rotate(brother);
                        brother = cur->parent->left;
                    }
                    brother->black = cur->parent->black;
                    cur->parent->black = true;
                    brother->left->black = true;
                    right_rotate(cur->parent);
                    cur = root;
                }
            }
        }
    }
    cur->black = true;
}

template <class T>
void Order_Statistic_Tree<T>::print_tree(){
    if(root == nil)
        std::cout << "Tree is empty!\n";
    else
        Order_Statistic_Tree<T>::print_node(root);
    cout << "-------------------------------" << endl;
}

template <class T>
void Order_Statistic_Tree<T>::print_node(OSNode<T>* cur, int depth, bool left, vector<bool> draw) {
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
            cout << "B" << "(" << cur->size << ")";
        else
            cout << "R" << "(" << cur->size << ")";
    }
    cout << cur->value << std::endl;

    if(depth > 0) new_draw[depth-1] = !left;
    print_node(cur->left, depth + 1, true, new_draw);


}

template <class T>
bool Order_Statistic_Tree<T>::find_element(const T& elem){
    return Order_Statistic_Tree<T>::find_node(root, elem);
}

template <class T>
void Order_Statistic_Tree<T>::delete_node(OSNode<T>* cur) {
    OSNode<T>* alt_cur = cur;
    bool is_alt_cur_black = alt_cur->black;
    OSNode<T>* new_cur;
    if(cur->left == nil){
        new_cur = cur->right;
        transplant_tree(cur, cur->right);
        recount_size(cur->right);
    }
    else if(cur->right == nil){
        new_cur = cur->left;
        transplant_tree(cur, cur->left);
        recount_size(cur->left);
    }
    else{
        alt_cur = minimum(cur->right);
        is_alt_cur_black = alt_cur->black;
        new_cur = alt_cur->right;
        if(alt_cur->parent == cur)
            new_cur->parent = alt_cur;
        else{
            transplant_tree(alt_cur, alt_cur->right);
            alt_cur->right = cur->right;
            alt_cur->right->parent = alt_cur;
        }
        transplant_tree(cur, alt_cur);
        alt_cur->left = cur->left;
        alt_cur->left->parent = alt_cur;
        alt_cur->black = cur->black;
    }
    recount_size(new_cur);

    delete cur;
    if(is_alt_cur_black)
        delete_fix(new_cur);



}

template <class T>
void Order_Statistic_Tree<T>::transplant_tree(OSNode<T>* old_node, OSNode<T>* new_node){
    if(old_node->parent == nil)
        root = new_node;
    else if(old_node->parent->left == old_node)
        old_node->parent->left = new_node;
    else
        old_node->parent->right = new_node;
    new_node->parent = old_node->parent;

}

template <class T>
void Order_Statistic_Tree<T>::recount_size(OSNode<T>* cur){
    if(cur != nil)
        cur->size = cur->left->size + cur->right->size + 1;
    if(cur->parent != nil)
        recount_size(cur->parent);

}


template <class T>
OSNode<T>* Order_Statistic_Tree<T>::minimum(OSNode<T>* cur){
    while(cur->left != nil)
        cur = cur->left;
    return cur;
}

template <class T>
void Order_Statistic_Tree<T>::delete_element(const T& elem){
    OSNode<T>* cur = root;
    while(cur != nil){
        if(cur->value == elem){
            delete_node(cur);
            return;
        }else if(cur->value < elem){
            if(!cur->right)
                return;
            else{
                cur = cur->right;
            }
        }else{
            if(cur->left == nil)
                return;
            else{
                cur = cur->left;
            }
        }
    }
}

template<class T>
void Order_Statistic_Tree<T>::left_rotate(OSNode<T> *cur) {
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
    next->size = cur->size;
    cur->size = cur->left->size + cur->right->size + 1;
}

template<class T>
void Order_Statistic_Tree<T>::right_rotate(OSNode<T> *cur) {
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

    next->size = cur->size;
    cur->size = cur->left->size + cur->right->size + 1;
}

template<class T>
T Order_Statistic_Tree<T>::get_element(int number) {
    assert(number <= root->size);
    auto node = get_node(root, number);
    return node->value;
}

template<class T>
int Order_Statistic_Tree<T>::get_rank(OSNode<T> *cur) {
    int rank = cur->left->size + 1;
    auto next = cur;
    while(next != root){
        if(next == next->parent->right)
            rank = rank + next->parent->left->size + 1;
        next = next->parent;
    }
    return rank;
}

template<class T>
bool Order_Statistic_Tree<T>::find_node(OSNode<T> *cur, const T &value) {
    if(cur == nil)
        return false;
    if(cur->value == value)
        return true;
    else if(cur->value > value)
        return find_node(cur->left, value);
    else
        return find_node(cur->right, value);
}



