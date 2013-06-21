#include <iostream>
#include <thread>

using namespace std;

// with 'volatile' variable, the program gets to exit

void f1 (volatile int *control)
{
	while(!*control){}
}

void f2 (volatile int *control)
{
	*control = 1;
}

int main ()
{
	volatile int i = 0;
	volatile int *control = &i;
	thread t1(f1,control);
	thread t2(f2,control);

	t1.join();
	t2.join();
	cout<<"program exits"<<endl;

	return 0;
}
