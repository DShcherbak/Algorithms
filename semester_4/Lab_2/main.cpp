#include <iostream>
#include "Binary_Search_Tree.h"
#include "Red_Black_Tree.h"
#include "Tree.h"
#include <cassert>

int main() {
    auto RBT = new Red_Black_Tree<int>();
    RBT->insert_element(3);

   // RRBT->insert_element(3);
//    std::cout << (RBT->find_element(3) ? "Binary okay" : "NO!") << std::endl;
//    std::cout << (RBT->find_element(4) ? "NO!" : "Binary okay") << std::endl;
  //  std::cout << (RRBT->find_element(3) ? "Rb okay" : "NO!") << std::endl;
 //   std::cout << (RRBT->find_element(4) ? "NO!" : "rb okay") << std::endl;
    RBT->insert_element(2);
    RBT->print_tree();
    RBT->insert_element(9);
    RBT->print_tree();
    RBT->insert_element(4);
    RBT->print_tree();
    RBT->insert_element(5);
    RBT->print_tree();
    RBT->insert_element(6);
    RBT->print_tree();
    RBT->insert_element(7);
    RBT->print_tree();
    RBT->insert_element(8);
    RBT->print_tree();
    RBT->insert_element(10);
    RBT->print_tree();
    RBT->insert_element(11);
    RBT->print_tree();
    RBT->insert_element(12);
    RBT->print_tree();
    RBT->insert_element(13);
    RBT->print_tree();
    RBT->insert_element(14);
    RBT->print_tree();
    RBT->insert_element(15);
    RBT->print_tree();
    RBT->insert_element(16);
    RBT->print_tree();
    RBT->insert_element(17);
    RBT->print_tree();
    RBT->insert_element(18);
    RBT->print_tree();
    RBT->insert_element(19);
    RBT->print_tree();
    RBT->insert_element(20);
    RBT->print_tree();
    RBT->insert_element(21);
    RBT->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i == 1) ^ RBT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }

    RBT->delete_element(7);
    RBT->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i == 1 || i == 7) ^ RBT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }
    RBT->delete_element(2);
    RBT->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i == 1 || i == 7 || i == 2) ^ RBT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }
    RBT->delete_element(9);
    RBT->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i == 1 || i == 7 || i == 2 || i == 9) ^ RBT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }
    RBT->delete_element(3);
    RBT->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i < 4 || i == 7 || i == 9) ^ RBT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }


    delete RBT;

    return 0;
}
