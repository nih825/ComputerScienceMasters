

#include<iostream>
#include<vector>
#include <forward_list>
#include <string>
#include <unordered_map>

using namespace std;

int main(void){
    vector<int> v={2, 4, 7, 542, 211, 6};
    //all_of
    if(std::all_of(v.begin(),v.end(),[](int number){ for(int i=2; i<number; i++){ if(number%i==0)return false;} return true;}))
        cout<<"All prime"<<endl;
    else
        cout<<"Not all prime"<<endl;
    
    //any_of
    if(std::any_of(v.begin(),v.end(),[](int number){ for(int i=2; i<number; i++){ if(number%i==0)return false;} return true;}))
        cout<<"At least one prime"<<endl;
    else
        cout<<"No primes"<<endl;
    
    
    //none_of
    if(std::none_of(v.begin(),v.end(),[](int number){ for(int i=2; i<number; i++){ if(number%i==0)return false;} return true;}))
        cout<<"No Primes"<<endl;
    else
        cout<<"At least one prime"<<endl;
    
    //copy_n
    copy_n
    (v.begin(), 5,
     ostream_iterator<int>
     (cout, "\n"));
    
    //find_if_not
    cout << *find_if_not
    (v.begin(),
     v.end(),
     [](int i) {
         return i%2 == 1;
     });
    
    //partition_copy
    vector<int> primes;
    vector<int> composites;
    
    partition_copy
    (v.begin(),
     v.end(),
     back_inserter(primes),
     back_inserter(composites),
     [](int number){ for(int i=2; i<number; i++){ if(number%i==0)return false;} return true;});
    cout<<endl<<"primes"<<endl;
    for(int i=0; i<primes.size(); i++)
        cout<<primes[i]<<endl;
    
    //minmax element
    typedef vector<int>::const_iterator iterator;
    std::pair<iterator,iterator> p=std::minmax_element(v.begin(),v.end());
    cout << "The smallest element is " << *(p.first) << endl;
    cout << "The largest element is  " << *(p.second) << endl;
    
    //minmax
    tuple<int const&, int const&> p1 = std::minmax(500, -100);
   
    //forward list
    std::forward_list<int> list1;
    list1.push_front(1);
    list1.push_front(2);
    list1.push_front(3);
    
    //unordered_map
    std::unordered_map<std::string,int> mymap = {
        {"lion",3},
        {"zebra",10}};

    
    return 0;
    
    
}