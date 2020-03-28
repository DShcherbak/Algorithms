#include <iostream>
#include "Binary_Search_Tree.h"
#include "Red_Black_Tree.h"
#include "Tree.h"
#include <cassert>

int main() {
    auto BT = new Binary_Search_Tree<int>();
   // auto RBT = new Red_Black_Tree<int>();
    BT->insert_element(3);
    BT->print_tree();

   // RBT->insert_element(3);
//    std::cout << (BT->find_element(3) ? "Binary okay" : "NO!") << std::endl;
//    std::cout << (BT->find_element(4) ? "NO!" : "Binary okay") << std::endl;
  //  std::cout << (RBT->find_element(3) ? "Rb okay" : "NO!") << std::endl;
 //   std::cout << (RBT->find_element(4) ? "NO!" : "rb okay") << std::endl;
    BT->insert_element(2);
    BT->insert_element(7);
    BT->insert_element(5);
    BT->print_tree();
    std::cout << "--------------------------------------\n";
    std::cout << "--------------------------------------\n";
    BT->insert_element(9);
    BT->insert_element(4);
    BT->insert_element(6);
    BT->insert_element(8);
    BT->insert_element(10);
    BT->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i == 1) ^ BT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }

    BT->delete_element(7);
    BT->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i == 1 || i == 7) ^ BT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }
    BT->delete_element(2);
    BT->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i == 1 || i == 7 || i == 2) ^ BT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }
    BT->delete_element(9);
    BT->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i == 1 || i == 7 || i == 2 || i == 9) ^ BT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }
    BT->delete_element(3);
    BT->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i < 4 || i == 7 || i == 9) ^ BT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }

    delete BT;
    return 0;
}
