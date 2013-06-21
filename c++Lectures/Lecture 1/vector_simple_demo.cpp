#include<vector>
#include<iostream>
using namespace std;
int main()
{  
  vector<int> v; // a vector of ints
  v.push_back(1);
  v.push_back(2);
  for(auto it = v.begin(); it != v.end(); it++) {
    cout << *it << ", ";
  } // Prints "1, 2,"
  return 0;
}
