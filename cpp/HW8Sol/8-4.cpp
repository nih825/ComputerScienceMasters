using namespace std;
#include <time.h>
#include<iostream>


struct MyClassVolatile {
    MyClassVolatile(double var) {
        i=var;
        j=var;
    }
    
    void incrementI(){
        i++;
        
    }
    void incrementJ(){
        j++;
    }
    
    volatile double i;
    double j;
};

//Make sure to compile with optimization flags on
int main(void){
    
    int iters=1000000000;
    MyClassVolatile m= MyClassVolatile(1);
    clock_t t0;
    t0=clock();
    for(int i=0; i<iters; i++)
        m.incrementI();
    cout<<"The nonvolatile incrementation took: "<<(double)(clock()-t0)/CLOCKS_PER_SEC<<endl;
    
    MyClassVolatile m1= MyClassVolatile(1);
    clock_t t1;
    t1=clock();
    for(int i=0; i<iters; i++){
        m1.incrementJ();
    }
    cout<<"The volatile iteration took: "<<(double)(clock()-t1)/CLOCKS_PER_SEC<<endl;
    return 0;
    
}