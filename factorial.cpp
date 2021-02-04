#include <iostream>
#include <type_traits>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <typeinfo>
#include <cassert>

using boost::mpl::placeholders::_1;
using boost::mpl::lambda;
using namespace boost;

template <size_t N>
struct Factorial{
	const static int value = N * Factorial<N-1>::value;
};

template <>
struct Factorial<1>{
	const static int value = 1;
};


int main() {
	assert((Factorial<4>::value == 24));

	return 0;
}
