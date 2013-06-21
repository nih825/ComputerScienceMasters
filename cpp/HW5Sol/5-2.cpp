//
//  5-2.cpp
//  HW5
//
//  Created by Rukmaiah Bhupalam on 2/8/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#include<vector>
#include<iostream>
using namespace std;
mutex themutex;


struct Stack {
    Stack();
    int Pop();
    void Push(int val);
private:
    vector<int> stack_vec;
    unsigned count;
};

Stack::Stack(){
    lock_guard<std::mutex> guard(themutex);
    count=0;
}

int Stack::Pop(){
    lock_guard<std::mutex> guard(themutex);
    if(count==0)
        return -1;
    else {
        int val=stack_vec.back();
        stack_vec.pop_back();
        count--;
        return val;
    }
}

void Stack::Push(int val){
    lock_guard<std::mutex> guard(themutex);
    stack_vec.push_back(val);
    count++;
}

int main(void){
    Stack * stack = new Stack();
    cout<<stack->Pop()<<endl;
    stack->Push(5);
    stack->Push(6);
    stack->Push(-11);
    cout<<stack->Pop()<<endl;
    cout<<stack->Pop()<<endl;
    cout<<stack->Pop()<<endl;
    return 0;
}


