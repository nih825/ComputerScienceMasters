//
//  4-4.cpp
//  HW4
//
//  Created by Rukmaiah Bhupalam on 2/1/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//


#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <mutex>
using namespace std;


mutex themutex;

void counter(){
    lock_guard<std::mutex> guard(themutex);
    for(int i=0; i < 100; i++){
        thread::id threadid = this_thread::get_id();
        cout << "Thread id " << threadid << " has counted to " << i+1 <<  endl;
    }
}

int main(void){
    
    thread t1(counter);
    thread t2(counter);
    thread t3(counter);
    t1.join();
    t2.join();
    t3.join();
    
    return 0;
}