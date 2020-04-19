#include <iostream>
#include "Binary_Search_Tree.h"
#include "Red_Black_Tree.h"
#include "Tree.h"
//#include "../Folder.h"
#include "Order_Statistic_Tree.h"
#include <cassert>
#include "../sqlite3pp-master/headeronly_src/sqlite3pp.h"
#include "../testing/testing.cpp"
#include <vector>
#include <set>

void check_RBTree(){
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
    cout << "Insertion done!\n";
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
    /*  RBT->delete_element(9);
      RBT->print_tree();
      for(int i = 1; i <= 10; i++){
          assert(((i == 1 || i == 7 || i == 2 || i == 9) ^ RBT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
      }
      RBT->delete_element(3);
      RBT->print_tree();
      for(int i = 1; i <= 10; i++){
          assert(((i < 4 || i == 7 || i == 9) ^ RBT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
      }*/
    RBT->delete_element(15);
    RBT->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i == 1 || i == 7 || i == 2) ^ RBT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }
    RBT->delete_element(17);
    RBT->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i == 1 || i == 7 || i == 2) ^ RBT->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }
    delete RBT;

}

void check_OSTree(){
    auto OST = new Order_Statistic_Tree<int>();
    OST->insert_element(3);

    // ROST->insert_element(3);
//    std::cout << (OST->find_element(3) ? "Binary okay" : "NO!") << std::endl;
//    std::cout << (OST->find_element(4) ? "NO!" : "Binary okay") << std::endl;
    //  std::cout << (ROST->find_element(3) ? "Rb okay" : "NO!") << std::endl;
    //   std::cout << (ROST->find_element(4) ? "NO!" : "rb okay") << std::endl;
    OST->insert_element(2);
    OST->print_tree();
    OST->insert_element(9);
    OST->print_tree();
    OST->insert_element(4);
    OST->print_tree();
    OST->insert_element(5);
    OST->print_tree();
    OST->insert_element(6);
    OST->print_tree();
    OST->insert_element(7);
    OST->print_tree();
    OST->insert_element(8);
    OST->print_tree();
    OST->insert_element(10);
    OST->print_tree();
    OST->insert_element(11);
    OST->print_tree();
    OST->insert_element(12);
    OST->print_tree();
    OST->insert_element(13);
    OST->print_tree();
    OST->insert_element(14);
    OST->print_tree();
    OST->insert_element(15);
    OST->print_tree();
    OST->insert_element(16);
    OST->print_tree();
    OST->insert_element(17);
    OST->print_tree();
    OST->insert_element(18);
    OST->print_tree();
    OST->insert_element(19);
    OST->print_tree();
    OST->insert_element(20);
    OST->print_tree();
    OST->insert_element(21);
    OST->print_tree();
    cout << "Insertion done!\n";
    for(int i = 1; i <= 10; i++){
        assert(((i == 1) ^ OST->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }

    OST->delete_element(7);
    OST->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i == 1 || i == 7) ^ OST->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }
    OST->delete_element(2);
    OST->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i == 1 || i == 7 || i == 2) ^ OST->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }
      OST->delete_element(9);
      OST->print_tree();
      for(int i = 1; i <= 10; i++){
          assert(((i == 1 || i == 7 || i == 2 || i == 9) ^ OST->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
      }
      OST->delete_element(3);
      OST->print_tree();
      for(int i = 1; i <= 10; i++){
          assert(((i < 4 || i == 7 || i == 9) ^ OST->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
      }
    OST->delete_element(15);
    OST->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i < 4  || i == 7 || i == 9) ^ OST->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }
    OST->delete_element(17);
    OST->print_tree();
    for(int i = 1; i <= 10; i++){
        assert(((i < 4  || i == 7 || i == 9) ^ OST->find_element(i)) && (cout << "Test \"" << i << "\" complete.\n"));
    }

    cout << OST->get_element(10) << endl;
    OST->delete_element(OST->get_element(10));
    OST->print_tree();
    cout << OST->get_element(10) << endl;
    delete OST;

}

int main() {
//    vector <Folder*> included = read_folders_from_database("included");
//    vector <Folder*> excluded = read_folders_from_database("excluded");
    //print_folders(included, excluded);
    auto OST = new Order_Statistic_Tree<Folder*>;
//    for(auto & fold : included)
//        OST->insert_element(fold);
//    assert(test_for_correct_folders(OST, included, excluded) && cout << "Test for insertion passed.\nTest for search passed\n");
    set <Folder*> deleted;
//    for(auto & fold : included){
        if(randomInt(1,6) == 6){
//            OST->delete_element(fold);
 //           deleted.insert(fold);
        }
  //  }
   // assert(test_for_correct_folders(OST, included, excluded, deleted) && cout << "Test for deletion passed.\n");
    return 0;
}
