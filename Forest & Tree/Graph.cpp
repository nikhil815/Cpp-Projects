#include <iostream>
#include "Graph.h"

using namespace std;
ostream& operator<<(ostream& out, Graph& list)
{
    int j,k;
    out << "V = {";

    for(k=1;k<=list.size;k++){
        out << k << ",";
    }

    out << "}" << endl;
    out << "E =" << endl << "{" << endl;

    for(j=1; j<=list.size; j++){

        out << "      " << j << "  => ";
        out << list.elems[j] << endl;
    }
	out << "}" << endl;

	return out;
}
Graph::Graph(){
    elems = new DoubleLinkedList[MAX_CARD];
    size = cap = 0;
    int i;
    if(elems == NULL)
        cout << "Not enough memory for this graph!" << endl;
    else
        size = Default_Node;
        cap = MAX_CARD;

}
Graph::Graph(int n){
    elems = new DoubleLinkedList[MAX_CARD];
    size = cap = 0;
    int i;
    if(elems == NULL)
        cout << "Not enough memory for this graph!" << endl;
    else
        size = n;
        cap = MAX_CARD;
}
Graph::Graph(const Graph& v){

        elems = new DoubleLinkedList[v.cap];
        size = cap = 0;
        int i;
        if(elems == NULL)
            cout << "Not enough memory for this graph!" << endl;
        else
            size = v.size;
            cap = v.cap;
            for(i=1; i<=v.size; i++){
                elems[i] = DoubleLinkedList();
                Node* current = v.elems[i].head;
                int data;
                while(current != NULL){
                    data = current->data;
                    elems[i].add_to_back(data);
                    current = current -> next;
                }
                delete current;
            }
}
Graph::~Graph(){
    int i;
    for(i=1;i<=size;i++){
        elems[i].~DoubleLinkedList();
    }
    delete[] elems;
}
bool Graph::edge_exists(int v1, int v2){
    if(v1 > size || v2 > size || v1<=0 || v2<=0){
        return false;
    }

    return (elems[v1].search(v2) && elems[v2].search(v1));
}
bool Graph::add_edge(int v1, int v2){
    if(v1 > size || v2 > size || v1<=0 || v2<=0 || edge_exists(v1,v2)){
        return false;
    }
    
    bool success1 = elems[v1].add_to_back(v2);
    bool success2 = elems[v2].add_to_back(v1);
    return (success1 && success2);
}
bool Graph::remove_edge(int v1, int v2){
    if(v1 > size || v2 > size || v1<=0 || v2<=0 || !edge_exists(v1,v2)){
        return false;
    }
    
    elems[v1].remove_item(v2);
    elems[v2].remove_item(v1);
    return true;
}
int Graph::get_degree(int v){

    if(v > size || v<=0 ){
        cout << "vertex does not exist in graph" << endl;
        return -1;
    }
    int count, i;
    count = elems[v].count_nodes();

    return count;
}
Graph Graph::operator++(){
    
    int new_size = size + 1;

    if(new_size > cap){

        int i, new_cap = cap + (MAX_CARD / 2);
        DoubleLinkedList* temp = new DoubleLinkedList[new_cap];

        if(temp == NULL)
            cout << "Not enough memory for this operation!" << endl;
        else
            int i;
            for(i =1; i<=size; i++){
                temp[i] = elems[i];
            }

            DoubleLinkedList link;
            temp[new_size]= link;

            cap = new_cap;
            size = new_size;
            delete[] elems;
            elems = temp;
            return (*this);
    }

    size = new_size;

    return (*this);
}
Graph Graph::operator++(int){
    
    int new_size = size + 1;

    if(new_size > cap){

        int i, new_cap = cap+ (MAX_CARD / 2);
        DoubleLinkedList* temp = new DoubleLinkedList[new_cap];

        if(temp == NULL)
            cout << "Not enough memory for this operation!" << endl;
        else
            int i;
            for(i =1; i<=size; i++){
                temp[i] = elems[i];
            }

            cap = new_cap;
            size = new_size;
            delete[] elems;
            elems = temp;
            return (*this);
    }

    size = new_size;

    return (*this);
}
Graph Graph::operator--(){
    
    int i;
    for(i=1; i<size; i++){
        elems[i].remove_item(size);
    }
    elems[size].~DoubleLinkedList();
    size--;
    return (*this);

}
Graph Graph::operator--(int){
    
    int i;
    for(i=1; i<size; i++){
        elems[i].remove_item(size);
    }
    elems[size].~DoubleLinkedList();
    size--;
    return (*this);
    
}
bool Graph::path_exists(int v1, int v2){
    
    if(v1<0||v2<0||v1>size||v2>size){
        return false;
    }
    if(v1==v2){
        return true;
    }
    
    int i;
    //create an array of visited vertces
    bool* vis = new bool[cap];
    //using a double linked list to keep track of vertices
    DoubleLinkedList ver;

    for(i=1;i<=size;i++){
        vis[i] = false;
    }

    ver.add_to_front(v1);

    while (ver.count_nodes()!=0){
        int temp,k;
        k = ver.head -> data;
        Node* current = elems[k].head;
        ver.remove_from_front();

        while (current != elems[i].tail || current != NULL){
            
            temp = current -> data;
            if(temp==v2){
                return true;
            }

            if(!vis[temp]){
                vis[temp] = true;
                ver.add_to_back(temp);
            }

            current = current -> next;
        }
    }
    
    return false;

}

//DOUBLE LINKED LIST FUNCTIONS
ostream& operator<<(ostream& out, DoubleLinkedList& list)
{
	int n = list.count_nodes(), i;
	
	for (i = 0; i < n; ++i)
	{
		if (i != 0) out << ", ";
		out << list[i];
	}

	return out;
}

DoubleLinkedList::DoubleLinkedList()
{
	head = tail = NULL;
	dummy = 0;
}

DoubleLinkedList::~DoubleLinkedList()
{
	if (head == NULL)
		return;

	Node* current;
	current = head;

	while (current != NULL)
	{
		Node* temp = current;
		current = current->next;
		delete temp;
	}

	head = tail = NULL;
}

bool DoubleLinkedList::add_to_front(int x)
{
	//Allocating memory for one node using a pointer to a node
	Node* new_node = new Node;

	if (new_node == NULL)
		return false;

	new_node->data = x;
	new_node->next = head;
	new_node->previous = NULL;

	if (head == NULL)
		head = tail = new_node;
	else
	{
		head->previous = new_node;
		head = new_node;
	}

	return true;
}

bool DoubleLinkedList::add_to_back(int x)
{
	//Allocating memory for one node using a pointer to a node
	Node* new_node = new Node;

	if (new_node == NULL)
		return false;
	
	new_node->data = x;
	new_node->next = NULL;
	new_node->previous = NULL;

	if (head == NULL)
		head = tail = new_node;
	else
	{
		tail->next = new_node;
		new_node->previous = tail;
		tail = new_node;
	}

	return true;
}

bool DoubleLinkedList::search(int x)
{
	Node* current;

	for (current = head; current != NULL; current = current->next)
		if (current->data == x) return true;

	return false;
}

bool DoubleLinkedList::insert_item(int pos, int x)
{
	int i;
	Node* current;
	Node* new_node;
	if (pos == 0)
		return add_to_front(x);
	
	int n = count_nodes();
	if (pos == n)
		return add_to_back(x);

	if (pos > n)
	{
		cout << "Position is out of range!" << endl;
		return false;
	}
	//Allocating memory for one node to be added
	//to the linked list
	new_node = new Node;

	if (new_node == NULL)
		return false;

	new_node->data = x;
	new_node->next = NULL;
	new_node->previous = NULL;

	current = head;
	for (i = 0; i < pos; ++i)
		current = current->next;

	new_node->next = current;
	new_node->previous = current->previous;
	new_node->previous->next = new_node;
	current->previous = new_node;

	return true;
}

int DoubleLinkedList::count_nodes()
{
	int c = 0;
	Node* current;

	for (current = head; current != NULL; current = current->next)
		++c;

	return c;
}

void DoubleLinkedList::remove_from_front()
{
	if (head == NULL)
		return;

	Node* temp = head;

	//If we do not check head is NULL
	//NULL pointer exception
	if (head == tail)
		head = tail = NULL;
	else	
		head = head->next;
	
	delete temp;
}

void DoubleLinkedList::remove_item(int x)
{
	if (head == NULL)
		return;

	if (head->data == x)
	{
		remove_from_front();
		return;
	}

	if (tail->data == x)
	{
		remove_from_back();
		return;
	}

	Node* current;
	for (current = head; current != NULL; current = current->next)
	{
		if (current->data == x)
		{
			Node* temp = current;
			current->previous->next = current->next;
			current->next->previous = current->previous;
			delete temp;
			break;
		}
	}
}

void DoubleLinkedList::remove_from_back()
{
	if (head == NULL)
		return;

	if (head == tail)
	{
		remove_from_front();
		return;
	}

	Node* temp = tail;
	tail->previous->next = NULL;
	tail = tail->previous;
	delete temp;
}

int& DoubleLinkedList::operator[](int index)
{
	int i, n = count_nodes();

	if (index < 0 || index >= n)
	{
		cout <<index << "Index out of range!" << endl;
		return dummy;
	}

	Node* current = head;
	for (i = 0; i < index; ++i)
		current = current->next;

	return current->data;
}