#include <type_traits>
#include <cassert>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
using boost::mpl::placeholders::_1;
using boost::mpl::lambda;
using namespace boost;
template <typename Input>
struct AddPointer{
	using type = Input*;
};

/*
 * metafunction class:
 * A metafunction class is a class with a publicly accessible nested metafunction called apply.
 * Whereas a metafunction is a template but not a type, a metafunction class wraps that template within an ordinary non-templated class, which is a type
 */
struct AddPointerF{
	template <typename T>
	struct apply
	{
		using type = typename AddPointer<T>::type;
	};
};

template <typename F, typename X>
struct twice{
	using once = typename F::template apply<X>::type;
	using type = typename F::template apply<once>::type;
};

template <class UnaryMetaFunctionClass, class Arg>
struct apply1
: UnaryMetaFunctionClass::template apply<Arg>
{};

template <typename F, typename X>
struct Twice:apply1<F, typename apply1<F, X>::type>{
};

template <typename F, typename X>
struct Twice2:apply1<typename lambda<F>::type, typename apply1<typename lambda<F>::type, X>::type>{
};

template <typename F, typename X>
struct Twice3: mpl::apply<F, typename mpl::apply<F, X>::type>
{
};

int main() {
	using my_type = twice<AddPointerF, int>::type;
	using my_type_again = twice<typename lambda<AddPointer<_1>>::type, int>::type;
	using my_type1 = Twice<AddPointerF, int>::type;
	using my_type2 = Twice2<AddPointer<_1>, int>::type;
	using my_type3 = Twice3<AddPointer<_1>, int>::type;
	assert((std::is_same<my_type, int**>::value));
	assert((std::is_same<my_type_again, int**>::value));
	assert((std::is_same<my_type1, int**>::value));
	assert((std::is_same<my_type2, int**>::value));
	assert((std::is_same<my_type3, int**>::value));
	return 0;
}
