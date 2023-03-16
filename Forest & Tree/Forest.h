#pragma once
#include <iostream>
#define MAX_CARD 100
#define Default_Node 5
#include <vector>

#include "Graph.h"

using namespace std;

class Forest : public Graph{
public:
    Forest();
    Forest(int);
    bool cycle_exists();
    bool find_cycle(int,vector<bool>&);
    bool add_edge(int,int);
};