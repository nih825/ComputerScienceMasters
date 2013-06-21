//
//  6-1.cpp
//  Homework6
//
//  Created by Rukmaiah Bhupalam on 2/17/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#include <iostream>
using namespace std;

template<class T>
struct Complex {
public:
    T r;
    T i;
    Complex(T a, T b){
        r=a;
        i=b;
        
    }
    Complex operator+(Complex &obj1) const;
    Complex operator*(Complex &obj1) const;
    inline friend ostream& operator<<(ostream &ref, Complex &obj1){
        ref<<obj1.r<<"+"<<obj1.i<<"i";
        return ref;
    }
};

template <class T>
Complex<T> Complex<T>::operator+(Complex &obj1) const{
    Complex additive= Complex(r+obj1.r,i+obj1.i);
    return additive;
}

template <class T>
Complex<T> Complex<T>::operator*(Complex &obj1) const{
    T r1=obj1.r;
    T i1=obj1.i;
    T rComp=r*r1+i*i1*-1;
    T iComp=i*r1+i1*r;
    Complex multiplied= Complex(rComp,iComp);
    return multiplied;
}


int main(void){
    Complex<double> first = Complex<double>(3.2,2.1);
    Complex<double> second=Complex<double>(2.1,5.9);
    Complex<double> add=first+second;
    Complex<double> multiply=first*second;
    cout<<add<<endl;
    cout<<multiply<<endl;
    return 0;
}
