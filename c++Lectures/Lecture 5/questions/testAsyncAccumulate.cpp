#include "asyncAccumulate.h"
#include <boost/iterator/counting_iterator.hpp>
using namespace cspp51044;
using boost::counting_iterator;

int main()
{
	std::vector<long long> 
      v(counting_iterator<long long>(0LL), counting_iterator<long long>(1000000LL));
	std::cout << async_accumulate(v.begin(), v.end(), 0LL) << std::endl;
    return 0;
}
