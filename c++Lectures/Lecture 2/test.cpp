#include"optimized_copy.h"
#include<vector>
#include<set>
#include<iterator>
#include<iostream>

using namespace std;

int main()
{
  set<int> si;
  si.insert(1);
  si.insert(2);
  si.insert(3);
  si.insert(4);
  si.insert(5);
  vector<int> vi;
  optimized_copy(si.begin(), si.end(), back_inserter(vi));

  for(auto it = vi.begin(); it != vi.end(); it++) {
    cout << *it << endl;
  }
  return 0;
}
  
