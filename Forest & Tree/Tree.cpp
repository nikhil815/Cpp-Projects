#include <iostream>
#include "Graph.h"
#include "Forest.h"
#include "Tree.h"
#include <vector>
#include <queue>


using namespace std;
Tree::Tree(){
    elems = new DoubleLinkedList[MAX_CARD];
    size = cap = 0;
    int i;
    if(elems == NULL)
        cout << "Not enough memory for this graph!" << endl;
    else
        size = 1;
        last_vertex = 1;
        root = 1;
        cap = MAX_CARD;
}
Tree Tree::operator++(){
    size++;
    add_edge(last_vertex, size);
    last_vertex = size;
    return (*this);
}
Tree Tree::operator--(){
    int i;
    for(i=1; i<size; i++){
        elems[i].remove_item(last_vertex);
    }
    elems[last_vertex].~DoubleLinkedList();
    size--;
    last_vertex = size;
    
    return (*this);

}
bool Tree::add_vertex(int v){
    if(v<1 || v>size){
        return false;
    }

    size++;
    add_edge(v, size);
    // if(cycle_exists()){
    //     remove_edge(v, size);
    //     size--;
    //     return false;
    // }

    last_vertex = size;
    return true;
}

bool Tree::set_root(int v){
    if(v<1 || v>size){
        return false;
    }
    root  = v;
    return true;
}


