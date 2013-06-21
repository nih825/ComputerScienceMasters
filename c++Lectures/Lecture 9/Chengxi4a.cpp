#include <iostream>
#include <thread>

using namespace std;

// this is the version without making variable i and pointer control into volatile

void f1 (int *control)
{
	while(!*control){}
}

void f2 (int *control)
{
	*control = 1;
}

int main ()
{
	int i = 0;
	int *control = &i;
	thread t1(f1,control);
	thread t2(f2,control);

	t1.join();
	t2.join();
	cout<<"program exits"<<endl;

	return 0;
}
