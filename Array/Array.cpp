#include <iostream>
#include "Array.h"

using namespace std;
template <typename typex>
ostream& operator<<(ostream& out, Array<typex>& list)
{
    int i;
	
	for (i = list.get_lower(); i <= list.get_upper(); ++i)
	{
		if (i != 0) out << ", ";
		out << list[i];
	}

	return out;
}
template <typename type>
Array<type>::Array()
{
	capacity = 0;
	lowerbound = upperbound = -1;
	dummy = 0;
	elements = NULL;
}

template <typename type>
Array<type>::Array(int n)
{
	capacity = 0;
	lowerbound = upperbound = -1;
	dummy = 0;
	elements = new type[n + MAX_ELEM];
	if (elements == NULL)
		cout << "Not enough memory!" << endl;
	else
	{
		lowerbound = 0;
		upperbound = n - 1;
		capacity = n + MAX_ELEM;
	}
}

template <typename type>
Array<type>::Array(int lb, int ub)
{
	int n = ub - lb + 1;
	capacity = 0;
	lowerbound = upperbound = -1;
	dummy = 0;
	elements = new type[n + MAX_ELEM];
	if (elements == NULL)
		cout << "Not enough memory!" << endl;
	else
	{
		lowerbound = lb;
		upperbound = ub;
		capacity = n + MAX_ELEM;
	}
}

template <typename type>
Array<type>::Array(const Array<type>& ar)
{
	int i;
	capacity = 0;
	lowerbound = upperbound = -1;
	dummy = 0;
	type * temp = new type[ar.capacity];
	if (temp == NULL)
		cout << "Not enough memory!" << endl;
	else
	{
		int n = ar.upperbound - ar.lowerbound + 1;
		for (i = 0; i < n; ++i)
			temp[i] = ar.elements[i];
		lowerbound = ar.lowerbound;
		upperbound = ar.upperbound;
		capacity = ar.capacity;
		delete[] elements;
		elements = temp;
	}
}

template <typename type>
Array<type>::~Array()
{
	delete[] elements;
}
template <typename type>
bool Array<type>::add_item(type x)
{
	int i, n = upperbound - lowerbound + 1;
	if (n == capacity)
	{
		type* temp = new int[capacity + MAX_ELEM / 2];
		if (temp == NULL)
		{
			cout << "Not enough memory!" << endl;
			return false;
		}

		for (i = 0; i < n; ++i)
			temp[i] = elements[i];

		delete[] elements;
		elements = temp;
	}

	elements[n] = x;
	++upperbound;
	return true;
}
template <typename type>
int Array<type>::get_lower()
{
	return lowerbound;
}
template <typename type>
int Array<type>::get_upper()
{
	return upperbound;
}
template <typename type>
bool Array<type>::insert_item(int pos, type x)
{
	if (pos < lowerbound || pos > upperbound)
	{
		cout << "Index out of range!" << endl;
		return false;
	}

	int i, n = upperbound - lowerbound + 1;
	if (n == capacity)
	{
		type* temp = new int[capacity + MAX_ELEM / 2];
		if (temp == NULL)
		{
			cout << "Not enough memory!" << endl;
			return false;
		}

		for (i = 0; i < n; ++i)
			temp[i] = elements[i];

		delete[] elements;
		elements = temp;
	}

	for (i = upperbound; i >= pos - lowerbound; --i)
		elements[i] = elements[i - 1];
	
	elements[pos - lowerbound] = x;
	++upperbound;
	return true;
}
template <typename type>
void Array<type>::remove_item()
{
	if (lowerbound < upperbound)
		--upperbound;
}
template <typename type>
bool Array<type>::remove_item(type x)
{
	int i;
	int pos = find_pos(x) ;
	if(pos == -1){
		return false;
	}

	erase_item(pos);
	return true;
}
template <typename type>
void Array<type>::erase_item(int pos)
{
	if (pos < lowerbound || pos > upperbound)
	{
		cout << "Index out of range!" << endl;
		return;
	}

	int i;
	for (i = pos - lowerbound; i < upperbound; ++i)
		elements[i] = elements[i + 1];

	--upperbound;
}
template <typename type>
bool Array<type>::find_item(type x, int& pos)
{
	int i;
	for (i = lowerbound; i <= upperbound; ++i)
	{
		if (elements[i - lowerbound] == x)
		{
			pos = i;
			return true;
		}
	}

	pos = lowerbound - 1;
	return false;
}
template <typename type>
int Array<type>::find_pos(type x)
{
	int i;
	for (i = lowerbound; i <= upperbound; ++i)
	{
		if (elements[i - lowerbound] == x)
		{
			return i;
		}
	}

	return -1;
}
template <typename type>
Array<type>& Array<type>::operator=(Array<type> &ar)
{
	int i;
	capacity = 0;
	lowerbound = upperbound = -1;
	dummy = 0;
	type *temp = new type[ar.capacity];
	if (temp == NULL)
		cout << "Not enough memory!" << endl;
	else
	{
		int n = ar.upperbound - ar.lowerbound + 1;
		for (i = 0; i < n; ++i)
			temp[i] = ar.elements[i];
		lowerbound = ar.lowerbound;
		upperbound = ar.upperbound;
		capacity = ar.capacity;
		delete[] elements;
		elements = temp;
	}

	return *this;
}
template <typename type>
type& Array<type>::operator[](int index)
{
	if (index < lowerbound || index > upperbound)
	{
		cout << "Index out of range!" << endl;
		return dummy;
	}

	return elements[index - lowerbound];
}