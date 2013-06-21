#include <iostream>
#include <fstream>
#include "BasicIndentStream.h"

using namespace std;
using namespace cspp51044;

int main()
{
	indent_wostream ins(wcout);
	ins << L"int" << endl;
	ins << L"fib(int n) { " << indent << endl;
	ins << L"if (n == 0) " << indent << endl;
	ins << L"return 0;" << unindent << endl;
	ins << L"if (n == 1) " << indent << endl;
	ins << L"return 1;" << unindent << endl;
	ins << L"return fib(n-2) + fib(n-1);" << unindent << endl;
	ins << L"}" << endl;
	return 0;
}