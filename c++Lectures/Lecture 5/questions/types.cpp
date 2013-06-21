#include <iostream>
using namespace std;
struct A {
	int ifip(int *) { return 5; }
	int fm(double(*ffd)(float &)) { float f=2; return ffd(f); }
	int i;
	int j;
};
char *fcp(char *, char *) { return "foo"; }
void (fvv) (void (*)() ) {};

int ifv() { return 42; }
int main()
{
	double d = 1.5;
	A *ap = new A;
	A a;
	char const *ccp = "hello";
	char const &ccr(*ccp);
	long ls[7];
	int *ip = new int(5);
	int **ipp = &ip;
	int *&ipr=ip;
	float f = 1.2f;
	float &fr(f);
	int (*ifvp)() = &ifv;
	int (*&ifvpr)() = ifvp;
	char *(*fcpp)(char *, char *) = fcp;
	int A::*aip = &A::i;
	int (A::*afp)(int *) = A::ifip;
	int (A::**afpp)(int *) = &afp;
	int (A::*&afpr)(int *) = afp;
	int (A::*pfm)(double (*)(float &)) = &A::fm;
	void (*p[10]) (void (*)() ) = {
		fvv, fvv, fvv, fvv, fvv,
		fvv, fvv, fvv, fvv, fvv
	};
	cout << ccp << endl;
	return 0;
}
