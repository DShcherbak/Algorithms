#include "B_Tree.h"

const double INF = 1e9+7;

template <class T>
B_Tree<T>::B_Tree()  {

}

template <class T>
B_Tree<T>::~B_Tree(){
    TreeInterface<T>::delete_subtree(root);
}


template <class T>
void B_Tree<T>::print(){
    if(!root)
        std::cout << "Tree is empty!\n";
    else
        B_Tree<T>::print_node(root);
}



template <class T>
bool B_Tree<T>::insert_element(shared_ptr<T>) {
    std::cout << "Не можна вставляти елементи в оптимальне бінарне дерево.\n";
    std::cout << "Для збереження властивостей дерево має бути статичним." << endl;

    return false;
}

template <class T>
void B_Tree<T>::delete_element(shared_ptr<T>) {
    std::cout << "Не можна видаляти елементи з оптимального бінарного дерева.\n";
    std::cout << "Для збереження властивостей дерево має бути статичним." << endl;
}

template <class T>
void B_Tree<T>::print_node(B_Node<T>* cur, int depth, bool left, vector<bool> draw) {
    if (cur == nullptr)
        return;
    vector<bool> new_draw = draw;
    new_draw.push_back(false);
    if (depth > 0)
        new_draw[depth] = left;
    if(cur->right != nullptr){
        print_node(cur->right, depth + 1, false, new_draw);
        for (int i = 0; i <= depth; i++) {
            cout << (new_draw[i] ? "|" : " ") << "\t";
        }
        cout << "|\n";
    }
    for (int i = 0; i < depth; i++) {
        cout << (draw[i] ? "|" : " ") << "\t";
    }

//    cout <<  "(" << _values_probabilities[0] << ")";
    cout << convert_to_string(cur->value) << std::endl;


    if(depth > 0)
        new_draw[depth] = !left;
    if(cur->left != nullptr){
        for (int i = 0; i <= depth; i++) {
            cout << (new_draw[i] ? "|" : " ") << "\t";
        }
        cout << "|\n";
        print_node(cur->left, depth + 1, true, new_draw);
    }
}


template<class T>
node B_Tree<T>::find_leaf(node cur, shared_ptr<T> elem) {
    while(!cur->is_leaf){
        for(int i = 0, n = cur->keys.size(); i < n; i++){
            if(cur->keys[i] >= convert_to_string(elem)){
                cur = cur->children[i];
                break;
            }
            cur = cur->children[n];
        }
    }
    return cur;
}

template <class T>
bool B_Tree<T>::find_element(shared_ptr<T> elem){
    auto leaf = find_leaf(root, elem);
    int i = 0;
    int result = 0;
    for(int n = leaf->keys.size(); i < n; i++){
        if(leaf->keys[i] == convert_to_string(elem))
            break;
    }
    return i != leaf->keys.size();
}







template<class T>
void B_Tree<T>::perform(const string &command) {
}

