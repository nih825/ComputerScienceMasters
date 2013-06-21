#include<iostream>
#include<vector>
using namespace std;

struct MyClass {
    
    MyClass(): data_count(0){}
    
    MyClass(const MyClass& m): data_count(0){
        m.data_count++;
        
    }
  
    mutable int data_count;
};

struct MyClass2 {
    
    MyClass2(): data_count(0){}
    
    MyClass2(const MyClass2& m){
        MyClass2& m2=const_cast<MyClass2&>(m);
        m2.data_count++;
        
    }
    
    int data_count;
    
};

int main(void){
    
    MyClass m = MyClass();
    vector<MyClass> dataObjects;
    dataObjects.resize(100);
    for(int i=0; i<100; i++){
        dataObjects[i]=MyClass(m);
    }
    cout<<m.data_count<<endl<<endl;
    
    MyClass2 m2 = MyClass2();
    vector<MyClass2> dataObjects2;
    dataObjects2.resize(100);
    for(int i=0; i<100; i++){
        dataObjects2[i]=MyClass2(m2);
    }
    cout<<m2.data_count<<endl<<endl;
    
    cout<<"I like the mutable version of this code better as I find it to be more elegant"<<endl;
    
    return 0;
}