#include<algorithm>
#include<iostream>
#include<iterator>
#include<forward_list>
#include<vector>
#include<cmath>
#include<random>
#include<tuple>
#include<chrono>
using namespace std;

bool is_prime(int &i) {
  int squareRoot = sqrt(i);
  for(int d = 2; d <= squareRoot; d++) {
    if(i%d == 0) {
      return false;
    }
  }
  return true;
}

int main()
{
  chrono::time_point<chrono::high_resolution_clock> start(chrono::high_resolution_clock::now());
  int asArray[] = { 2, 4, 7, 542, 211, 6 };
  vector<int> vi(begin(asArray), end(asArray));

  if(all_of(vi.begin(), vi.end(), is_prime)) {
    cout << "All of the numbers are prime" << endl;
  }

  if(any_of(vi.begin(), vi.end(), is_prime)) {
    cout << "Some of the numbers are prime" << endl;
  }

  if(none_of(vi.begin(), vi.end(), is_prime)) {
    cout << "None of the numbers are prime" << endl;
  }

  cout << "The first three numbers are\n\t";
  copy_n(vi.begin(), 3, ostream_iterator<int>(cout, "\n\t"));
  cout << endl;

  auto non_prime(find_if_not(vi.begin(), vi.end(), is_prime));
  if(non_prime != vi.end()) {
    cout << "First non-prime is " << *non_prime 
         << " at offset " << non_prime - vi.begin() << endl;
  }
  vector<int> primes;
  vector<int> composites;
  partition_copy(vi.begin(), vi.end(), back_inserter(primes), 
                 back_inserter(composites), is_prime);

  cout << "Primes are\n\t";
  copy(primes.begin(), primes.end(), ostream_iterator<int>(cout, "\n\t"));
  cout << endl;

  cout << "Composites are\n\t";
  copy(composites.begin(), composites.end(), ostream_iterator<int>(cout, "\n\t"));
  cout << endl;

  auto minmax_ex = minmax(12, 5);
  cout << "The smaller of 12 and 5 is " << minmax_ex.first 
       << ". The larger is " << minmax_ex.second << endl;

  auto minmax_element_ex = minmax_element(vi.begin(), vi.end());
  cout << "The smallest in our list is " << *minmax_element_ex.first 
       << ". The largest is " << *minmax_element_ex.second << endl;

  forward_list<int> fli(vi.begin(), vi.end());
  cout << "The same numbers as in our vector stored in a forward list\n\t";
  copy(fli.begin(), fli.end(), ostream_iterator<int>(cout, "\n\t"));
  cout << endl;

  default_random_engine generator;
  normal_distribution<double> distribution;
  vector<double> random_vector(11);

  generate(random_vector.begin(), 
           random_vector.end(),
           [&]()->double { return distribution(generator); });

  cout << "Some normally distributed random numbers\n\t";
  copy(random_vector.begin(), random_vector.end(),
       ostream_iterator<double>(cout, "\n\t"));
  auto tidf = make_tuple(3, .14, 15.9f);

  int i;
  double d;
  float f;
  tie(i, d, f) = tidf;
  cout << "i = " << i << endl;
  cout << "d = " << d << endl;
  cout << "f = " << f << endl;
  cout << endl;

  auto finish(chrono::high_resolution_clock::now());
  cout << "Elapsed time is " 
       << chrono::duration_cast<chrono::microseconds>(finish-start).count()
       << " microseconds" << endl;
  return 0;
}
