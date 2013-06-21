
#include<iostream>
#include<vector>
using namespace std;


int main(void){
    vector<int> v={2, 4, 7, 542, 211, 6};
    if(std::all_of(v.begin(),v.end(),[](int number){ for(int i=2; i<number; i++){ if(number%i==0)return false;} return true;}))
       cout<<"All prime"<<endl;
    else
       cout<<"Not all prime"<<endl;
    
    return 0;
}