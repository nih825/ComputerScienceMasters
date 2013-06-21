#include<thread>
#include<atomic>
#include<vector>
#include<chrono>
#include<iostream>
using namespace std;
atomic<int> workCount;

void thrFunc() {
  for(int i = 0; i < 10000000; i++) {
    workCount++;
  }
}

int main()
{
  vector<thread> threads;
  for(int i = 0; i < 4; i++) {
    threads.push_back(thread(thrFunc));
  }
  this_thread::sleep_for(chrono::milliseconds(50));
  cout << workCount.load() << " work units done" << endl;
  for(int i = 0; i < 4; i++) {
    threads[i].join();
  }
  return 0;
}
  