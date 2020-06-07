#include "Persistent_Tree.h"


#include "Persistent_Tree.h"

using namespace std;


template <class T>
Persistent_Tree<T>::Persistent_Tree(){
    nil = make_shared<PNode<T>> (PNode<T>());
    roots[0] = nil;
    current = 0;
}

template <class T>
Persistent_Tree<T>::Persistent_Tree(vector <shared_ptr<T>> included){
    nil = make_shared<PNode<T>> (PNode<T>());
    roots.push_back(nil);
    last = 0;
    current = 0;
    for(int i = 0, n = included.size(); i < n; i++){
        free_insert(included[i]);
    }
    current = 0;
}

template <class T>
void Persistent_Tree<T>::free_insert(shared_ptr<T> new_elem){
    shared_ptr<PNode<T>> cur = roots[0];
    auto prev = cur;
    auto new_node = make_shared<PNode<T>>(PNode<T>(new_elem));
    new_node->left = nil;
    new_node->right = nil;
    while(cur != nil){
        prev = cur;
        if((*cur->value) == (*new_elem)){
            return;
        }
        else if((*cur->value) < (*new_elem))
            cur = cur->right;
        else
            cur = cur->left;

    }
    new_node->parent = prev;
    if(cur == roots[0]){
        roots[0] = new_node;
        roots[0]->parent = nil;
    }else if((*new_node->value) < (*prev->value))
        prev->left = new_node;
    else
        prev->right = new_node;
    new_node->black = false;
    insert_fix_free(new_node);
}

template <class T>
void Persistent_Tree<T>::insert_fix_free(shared_ptr<PNode<T>> cur){
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
    roots[0]->black = true;
}

template <class T>
Persistent_Tree<T>::~Persistent_Tree()= default;

template <class T>
void Persistent_Tree<T>::delete_subtree(shared_ptr<PNode<T>> cur) {
    if(!cur)
        return;
    if(cur == nil)
        return;
    delete_subtree(cur->left);
    delete_subtree(cur->right);
    //delete cur;
}

template <class T>
shared_ptr<PNode<T>> make_full_copy(shared_ptr<PNode<T>> old){
    string name = convert_to_string(old->value);
    auto new_cur = make_shared<PNode<T>>(PNode<T>(make_shared<T>(name)));
    new_cur->left = old->left;
    new_cur->right = old->right;
    new_cur->parent = old->parent;
    new_cur->black = old->black;
    return new_cur;
}

template <class T>
void fully_reconnect(shared_ptr<PNode<T>> new_node, shared_ptr<PNode<T>> father = nullptr, bool left = true) {
    new_node->left->parent = new_node;
    new_node->right->parent = new_node;
    if(father){
        if(left)
            father->left = new_node;
        else
            father->right = new_node;
    }
}

template <class T>
bool Persistent_Tree<T>::insert_element(shared_ptr<T> new_elem){
    if(current != last){
        cout << "Вставлення нового елементу неможливо, поки ви переглядаєте історію.";
        cout << "Поверніться в поточний стан (" << last << ") для виконання цієї операції.\n";
        return false;
    }
    if(find_element(new_elem))
        return false;
    current++;
    last++;

    //create new root
    auto new_root = make_full_copy(roots[current-1]);
    fully_reconnect(new_root);
    roots.push_back(new_root);

    // create cir and prev pointers
    shared_ptr<PNode<T>> cur = new_root;
    auto prev = cur;

    //create new node to insert
    auto new_node = make_shared<PNode<T>>(PNode<T>(new_elem));
    new_node->left = nil;
    new_node->right = nil;

    //going down the tree
    while(cur != nil){
        prev = cur;
        if((*cur->value) < (*new_elem)){
            if(cur->right != nil){
                auto new_cur = make_full_copy(cur->right);
                fully_reconnect(new_cur, cur, false);
            }
            cur = cur->right;
        }
        else{
            if(cur->left != nil){
                auto new_cur = make_full_copy(cur->left);
                fully_reconnect(new_cur, cur, left);
            }
            cur = cur->left;
        }
    }

    new_node->parent = prev;

    if(cur == roots[current]){
        roots[current] = new_node;
        roots[current]->parent = nil;
    } else if((*new_node->value) < (*prev->value))
        prev->left = new_node;
    else
        prev->right = new_node;
    new_node->black = false;

    insert_fix(new_node);
    return true;
} //for now BST

template <class T>
void Persistent_Tree<T>::insert_fix(shared_ptr<PNode<T>> cur){
    while(!cur->parent->black){
        if(cur->parent == cur->parent->parent->left){
            auto uncle = cur->parent->parent->right;
            if(!uncle->black){
                cur->parent->black = true;
                auto new_uncle = make_full_copy(uncle);
                fully_reconnect(uncle, cur->parent->parent, false);

                new_uncle->black = true;
                new_uncle->parent->black = false;
                cur = new_uncle->parent;
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
                auto new_uncle = make_full_copy(uncle);
                fully_reconnect(new_uncle, cur->parent->parent, true);

                new_uncle->black = true;
                new_uncle->parent->black = false;
                cur = new_uncle->parent;
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
    roots[current]->black = true;
}

template <class T>
void Persistent_Tree<T>::delete_fix(shared_ptr<PNode<T>> cur) {
    shared_ptr<PNode<T>> brother;
    while(cur != roots[current] && cur->black){
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
                cur = roots[current];
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
                    cur = roots[current];
                }
            }
        }
    }
    cur->black = true;
}

template <class T>
void Persistent_Tree<T>::print(){
    if(roots[current] == nil)
        std::cout << "Tree is empty!\n";
    else
        Persistent_Tree<T>::print_node(roots[current]);
    cout << "-------------------------------" << endl;
}

template <class T>
void Persistent_Tree<T>::print_node(shared_ptr<PNode<T>> cur, int depth, bool left, vector<bool> draw) {
    if (cur == nil)
        return;
    vector<bool> new_draw = draw;
    new_draw.push_back(false);
    if (depth > 0)
        new_draw[depth] = left;
    if(cur->right != nil){
        print_node(cur->right, depth + 1, false, new_draw);
        for (int i = 0; i <= depth; i++) {
            cout << (new_draw[i] ? "|" : " ") << "\t";
        }
        cout << "|\n";
    }
    for (int i = 0; i < depth; i++) {
        cout << (draw[i] ? "|" : " ") << "\t";
    }

    if (cur->black)
        cout << "(B)";
    else
        cout << "(R)";
    cout << convert_to_string(cur->value) << std::endl;

    if(depth > 0)
        new_draw[depth] = !left;
    if(cur->left != nil){
        for (int i = 0; i <= depth; i++) {
            cout << (new_draw[i] ? "|" : " ") << "\t";
        }
        cout << "|\n";
        print_node(cur->left, depth + 1, true, new_draw);
    }
}

template <class T>
bool Persistent_Tree<T>::find_element(shared_ptr<T> elem){
    return Persistent_Tree<T>::find_node(roots[current], elem);
}


template <class T>
void Persistent_Tree<T>::delete_node(shared_ptr<PNode<T>> cur) {
    if(current != last){
        cout << "Видалення неможливо, поки ви переглядаєте історію.";
        cout << " Поверніться в поточний стан (" << last << ") для видалення.\n";
        return;
    }
    shared_ptr<PNode<T>> alt_cur = cur;
    bool is_alt_cur_black = alt_cur->black;
    shared_ptr<PNode<T>> new_cur;
    if(cur->left == nil){
        new_cur = cur->right;
        transplant_tree(cur, cur->right);
    }
    else if(cur->right == nil){
        new_cur = cur->left;
        transplant_tree(cur, cur->left);
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
    //delete cur;
    if(is_alt_cur_black)
        delete_fix(new_cur);



}

template <class T>
void Persistent_Tree<T>::transplant_tree(shared_ptr<PNode<T>> old_node, shared_ptr<PNode<T>> new_node){
    if(old_node->parent == nil)
        roots[current] = new_node;
    else if(old_node->parent->left == old_node)
        old_node->parent->left = new_node;
    else
        old_node->parent->right = new_node;
    new_node->parent = old_node->parent;

}

template <class T>
shared_ptr<PNode<T>> Persistent_Tree<T>::minimum(shared_ptr<PNode<T>> cur){
    while(cur->left != nil)
        cur = cur->left;
    return cur;
}

template <class T>
void Persistent_Tree<T>::delete_element(shared_ptr<T> elem){
    shared_ptr<PNode<T>> cur = roots[current];
    while(cur != nil){
        if((*cur->value) == (*elem)){
            delete_node(cur);
            return;
        }else if((*cur->value) < (*elem)){
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
void Persistent_Tree<T>::left_rotate(shared_ptr<PNode<T>>cur) {
    if(cur->right == nil)
        return;
    auto next = cur->right;
    if(cur->parent == nil)
        roots[current] = next;
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
void Persistent_Tree<T>::right_rotate(shared_ptr<PNode<T>> cur) {
    if(cur->left == nil)
        return;
    auto next = cur->left;
    if(cur->parent == nil)
        roots[current] = next;
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

template<class T>
bool Persistent_Tree<T>::find_node(shared_ptr<PNode<T>>cur, shared_ptr<T> value) {
    if(cur == nil)
        return false;
    if((*cur->value) == (*value))
        return true;
    else if((*cur->value) > (*value))
        return find_node(cur->left, value);
    else
        return find_node(cur->right, value);
}

template <class T>
void Persistent_Tree<T>::history() {
    int number = 0;
    cout << "Ви переглядаєте дерево в стані: " << current << endl;
    cout << "Поточний стан дерева: " << last << endl;
    cout << "Введіть номер стану дерева, до якого бажаєте перейти: ";
    cin >> number;
    if(number < 0 || number > last){
        current = last;
    } else {
        current = number;
    }
    cout << "Дерево перейшло в стан номер " << current << endl;
}

template <class T>
void Persistent_Tree<T>::perform(const string &command) {
    if (command == "history"){
        history();
    }else{
        cout << "No such command for Persistent tree: " << command << endl;
    }
}


