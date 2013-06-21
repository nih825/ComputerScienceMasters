#include"md5.h"
#include<string>
#include<iostream>
#include<limits>
#include<sstream>
#include<iomanip>
#include<unordered_map>

using namespace std;
class Md5Hasher {
public:
  size_t operator()(string str) {
    size_t val;
    istringstream digest(md5(str).substr(0, numeric_limits<size_t>::digits/4));
    digest >> hex;
    digest >> val;
    return val;
  }
};

int main()
{
  unordered_map<string, int, Md5Hasher> md5map;
  md5map["foo"] = 1729;
  return 0;
}