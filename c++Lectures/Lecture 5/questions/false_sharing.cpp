#include <thread>
#include <mutex>
#include <boost/progress.hpp>
#include <algorithm>
#include <memory>
using namespace std;
// Note: This file uses Windows threads in place of C++11 threads

const int MAX_THREADS = 8;
const int paddedMutexSize = 512;

// We would like to use a union to specify the size of
// a padded mutex, but Visual C++ doesn't yet (VC10)
// implement 9.5p2 of the C++11 standard, so we will 
// first create another class to find out the offset of
// the field after the mutex member
struct FakePaddedMutex {
	mutex lck;
	char pad[paddedMutexSize - sizeof(mutex)]; // Not quite right. We don't know the offset yet
};

// Now, here's the real padded mutex. The code below is still
// slightly non-portable, but as noted above, with C++11 support,
// we could have just used a union and avoided the problem completely.
struct PaddedMutex {
   mutex lck;
   char pad[paddedMutexSize - offsetof(FakePaddedMutex, pad)];
};

// Global variable
PaddedMutex mutexes[MAX_THREADS];

// Sample custom data structure for threads to use.
struct MyData {
    MyData(int i) : val1(i), val2(i) {}
    long val1;
    int val2;
};

const long loopCount = 10000000;

void myThreadFunction(MyData *myData)
{
   int index = myData->val2 * 3 % MAX_THREADS;
   int x = 0;
   for(int i = 0; i < loopCount; i++) {
	   lock_guard<mutex> l(mutexes[index].lck);
	   myData->val1 += i;
  }
}

int main()
{
	// Using an array instead of a vector because we are 
	// investigating effects of precise memory layout
   unique_ptr<MyData> dataArray[MAX_THREADS];
   vector<thread> threads;
   boost::progress_timer t;

   for( int i=0; i<MAX_THREADS; i++ )
   {
       // Allocate memory for thread data.
       // Generate unique data for each thread to work with.
       dataArray[i] = unique_ptr<MyData>(new MyData(i));
	   threads.push_back(thread(myThreadFunction, dataArray[i].get()));
   } // End of main thread creation loop.

   // Wait until all threads have terminated.
   for(auto it = threads.begin(); it != threads.end(); it++) {
	   it->join();
   }

   return 0;
}

