#include<vector>
#include<iterator>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;

int arr[] = { -11, 2, 3, -4, 0 };

int main()
{
  vector<int> v(std::begin(arr), std::end(arr));
  sort(v.begin(), v.end(), [](int x, int y) { return abs(x) < abs(y); });
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, ", "));
  return 0;
}