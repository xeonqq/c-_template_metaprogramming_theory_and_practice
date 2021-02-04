#include <type_traits>
#include <cassert>

template <typename A, typename B>
struct True{
	using type = A;
};

template <typename A, typename B>
struct False{
	using type = B;
};

//meta function class
struct False_f
{

	template <typename A, typename B>
	struct apply
	{
		using type = typename False<A, B>::type;
	};
};

struct True_f
{

	template <typename A, typename B>
	struct apply
	{
		using type = typename True<A, B>::type;
	};
};

template <typename T1, typename T2>
struct Or
{
	using type = typename T1::template apply<True_f, T2>::type;
};

template <typename T1, typename T2>
struct And
{
	using type = typename T1::template apply<T2, False_f>::type;
};


int main() {

	assert((std::is_same<Or<True_f, False_f>::type, True_f>::value));
	assert((std::is_same<Or<False_f, True_f>::type, True_f>::value));
	assert((std::is_same<Or<False_f, False_f>::type, False_f>::value));
	assert((std::is_same<Or<True_f, True_f>::type, True_f>::value));

	assert((std::is_same<And<True_f, False_f>::type, False_f>::value));
	assert((std::is_same<And<False_f, True_f>::type, False_f>::value));
	assert((std::is_same<And<False_f, False_f>::type, False_f>::value));
	assert((std::is_same<And<True_f, True_f>::type, True_f>::value));
}
