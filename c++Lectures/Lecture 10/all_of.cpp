#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

bool is_prime(int &i)
{
  if(i==1) {
    return false;
  }
  int squareRoot = sqrt(i);
  for(int d = 2; d <= squareRoot; d++) {
    if(i%d == 0) {
      return false;
    }
  }
  return true;
}

int main()
{
  // vector<int> vi = { 2, 4, 7, 542, 211, 6 }; // OK in C++11
  int asArray[] = { 2, 4, 7, 542, 211, 6 };
  vector<int> vi(begin(asArray), end(asArray));

  if(!all_of(vi.begin(), vi.end(), is_prime)) {
    cout << "not ";
  }
  cout << "all of the numbers are prime\n";
  return 0;
}
