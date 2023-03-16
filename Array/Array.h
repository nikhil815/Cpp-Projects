#pragma once
#include <iostream>

using namespace std;

#define MAX_ELEM 100

template <typename type>
class Array
{
    
private:
	type* elements;
	int capacity;
	int lowerbound;
	int upperbound;
	int dummy;
public:
	Array();
	Array(int);
	Array(int, int);
	Array(const Array <type> &);
	~Array();
	bool add_item(type);
	void remove_item();
	bool remove_item(type);
	bool insert_item(int, type);
	void erase_item(int);
	bool find_item(type, int&);
	int find_pos(type);
	int get_lower();
	int get_upper();
	Array<type>& operator=(Array<type>&);
	type& operator[](int);
    template <typename typex> friend ostream& operator<<(ostream&, Array<typex>&);
};