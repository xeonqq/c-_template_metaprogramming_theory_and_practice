#include <type_traits>
#include <cassert>

int function(int a)
{
	return a+1;
}

/**
 * meta function:
 *
 * metafunction-name <type-arguments...>:: type
**/

template <typename Input>
struct AddPointer{
	using type = Input*;
};

int main()
{
	using pointer = typename AddPointer<int>::type;
	assert((std::is_same<pointer, int*>::value));

	using std_pointer = typename std::add_pointer<int>::type;
	assert((std::is_same<std_pointer, int*>::value));
	return 0;
}
