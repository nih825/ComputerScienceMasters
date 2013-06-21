#include<thread>
#include<atomic>
#include<vector>
#include<chrono>
#include<iostream>
#include<numeric>
#include<map>
#include<mutex>
using namespace std;

map<thread::id, int *> workCounts;
atomic<int> oldWork;
mutex mapMutex;
struct LocalWork {
  LocalWork() {
    lock_guard<mutex> guard(mapMutex);
    workCounts[this_thread::get_id()] = &count;
  }
  ~LocalWork() {
    lock_guard<mutex> guard(mapMutex);
    workCounts.erase(this_thread::get_id());
    oldWork += count;
  }
  int count;
};
void thrFunc() {
  LocalWork localWork;
  for(int i = 0; i < 1000000000; i++) {
    localWork.count++;
  }
}

int getWorkDone()
{
  lock_guard<mutex> guard(mapMutex);
  return accumulate
    (workCounts.begin(),
     workCounts.end(),
     oldWork.load(), 
     [](int acc, pair<thread::id, int *> kv) {
       return acc + *kv.second;
  });
}
int main()
{
  vector<thread> threads;
  for(int i = 0; i < 4; i++) {
    threads.push_back(thread(thrFunc));
  }
  this_thread::sleep_for(chrono::milliseconds(5));
  cout << getWorkDone() << " work units done" << endl;
  for(int i = 0; i < 4; i++) {
    threads[i].join();
  }
  return 0;
}
  