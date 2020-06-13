//
// Created by sadoffnick on 13.06.20.
//

#include "Binomial_Heap.h"



template <class T>
Binomial_Heap<T>::Binomial_Heap(vector<shared_ptr<T>> heap_base){
    head = nullptr;
    int n = heap_base.size();
    if(n == 0)
        return;
    auto header = make_shared<Binomial_Node<T>>(heap_base[0]);
    head = header;
    mask = 1;
    for(int i = 1; i < n; i++){
        auto add_heap = make_shared<Binomial_Heap<T>>(heap_base[i]);
        merge_heap(add_heap);
    }
}

template <class T>
void Binomial_Heap<T>::merge_heap(shared_ptr<Binomial_Node<T> > second_heap) {

}


template <class T>
bool Binomial_Heap<T>::insert_element(shared_ptr<T> element){
    auto new_heap_head = make_shared<Binomial_Heap<T>>(element);
    merge_heap(new_heap_head);
}