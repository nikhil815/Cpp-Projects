#include <iostream>
#include "Vector.h"
#include <cmath>
#define MAX_CARD 100

using namespace std;
ostream& operator <<(ostream& out, Vector v)
{
    int i;
    out << "{ ";
    for (i = 0; i < v.size; ++i){
            out << v[i] << " , " ;
    }
    out << "} ";
	return out;
}
Vector operator*(double d,Vector v){
    int i;
    Vector result;
    for (i = 0; i < v.size; ++i){
            result.vec[i]=v.vec[i] * d;
    }
    return result;
}
Vector::Vector()
{
    capacity=0;
    size=0;
    vec = new double[MAX_CARD];
	if (vec == NULL)
		cout << "Not enough memory for this set!" << endl;
	else
		capacity = MAX_CARD;
        vec[0]=0;
        vec[1]=1;
        size = 2;
}
Vector::Vector(double * arr, int num){
    vec = new double[MAX_CARD];
    int i;

    if (vec == NULL)
		cout << "Not enough memory!" << endl;
	else
	{
		size = num;

		for (i = 0; i < num; ++i)
			vec[i] = arr[i];
	}

}
Vector::Vector(const Vector& v)
{
    int i;
    vec = new double[v.capacity];

    if (vec == NULL)
		cout << "Not enough memory!" << endl;
	else
	{
		capacity = v.capacity;
		size = v.size;

		for (i = 0; i < v.size; ++i)
			vec[i] = v.vec[i];
	}
}
Vector::~Vector()
{
	delete[] vec;
}
int Vector::dimension()
{
    return size;
}
bool Vector::add_dimension(double v){
    int i;

	if (size == capacity)
	{
		int new_cap = capacity + MAX_CARD / 2;
		
        double *temp;
		temp = new double[new_cap];
		if (temp == NULL)
		{
			cout << "Not Enough Memory" << endl;
			return false;
		}

		for (i = 0; i < size; ++i)
			temp[i] = vec[i];

		delete [] vec;
		vec = temp;
		capacity = new_cap;
	}
	vec[size++] = v;
	return true;
}
bool Vector::remove_dimension(int index){
    int i;
    if(size>=index && index > 0){
        for (i = index; i < size; ++i)
			vec[i] = vec[i + 1];
		--size;
        return true;
    }
    return false;
}
bool Vector::insert_dimension(int index, double v){
    int i;
    int s = size;
    if(index == s++){
        add_dimension(v);
        size++;
        return true;
    }else if(size>index && index>0){
        vec[index]=v;
        size++;
        return true;
    }else { return false; }
}
double Vector::magnitude(){
    double result  =  0;
    int i;
    for (i = 0; i < size; ++i){
        result += pow(vec[i],2);
    }
    return sqrt(result);
}
double Vector::operator[](int index){

    double result;
    if(index>size){
        result =0;
    }else{
        result = vec[index];
    }
    return result;
}
bool Vector::operator==(Vector w){
    int i;
    bool found = true;
    if(w.dimension() != size){
        return false;
    }
    for (i = 0; i < size; ++i){
        if(vec[i]!=w[i]){
            found = false;
        }
    }
    return found;
}
bool Vector::operator!=(Vector w){
    bool result = (*this == w);
    return !result;
}
Vector& Vector::operator = (Vector v){
    
    vec = v.vec;
    size = v.size;
    capacity = v.capacity;
    
    return (*this);
}
Vector Vector::operator*(double scl){
    int i;
    Vector result;
    for (i = 0; i < size; ++i){
        result.insert_dimension(i,vec[i] * scl);
    }
    return result;
}
Vector Vector::operator*(Vector v){
    int i;
    Vector result;
   
    if (v.size > size){
       for (i = 0; i < v.size; ++i){
            if(i>size){
                result.insert_dimension(i,v.vec[i]);
            }else{
                result.insert_dimension(i,v.vec[i] * vec[i]);   
            }
        }
    }else if(size >v.size){
        for (i = 0; i < size; ++i){
            if(i>v.size){
                result.insert_dimension(i,vec[i]);
            }else{
                result.insert_dimension(i,v.vec[i] * vec[i]);
            }
        }
    }else{
        for (i = 0; i < size; ++i){
            result.insert_dimension(i,v.vec[i] * vec[i]);
        }
    }
    return result;
}
Vector Vector::operator+(Vector v){
    int i;
    Vector result;
   
    if (v.size > size){
       for (i = 0; i < v.size; ++i){
            if(i>size){
                result.insert_dimension(i,0-v.vec[i]);
            }else{
                result.insert_dimension(i,v.vec[i] + vec[i]);
            }
        }
    }else if(size >v.size){
        for (i = 0; i < size; ++i){
            if(i>v.size){
                result.insert_dimension(i,vec[i]);
            }else{
                result.insert_dimension(i,v.vec[i] + vec[i]);
            }
        }
    }else{
        for (i = 0; i < size; ++i){
            result.insert_dimension(i,v.vec[i] + vec[i]);
        }
    }
    return result;
}
Vector Vector::operator-(Vector v){
    int i;
    Vector result;
   
    if (v.size > size){
       for (i = 0; i < v.size; ++i){
            if(i>size){
                result.insert_dimension(i,0);
            }else{
                result.insert_dimension(i,vec[i] - v.vec[i]);
            }
        }
    }else if(size >v.size){
        for (i = 0; i < size; ++i){
            if(i>v.size){
                result.insert_dimension(i,0);
            }else{
                result.insert_dimension(i,vec[i] - v.vec[i]);
            }
        }
    }else{
        for (i = 0; i < size; ++i){
            result.insert_dimension(i,vec[i] - v.vec[i]);
        }
    }
    return result;
}
Vector Vector::operator +=(Vector f)
{
	(*this) = ((*this) + f);
	return (*this);
}
Vector Vector::operator -=(Vector f)
{
	(*this) = ((*this) - f);
	return (*this);
}

