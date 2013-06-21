#include<vector>
#include<iostream>
#include<string>

using namespace std;

int arr[] = { 1, 2, 4, 8 };
vector<int> v(arr, arr + sizeof(arr)/sizeof(int));
vector<int> vi1 = { 1, 2};
decltype(vi1) vi2 = { 3, 4};
vector<vector<int>> vvi = {vi1, vi2};

struct A {
  A(int _i) : i(_i) {};
  A(int _i, int _j) : i(_i), j(_j) {}
  A(string _s) : A(_s.size()) {}
  A(A const &) = delete;
  int i;
  int j = 5;
};

enum class Suits : unsigned int;


template<typename T, typename U>
struct B : public A {
  using A::A;
  int k = 7;
  T t;
  U u;
  Suits s;
};

template<typename T>
using BD = B<T, T>;

enum class Suits : unsigned int {
  Clubs, Diamonds, Hearts, Spades
};

int main()
{
  for(auto it = vvi.begin(); it != vvi.end(); it++) {
    cout << (*it)[0] << endl;
  }
  int product = 1;
  for(int i : vi1) {
    product *= i;
  }
  B<int, int> bi1(5);
  BD<int> bi2(5);
}