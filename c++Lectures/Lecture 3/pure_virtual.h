#include<iostream>
using std::cout;
using std::endl;

struct A {
  A();
  virtual void f() = 0;
  void g();
};

struct B : public A {
  void f() {
    cout << "B's f" << endl;
  }
};