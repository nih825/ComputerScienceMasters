#include<vector>
#include<iostream>
#include<thread>
#include<map>
using namespace std;

enum class sampleEnum { black, yellow };

struct MyClass {
    MyClass(initializer_list<int> l){
        a.resize(l.size());
        for(int i:l)
            a.push_back(i);
    }
    MyClass( const MyClass& ) = delete;
    void printVec() const{
        for(int i=0; i<a.size(); i++)
            cout<<a[i]<<endl;
    }
    
    virtual void g() final{
        cout<<"Cannot be overriden"<<endl;
    }
    
    vector<int> a;
};

struct MyClass2 {
    MyClass2(int i1): i(i1) {}
   // MyClass2(MyClass2 const &a)
   // : MyClass2(a, a.mtx) {}

    int i;
    mutex mtx;

private:
    MyClass2(MyClass2 const &a, const lock_guard<mutex>& )
    : i(a.i) {
        lock_guard<mutex> l(a.mtx);
    }

};

struct MyClass3: public MyClass2 {
    using MyClass2::MyClass2;
    
};

template <class A, class B>
auto pow(A x, B y) -> decltype(x^y){
    
    return x^y;
    
}

template<typename T>
using NewMap = map<T, T>;


int main(void){
    
    vector<int> a={1, 2,3};
    for(int x : a){
        cout<<x<<endl;
    }
    vector<vector<int>> aa;
    NewMap<int> mapper;
    MyClass m{0,0,0,4,2,5,1};
    m.printVec();
    m.g();
    MyClass2 m2=MyClass2(5);
    cout<<m2.i<<endl;
    
    return 0;
}
