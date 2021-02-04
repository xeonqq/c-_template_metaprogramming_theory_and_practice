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


template <typename Input>
struct Not{
	using type = typename Input::template apply<False_f,True_f>::type;
};

int main()
{
	assert((std::is_same<Not<True_f>::type, False_f>::value));
	assert((std::is_same<Not<False_f>::type, True_f>::value));
	return 0;
}
