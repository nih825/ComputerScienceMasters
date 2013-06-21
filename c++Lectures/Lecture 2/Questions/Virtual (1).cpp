#include <iostream>
#include <math.h>
#include <boost/progress.hpp>
using namespace std;
class A {
public: // 15.83s if virtual 15.82 if not virtual
   int f(double d, int i) {
       return static_cast<int>(d*log(d))*i;
   }
};
int main()
{
   boost::progress_timer t;
   A *a = new A();
   int ai = 0;
   for(int i = 0; i < 100000000; i++) {
           ai += a->f(10, i);
   }
   cout << ai << endl;
}
