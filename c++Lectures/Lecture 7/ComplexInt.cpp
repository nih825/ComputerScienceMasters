#include"ComplexInt.h"
using namespace cspp51044;

int main()
{
	typedef complex_int t_complex;
	
	t_complex c( 2, -3 );
	t_complex c2( 1, 1 );
	cout << "c " << c << endl;
	cout << "c2 " << c2 << endl;
	cout << "c*c2 " << c*c2 << endl;
	cout << "c+c2 " << c+c2 << endl;

	return 0;
}

