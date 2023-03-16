#include <iostream>
#include "Graph.h"
#include "Forest.h"
#include <vector>
#include <queue>


using namespace std;

Forest::Forest(){
    elems = new DoubleLinkedList[MAX_CARD];
    size = cap = 0;
    int i;
    if(elems == NULL)
        cout << "Not enough memory for this graph!" << endl;
    else
        size = Default_Node;
        cap = MAX_CARD;

}
Forest::Forest(int n){
    elems = new DoubleLinkedList[MAX_CARD];
    size = cap = 0;
    int i;
    if(elems == NULL)
        cout << "Not enough memory for this graph!" << endl;
    else
        size = n;
        cap = MAX_CARD;
}
bool Forest::cycle_exists()
{
    vector<bool> visited(size, false);
    int i;
    for (i = 1; i < size; i++)
        cout << i << endl;
        if (!visited[i] && find_cycle(i, visited))
            return true;
    return false;
}
bool Forest::find_cycle(int i, vector<bool>& visited)
{
    
    vector<int> parent(size, -1);
    queue<int> q;

    visited[i] = true;
    q.push(i);
 
    while (!q.empty()) {

        int u = q.front();
        q.pop();
        int v;
        int count = 0;
        DoubleLinkedList vertex = elems[u];

        while(count <= (vertex.count_nodes()))

            v = vertex[count];
            count++;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                parent[v] = u;
            }
            
            else if (parent[u] != v)
                return true;
    }
    return false;
}

bool Forest::add_edge(int v1, int v2){
    if(v1 > size || v2 > size || v1<=0 || v2<=0 || edge_exists(v1,v2)){
        return false;
    }
    
    bool success1 = elems[v1].add_to_back(v2);
    bool success2 = elems[v2].add_to_back(v1);

    
    // if(cycle_exists()){
    //     cout << "Cycle exists "<<endl;
    //     remove_edge(v1,v2);
    //     return false;
    // }
    return (success1 && success2);
}

