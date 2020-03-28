using namespace std;

int randomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

template <class T>
Binary_Search_Tree<T>::~Binary_Search_Tree(){
    TreeInterface<T>::delete_subtree(head);
}

template <class T>
void Binary_Search_Tree<T>::insert_element(const T& new_elem){
    Node<T>* cur = head;
    auto new_node = new Node<T>(new_elem);
    while(cur){
        if(cur->value == new_elem){
            if(!cur->left){
                cur->left = new_node;
                new_node->parent = cur;
                return;
            }
            else if(!cur->right){
                cur->right = new_node;
                new_node->parent = cur;
                return;
            }
            else{
                int ran = randomInt(0,1);
                if(ran)
                    cur = cur->left;
                else
                    cur = cur->right;
            }
        }else if(cur->value < new_elem){
            if(!cur->right){
                cur->right = new_node;
                new_node->parent = cur;
                return;
            }
            else
                cur = cur->right;
        }else{
            if(!cur->left){
                cur->left = new_node;
                new_node->parent = cur;
                return;
            }
            else
                cur = cur->left;
        }
    }
    if(cur == head)
        head = new_node;
} //for now BST

template <class T>
void Binary_Search_Tree<T>::print_tree(){
    if(!head)
        std::cout << "Tree is empty!\n";
    else
        TreeInterface<T>::print_node(head);
}

template <class T>
bool Binary_Search_Tree<T>::find_element(const T& elem){
    return TreeInterface<T>::find_node(head, elem);
}


template <class T>
void Binary_Search_Tree<T>::delete_node(Node<T>* cur){
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
        head = new_cur;
    else if(cur->parent->left == cur)
        cur->parent->left = new_cur;
    else
        cur->parent->right = new_cur;
    delete cur;
}

template <class T>
void Binary_Search_Tree<T>::transplant_tree(Node<T>* old_node, Node<T>* new_node){
    if(!old_node->parent)
        head = new_node;
    else if(old_node->parent->left == old_node)
        old_node->parent->left = new_node;
    else
        old_node->parent->right = new_node;
    if(new_node){
        new_node->parent = old_node->parent;
    }

}

template <class T>
Node<T>* Binary_Search_Tree<T>::minimum(Node<T>* cur){
    while(cur->left)
        cur = cur->left;
    return cur;
}


template <class T>
void Binary_Search_Tree<T>::delete_element(const T& elem){
    Node<T>* cur = head;
    while(cur){
        if(cur->value == elem){
            delete_node(cur);
            return;
        }else if(cur->value < elem){
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
