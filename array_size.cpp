#include <iostream>
#include <type_traits>
#include <array>
//not used here, the syntax indicats Container being a template class itself
template <template<typename...> class Container, class T, size_t N>
struct array_size
{
	static const std::size_t  value = N;
};

//general case
template <typename Container>
struct helper
{
};


//specialization on array
template <typename T, size_t N>
struct helper<std::array<T, N>>
{
	static constexpr std::size_t value{N};
};

int main()
{
	using Array = std::array<int, 10>;
	std::cout << helper<Array>::value<< std::endl;
}
