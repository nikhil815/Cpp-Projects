#pragma once

#include <iostream>

using namespace std;

class Vector{
    private:
        double* vec;
        int size;
        int capacity;
    
    public:
        Vector();
        Vector (double *, int);
        Vector(const Vector&);
        ~Vector();
        int dimension();
        bool add_dimension(double);
        bool remove_dimension(int);
        bool insert_dimension(int,double);
        double magnitude();
        double operator [](int);
        bool operator ==(Vector);
        bool operator !=(Vector);
        Vector& operator =(Vector);
        Vector operator *(double);
        Vector operator *(Vector);
        Vector operator +(Vector);
        Vector operator -(Vector);
        Vector operator +=(Vector);
        Vector operator -=(Vector);
        friend ostream& operator <<(ostream&,Vector);
        friend Vector operator *(double,Vector);
};