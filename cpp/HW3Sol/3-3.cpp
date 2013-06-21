//
//  3-3.cpp
//  Homework3
//
//  Created by Rukmaiah Bhupalam on 1/28/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct maxlenftn {
    maxlenftn() { maxlen = 0; }
    void operator()(string s) {
        maxlen = max(maxlen,s.size());
    }
    string::size_type maxlen;
};
int main() {
    const char *na[] = {
        "Spertus", "Lemon", "Golden", "Melhus"
    };
    vector<string> names(na, na + sizeof(na)/sizeof(const char *));
    maxlenftn maxf;
    for(int i=0; i<names.size(); i++)
        maxf(names[i]);
    cout << maxf.maxlen << endl;
    cout<<"This code did not work originally because when you put the maxf object in the for each loop it is not correctly calling the operator function for the functor and thus maxlen never gets updated"<<endl;
    return 0;
}