#pragma once
#include <iostream>

#define MAX_CARD 100

using namespace std;

class BigInteger{
    private:
		int* number; //Numbers are stored backwards in the array; the least significant digit is at position 0 in the array
		int dec; //base 10 representation of the Big Integer
		int neg; //integer showing whether the Big Int is negattive, can be 1 or -1
		int base; //the base of the Big Int
		int size; //size of the number array
		int capacity; //capacity of the number array

    public:
		//constructors
		BigInteger(); //default contsructor
		BigInteger(int, int);//int num, int base
		BigInteger(const BigInteger&);
		~BigInteger();

		//functions
		int num_digits();
		bool add_digit(int);
		void remove_digit();
		bool insert_digit(int, int);//int digit, int position

		//operators
		friend ostream& operator<<(ostream&, BigInteger);
		friend istream& operator>>(istream&, BigInteger&);

		int& operator[](int);
		bool operator==(BigInteger) const;
		bool operator!=(BigInteger);
		bool operator>(BigInteger);
		bool operator<(BigInteger);
		bool operator>=(BigInteger);
		bool operator<=(BigInteger);
		
		BigInteger& operator=(BigInteger);
		BigInteger operator++();
		BigInteger operator--();
		BigInteger operator++(int);
		BigInteger operator--(int);
		BigInteger operator+(BigInteger);
		BigInteger operator-(BigInteger);
		BigInteger operator*(BigInteger);
		BigInteger operator/(BigInteger);
		BigInteger operator%(BigInteger);

		//helper functions
		int* dec_to_base(int,int,int); //converts a decimal number to an array of the given base
		int base_to_dec(int*,int,int); //converts a Big Integer to base 10
		int base_to_dec(BigInteger); //converts a Big Integer to base 10
		int base_to_dec(); //converts a Big Integer to base 10
		int get_dec(); //returns the base 10 representation of the BigInt
		char int_to_base(int); //converts an integer to a BigInt as a char
		int char_to_base(char); //returns the minimum possible base given a BigInt as a char
		int char_to_int(char); //returns the integer value of one BigInt char
};