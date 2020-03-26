/*#include "Node.h"

void add_node_to_tree(Node* head, Node* new_node){
    if(!head){
        head = new_node;
        return;
    }
    Node* parent = head;
    while(parent){
        if(parent->value > new_node->value){
            if(parent->left)
                parent = parent->left;
            else{
                parent->left = new_node;
                new_node->parent = parent;
            }
        }else if(parent->value < new_node->value){
            if(parent->right)
                parent = parent->right;
            else{
                parent->right = new_node;
                new_node->parent = parent;
            }
        } else
            return;
    }
}

Node* search_value_in_tree(Node* head, int value){
    Node* cur = head;
    while(cur){
        if(value > cur->value){
            if(!cur->right)
                return nullptr;
            else
                cur = cur->right;
        }
        else if(value < cur->value){
            if(!cur->left)
                return nullptr;
            else
                cur = cur->left;
        }
        else{
            return cur;
        }
    }
    return nullptr;
}

void delete_node(Node* head, Node* del){
    if(del == head){
        if(!(del->left || del->right)){
            delete head;
        }else if(del->left){
            delete head;
            head = //chose new head
        }
    }
}

void delete_node_by_value(Node* head, int value);

int max_value(Node* head){
    Node* cur = head;
    while(cur->right){
        cur = cur->right;
    }
    return cur->value;
}

int min_value(Node* head){
    Node* cur = head;
    while(cur->left){
        cur = cur->left;
    }
    return cur->value;
}
*/