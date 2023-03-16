#pragma once
#include <iostream>
#define MAX_CARD 100
#define Default_Node 5

using namespace std;

class Node
{
	friend class DoubleLinkedList;
    friend class Graph;
    friend class Forest;
    friend class Tree;

	int data;
	Node* next;
	Node* previous;
	
};
class DoubleLinkedList
{
    friend class Graph;
    friend class Forest;
    friend class Tree;
    
    private:
        Node* head;
        Node* tail;
        int dummy;
    public:
        DoubleLinkedList();
        ~DoubleLinkedList();
        bool add_to_front(int);
        bool add_to_back(int);
        int  count_nodes();
        bool insert_item(int, int);
        bool search(int);
        void remove_item(int);
        void remove_from_front();
        void remove_from_back();
        int& operator[](int);
        friend ostream& operator<<(ostream&, DoubleLinkedList&);
};
class Graph{
    
    protected:
        DoubleLinkedList* elems;
        int size;
        int cap;

    public:
        //constructors
        Graph();
        Graph(int);
        Graph(const Graph&);
        ~Graph();

        bool edge_exists(int,int);
        bool add_edge(int,int);
        bool remove_edge(int,int);
        int get_degree(int);
        bool path_exists(int,int);

        Graph operator++();
		Graph operator--();
		Graph operator++(int);
		Graph operator--(int);
        friend ostream& operator<<(ostream&, Graph&);

};