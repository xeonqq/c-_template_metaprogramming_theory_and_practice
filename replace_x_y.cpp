
#include <type_traits>
#include <iostream>
/*
 *
 *Write a ternary metafunction replace_type<c,x,y> that takes an arbitrary compound type c as its first parameter,
and replaces all occurrences of a type x within c with y:
 *
 *
 * */

template <typename C, typename X, typename Y>
struct replace_type {
	using type = C;
};

template <typename T, typename SourceType, typename TargetType>
using replace_type_t = typename replace_type<T, SourceType, TargetType>::type;

template <typename X, typename Y>
struct replace_type <X*, X, Y>{
	using type = Y*;
};

template <typename S, typename T>
struct replace_type<S, S, T>
{
    using type = T;
};

template <typename X, size_t N, typename Y>
struct replace_type <X* [N], X, Y>{
	using type = Y* [N];
};

//template <typename X, typename Y>
//struct replace_type <X (*) (X), X, Y>{
//	using type = Y (*) (Y);
//};

template <typename R, typename X, typename... Args, typename Y>
struct replace_type <R (*) (Args...), X, Y>{
	using ret_t = typename replace_type<R, X, Y>::type;
	using type= ret_t (*) (replace_type_t<Args, X, Y>...);
};

int main()
{

typedef replace_type< void*, void, int >::type t1; // int*
typedef replace_type<int const*[10], int const, long>::type t2; // long* [10]

typedef replace_type< char& (*)(char&), char&, long&>::type t3; // long& (*)(long&)

typedef replace_type<float & (*) (double &, float &), float&, long>::type t4;

std::cout << std::is_same<t1, int*>::value << std::endl;
std::cout << std::is_same<t2, long*[10]>::value << std::endl;
std::cout << std::is_same<t3, long& (*)(long&)>::value << std::endl;
std::cout << std::is_same<t3, long& (*)(long&)>::value << std::endl;
std::cout << std::is_same<t4, long (*) (double &, long)>::value << std::endl;
}
