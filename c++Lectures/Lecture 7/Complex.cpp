#include"Complex.h"
using namespace cspp51044;

int main()
{
	{
	typedef complex<int> t_complex;
	t_complex c( 2, -3 );
	t_complex c2( 1, 1 );
	cout << "c " << c << endl;
	cout << "c2 " << c2 << endl;
	cout << "c*c2 " << c*c2 << endl;
	cout << "c+c2 " << c+c2 << endl;
	// 
	}
	{
	typedef complex<double> t_complex;
	t_complex c( 2.5, -3 );
	t_complex c2( 1.2, 1 );
	cout << "c " << c << endl;
	cout << "c2 " << c2 << endl;
	cout << "c*c2 " << c*c2 << endl;
	cout << "c+c2 " << c+c2 << endl;
	}
	return 0;
}

