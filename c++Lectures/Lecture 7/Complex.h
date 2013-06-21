#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>
#include <complex>
using std::ostream;
using std::cout;
using std::endl;

namespace cspp51044 {
template <class T>
class complex {
  // representation
	T mR;
	T mI;
  // structors
  public:
	complex( T r, T i ) : mR(r), mI(i) {}
  // operators
  public:
	complex& operator+=( const complex& c ) {
		this->mR += c.mR;
		this->mI += c.mI;
		return *this; }
	complex& operator*=( const complex& other ) {
		// http://www.clarku.edu/~djoyce/complex/mult.html
		// (x + yi)(u + vi) = (xu - yv) + (xv + yu)i
		// =
		// xu + xv(i) + yu(i) + yv(i)(i)
		// =
		// xu - yv + i(xv + yu)
		T iTemp = this->mR * other.mR - this->mI * other.mI;
		this->mI = this->mR * other.mI + this->mI * other.mR;
		this->mR = iTemp;
		return *this; }
	inline friend complex operator+( const complex& a, const complex& b ) {
		complex result = a;
		return result += b;
	}
	inline friend complex operator*( const complex& a, const complex& b ) {
		complex result = a;
		return result *= b;
	}
	inline friend ostream& operator<<( ostream& os, const complex& c ) {
		os << "(" << c.mR << (c.mI<0?"-":"+");
		if ( c.mI != 1 && c.mI != -1 ) // nicer output is 5-i not 5-1i (or 5+i)
			cout << (c.mI>0?c.mI:-c.mI); //cout << abs(c.mI);
		cout << "i)";
		return os;
	}

};
}
#endif

Animal * a = new Gorilla;
delete a;
