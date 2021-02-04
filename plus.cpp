#include <iostream>
#include <type_traits>

template <int T>
struct A{
	using type = int;
	static const int value=T;
};

template <typename Lhs, typename Rhs>
struct plus{
	static const typename Lhs::type value= Lhs::value + Rhs::value;
};

int main() {

	std::cout << std::is_same<A<1>, A<2>>::value << std::endl;
	std::cout << std::is_same<A<1>, A<1>>::value << std::endl;
	std::cout << plus<A<1>,A<2>>::value <<std::endl;
	return 0;
}

