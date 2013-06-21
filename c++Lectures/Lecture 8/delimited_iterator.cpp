#include "delimited_iterator.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using namespace cspp51044;

int
main()
{
    // No initializer lists in VS2010
    int fib_arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21 };
    vector<int> fib(fib_arr, fib_arr + sizeof(fib_arr)/sizeof(int));
    cout << "(";
    copy(fib.begin(), fib.end(), my_ostream_iterator<int>(cout, ", "));
    cout << ")" << endl << endl;

    wcout << L"Now with wide characters:" << endl << L"  (";
    copy(fib.begin(), fib.end(), delimited_iterator<int, wchar_t>(wcout, L", "));
    wcout << L")" << endl;
    return 0;
}