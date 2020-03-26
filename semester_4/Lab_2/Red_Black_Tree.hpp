int randomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

template <class T>
void Red_Black_Tree<T>::insert_element(T new_elem) {
    Node<T>* cur = head;
    auto new_node = Node<T>(new_elem);
    while(cur){
        if(cur->value == new_elem){
            if(!cur->left){
                cur->left = new_node;
                return;
            }
            else if(!cur->right){
                cur->right = new_node;
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
                return;
            }
            else
                cur = cur->right;
        }else{
            if(!cur->left){
                cur->left = new_node;
                return;
            }
            else
                cur = cur->left;
        }
    }
} //for now BST

template <class T>
bool Red_Black_Tree<T>::find_element(T elem){
    Node<T>* cur = head;
    while(cur){
        if(cur->value == elem){
            return true;
        }else if(cur->value < elem){
            if(!cur->right)
                return false;
            else
                cur = cur->right;
        }else{
            if(!cur->left)
                return false;
            else
                cur = cur->left;
        }
    }
}


template <class T>
void Red_Black_Tree<T>::transplant_tree(Node<T>* old, Node<T>* to){

}

template <class T>
Node<T>* minimum(Node<T>* cur){
    while(cur->left)
        cur = cur->left;
    return cur;
}

template <class T>
void Red_Black_Tree<T>::delete_node(Node<T>* cur){
    Node<T>* new_cur = nullptr;
    if(cur->left == nullptr)
        new_cur = cur->right;
    else if(cur->right == nullptr)
        new_cur = cur->left;
    else{
        new_cur = minimum(cur->right);
        if(new_cur->parent == cur)
            new_cur->left = cur->left;
        else{
            transplant_tree(new_cur, new_cur->right);
            new_cur->right = cur->right;
            new_cur->right->parent = new_cur;
        }
    }

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
void Red_Black_Tree<T>::delete_element(T elem){
    Node<T>* cur = head;
    while(cur){
        if(cur->value == elem){
            delete_node(cur);
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
} //only for BST
