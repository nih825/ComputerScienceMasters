#ifndef COMPLEX_INT_H
#define COMPLEX_INT_H

#include <iostream>
#include <cmath>
using std::ostream;
using std::cout;
using std::endl;

namespace cspp51044 {
class complex_int {
  // representation
	int mR;
	int mI;
  // Constructors
  public:
	complex_int( int r, int i = 0) : mR(r), mI(i) {}
  // operators
  public:
	complex_int& operator+=( complex_int c ) {
		mR += c.mR;
		mI += c.mI;
		return *this; 
    }
	complex_int& operator*=( complex_int other ) {
		// http://www.clarku.edu/~djoyce/complex/mult.html
		// (x + yi)(u + vi) = (xu - yv) + (xv + yu)i
		// =
		// xu + xv(i) + yu(i) + yv(i)(i)
		// =
		// xu - yv + i(xv + yu)
		int iTemp = this->mR * other.mR - this->mI * other.mI;
		this->mI = this->mR * other.mI + this->mI * other.mR;
		this->mR = iTemp;
		return *this; 
    }
	inline friend complex_int operator+( const complex_int& a, const complex_int& b ) {
		complex_int result = a;
		return result += b;
	}
	inline friend complex_int operator*( const complex_int& a, const complex_int& b ) {
		complex_int result = a;
		return result *= b;
	}
	inline friend ostream& operator<<( ostream& os, const complex_int& c ) {
		os << c.mR << (c.mI<0?"-":"+");
		if ( c.mI != 1 && c.mI != -1 ) // nicer output is 5-i not 5-1i (or 5+i)
			cout << (c.mI>0?c.mI:-c.mI); //cout << abs(c.mI);
		cout << "i";
		return os;
	}

};
}
#endif