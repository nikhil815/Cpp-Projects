#pragma once
#include <iostream>
#define MAX_CARD 100
#define Default_Node 5
#include <vector>

#include "Graph.h"
#include "Forest.h"

using namespace std;
class Tree : public Forest{
private:
    int last_vertex;
    int root;
public:
    Tree();
    bool add_vertex(int);
    Tree operator++();
    Tree operator--();
    bool set_root(int);
};