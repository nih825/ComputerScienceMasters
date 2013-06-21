
#include <boost/function_output_iterator.hpp>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &vec) {
    auto iter = make_function_output_iterator([](T i) {
        cout << i << ','; });
    copy(vec.begin(), vec.end(), iter);
    return os;
}

int main(void)
{
    vector<int> testing;
    for(int i=0; i<10; i++)
        testing.push_back(i);
    
    cout << testing << endl;
    
    return 0;
}