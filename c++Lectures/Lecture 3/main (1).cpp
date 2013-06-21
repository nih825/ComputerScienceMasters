#include "pure_virtual.h"

A::A()
{
  g();
}

int main()
{
	// A *a = new A(); !!!Illegal, f is not defined
	A *a = new B();
	return 0;
}
