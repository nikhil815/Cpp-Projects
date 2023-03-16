#include <iostream>
#include <math.h>  
#include <string.h> // used only in operator >> and functions called by >> only
#include "BigInteger.h"

using namespace std;

ostream& operator<<(ostream& out, BigInteger v)
{
	int i =v.size;
    char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char result;
	out << "(";
    if(v.neg < 0){
        out << "-";
    }
	while(i>0)
	{
        i--;
        if(v.number[i]>9){
            result = alpha[v.number[i]-10];
            out << result;
        }else{
            //result = static_cast<char>(v.number[i]);
            out << v.number[i];
        }
		
	}
	out << ")";
	return out;
}
istream& operator>>(istream& in, BigInteger& v)
{
    char num[1000];
    int bas, i, j, min_base, temp;
    char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
    cout << "Enter the number: ";
    in >> num;

    cout << "Enter the base: ";
    in >> bas;

    if(bas<0 || bas>36){
         cout << "Error Base out of bounds. " << endl;
        return in;
    }

    //find minimum base based on what is in the char array
    min_base = 0;
    for(j=0; j < strlen(num); j++){
        for(i = 0; i<strlen(alpha); i++){
            if(num[j] == alpha[i]){
                temp = i + 1 + 10;
                if(temp>min_base){
                    min_base = i + 1 + 10;
                }
            }
        }  
    }

    if(min_base>bas){
        cout << "Error Base is too small for given char, using minimum possible base." << endl;
        bas = min_base;
    }

    int* num_arr;
    int cap;
    int len = strlen(num);
    
    char* negative = "-";
    char tem[1000];
    bool is_neg = (num[0]==negative[0]);

    if(is_neg){
        for(i=0; i< (len-1) ; i++){
            tem[i] = num[i+1];
        }
    }
  
    if(len>MAX_CARD){
        cap = len + MAX_CARD;
        num_arr = new int[cap];
    }else{
        cap = MAX_CARD;
        num_arr = new int[cap];
    }

    if(num_arr == NULL){
        cout << "Not enough memory for this operation." << endl;
    }else{
        if(is_neg){
            for(i=0; i<strlen(tem); i++){
                
                num_arr[(strlen(tem) - i  -1)]= v.char_to_int(tem[i]); 
            }
            
            v.dec = v.base_to_dec(num_arr, strlen(tem), bas);
            v.size = strlen(tem);
        }else{
            for(i=0; i<len; i++){
                num_arr[(len - i  -1)]= v.char_to_int(num[i]); 
            }
             v.dec = v.base_to_dec(num_arr, strlen(num), bas);
             v.size = strlen(tem);
        }
        
        if(is_neg){
            v.neg = -1;
        }else{
            v.neg = 1;
        }

        v.base = bas;
        v.capacity = cap;
        v.~BigInteger();
        v.number = num_arr;
    } 
    return in;
}
BigInteger::BigInteger(){
    number = new int[MAX_CARD];
    neg = 1;
    dec =0;
    size = 0;
	capacity = 0;
    base = 0;
    if (number == NULL)
		cout << "Not enough memory for this set!" << endl;
	else
		capacity = MAX_CARD;
        base = 10;
        number[0] = 0;
        size++;
}
BigInteger::BigInteger(const BigInteger& v)
{
	int i;
	base = dec = size = capacity = 0;
    neg = 1;
	number = new int[v.capacity];
	if (number == NULL)
		cout << "Not Enough Memory!" << endl;
	else
	{
		base = v.base;
		capacity = v.capacity;
        size = v.size;
        neg = v.neg;
        dec = v.dec;
		for (i = 0; i < v.size; ++i)
			number[i] = v.number[i];
	}
}
BigInteger::BigInteger(int n, int b){
    number = new int[MAX_CARD];
    size = 0;
	capacity = 0;
    base = 0;
    dec = n;
    if(n<0){
        neg = -1;
    }else {
        neg = 1;
    }
    int x = n * neg;
    if(b > 36 || b < 0){
        base = 0;
        cout << "base cannot be bigger than 36" << endl;
    }else{
       if (number == NULL)
            cout << "Not enough memory for this set!" << endl;
        else
            capacity = MAX_CARD;
            base = b;
            number = dec_to_base(n,b,neg);
            if(x==0){
                size = 1;
            }else{
                while(x>=1){
                    x = x/b;
                    size++;
                } 
            }
    }
}
BigInteger::~BigInteger(){
    delete[] number;
}
bool BigInteger::add_digit(int num){
    
    if(num>=base){
        return false;
    }

    int new_cap = capacity;
    if(size >= new_cap){
        new_cap = capacity + (MAX_CARD/2);
    }
    int* temp = new int[new_cap];

    int i,new_size;
    if (temp == NULL){
         cout << "Not enough memory for this BigInt!" << endl;
        return false;
    } else {
        if(size == 1 && number[0]==0){
            new_size = size;
        }else{
            new_size = size+1;
        }
        for(i = 0; i < new_size; ++i){
            if(i==0){
                temp[i] = num;
            }else{
                temp[i] = number[i-1];
            }
        }
        delete[] number;
        number = temp;
        size = new_size;
        capacity = new_cap;
        dec = base_to_dec();
    }
    return true;
    
}
void BigInteger::remove_digit(){
    
    if(size > 0){
        int* temp = new int[capacity];
        int i;
        if (temp == NULL){
            cout << "Not enough memory for this BigInt!" << endl;
        } else {
            if(size > 1){
                    for(i = 0; i < size; ++i){
                        if(i!=0){
                            temp[i-1] = number[i];
                        }
                    }
                    delete[] number;
                    number = temp;
                    size --;
                    dec = base_to_dec();
            }else{
                number[0]=0;
                size --;
                dec = 0;
            }
        }
    }

}
bool BigInteger::insert_digit(int num, int pos){
    
    if(pos >= size || pos < 0 || num>=base){
        return false;
    }
    
    int new_cap = capacity;
    if(size >= new_cap){
        new_cap = capacity + (MAX_CARD/2);
    }
    int* temp = new int[new_cap];

    int i,new_size;
    if (temp == NULL){
         cout << "Not enough memory for this BigInt!" << endl;
        return false;
    } else {
        if(size == 1 && number[0]==0){
            new_size = size;
        }else{
            new_size = size+1;
        }
        for(i = 0; i < new_size; ++i){
            
            if(i == pos){
                temp[i] = num;
            }else{
                if(i<pos){
                    temp[i] = number[i];
                }else{
                    temp[i] = number[i-1];
                }
            }
        }
        delete[] number;
        number = temp;
        size = new_size;
        capacity = new_cap;
        dec = base_to_dec();
    }
    return true;
}
int& BigInteger::operator[](int ind){   
	return number[ind];
}
bool BigInteger::operator==(BigInteger v) const{
    //assuming numbers of different bases are not equal even if they have the same decimal value  
	
    if(v.size != size || v.base != base || v.neg != neg){
         return false;
    }
    return (dec == v.dec);
}
bool BigInteger::operator!=(BigInteger v) {
    return !((*this) == v);
}
bool BigInteger::operator>(BigInteger v){   
	//assuming we can compare numbers of different bases
    return (dec > v.dec);
}
bool BigInteger::operator<(BigInteger v){   
	//assuming we can compare numbers of different bases
    return (dec < v.dec);
}
bool BigInteger::operator>=(BigInteger v){   
	//assuming we can compare numbers of different bases
    return (dec >= v.dec);
}
bool BigInteger::operator<=(BigInteger v){   
	//assuming we can compare numbers of different bases
    return (dec <= v.dec);
}
BigInteger BigInteger::operator++(){
    int inc = (dec + 1);
    int* temp = dec_to_base(inc, base, neg);

    int x = inc;
    int new_size = 0;
    while(x>=1){
        x = x/base;
        new_size++;
    }

    int new_neg;
    if(inc < 0){
        new_neg = -1;
    }else{
        new_neg = 1;
    }
    delete[] number;
    number = temp;
    size = new_size;
    neg = new_neg;
    dec = inc;

    return (*this);
}
BigInteger BigInteger::operator--(){
    int inc = (dec - 1);
    int* temp = dec_to_base(inc, base, neg);
    
    int x = inc;
    int new_size = 0;
    while(x>=1){
        x = x/base;
        new_size++;
    }

    int new_neg;
    if(inc < 0){
        new_neg = -1;
    }else{
        new_neg = 1;
    }
    delete[] number;
    number = temp;
    size = new_size;
    neg = new_neg;
    dec = inc;

    return (*this);
}
BigInteger BigInteger::operator++(int){
    int inc = (dec + 1);
    int* temp = dec_to_base(inc, base, neg);
    
    int x;
    if(inc<0){
        x=inc*-1;
    } else{
        x=inc;
    }
    int new_size = 0;
    while(x>=1){
        x = x/base;
        new_size++;
    }

    int new_neg;
    if(inc < 0){
        new_neg = -1;
    }else{
        new_neg = 1;
    }
    delete[] number;
    number = temp;
    size = new_size;
    neg = new_neg;
    dec = inc;

    return (*this);
}
BigInteger BigInteger::operator--(int){
    int inc = (dec - 1);
    int* temp = dec_to_base(inc, base, neg);
    int x;
    if(inc<0){
        x=inc*-1;
    } else{
        x=inc;
    }
    int new_size = 0;
    while(x>=1){
        x = x/base;
        new_size++;
    }

    int new_neg;
    if(inc < 0){
        new_neg = -1;
    }else{
        new_neg = 1;
    }
    delete[] number;
    number = temp;
    size = new_size;
    neg = new_neg;
    dec = inc;

    return (*this);
}
BigInteger& BigInteger::operator=(BigInteger v){
    int i;
	base = dec = size = capacity = 0;
    neg = 1;
	number = new int[v.capacity];
	if (number == NULL)
		cout << "Not Enough Memory!" << endl;
	else
	{
		base = v.base;
		capacity = v.capacity;
        size = v.size;
        neg = v.neg;
        dec = v.dec;
		for (i = 0; i < v.size; ++i)
			number[i] = v.number[i];
	}
    return(*this);
}
BigInteger BigInteger::operator+(BigInteger v){
    int dec_res = dec + v.dec;
    
    BigInteger result = BigInteger(dec_res, base);
    
    return result;
}
BigInteger BigInteger::operator-(BigInteger v){
    int dec_res = dec - v.dec;

    BigInteger result = BigInteger(dec_res, base);
    return result;
}
BigInteger BigInteger::operator*(BigInteger v){
    int dec_res = dec * v.dec;

    BigInteger result = BigInteger(dec_res, base);
    return result;
}
BigInteger BigInteger::operator/(BigInteger v){
    int dec_res = dec / v.dec;

    BigInteger result = BigInteger(dec_res, base);
    return result;
}
BigInteger BigInteger::operator%(BigInteger v){
    int dec_res = dec % v.dec;
    BigInteger result = BigInteger(dec_res, base);
    return result;
}
int BigInteger::num_digits(){
    return size;
}
int* BigInteger::dec_to_base(int num,int b, int sign){
    int div;
    if(num < 0){
        div= num * -1;
    }else{
        div= num ; //result of division
    }
   
    int i = 0;
    int rem; //remainder
    int* result= new int[MAX_CARD];
    if(b > 36 || b < 0){
        cout << "base cannot be bigger than 36" << endl;
        return result;
    }

    while(div>=1){
        rem = div%b;
        div = div/b;

        if(!(i==0 && rem==0)){
            result[i]=rem;
        }
        i++;
    }
    return result;
}
int BigInteger::base_to_dec(int* v, int s, int b){
    int i;
    int result = 0;
    for (i = 0; i < s; ++i){
        result += v[i] * pow(b,i);
    }
    return result;

}
int BigInteger::base_to_dec(BigInteger v){
    int i;
    int result = 0;
    for (i = 0; i < v.size; ++i){
        result += v[i] * pow(v.base,i);
    }
    return result;

}
int BigInteger::base_to_dec(){
    int i;
    int result = 0;
    for (i = 0; i < size; ++i){
        result += number[i] * pow(base,i);
    }
    result *= neg;
    return result;

}
char BigInteger::int_to_base(int num){
    if(num>9){
        return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[num-10];
    }
    char ch = static_cast<char>(num);
    return ch;
    
}
int BigInteger::get_dec(){
    return dec;
}
int BigInteger::char_to_base(char c){
    char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    int result = -1;
    for(i = 0; i<strlen(alpha); i++){
        if(c == alpha[i]){
            result = i + 1 + 10;
        }
    }
    return result;
}
int BigInteger::char_to_int(char c){
    char* alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    for(i=0;i<strlen(alpha); i++){
        if(alpha[i]==c){
            return i;
        }
    }
    return -1;
}