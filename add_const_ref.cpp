#include <type_traits>
#include <iostream>
/*
 *
 * Write a unary metafunction add_const_ref<T> that
 * returns T if it is a reference type,
 * and otherwise returns T const&.
 * Write a program to test your metafunction. Hint: you can use boost::is_same to test the results.
 *
 * */

using namespace std;


template <bool b, typename T>
struct add_const_impl;

template <typename T>
struct add_const_impl<true, T>
{
	using type=typename remove_reference<T>::type;
};

template <typename T>
struct add_const_impl<false, T>
{
	using type=typename add_const<T>::type&;
};

template <typename T>
struct add_const_ref
{
	using type = typename add_const_impl<is_reference<T>::value, T>::type;
};

int main()
{
	cout << is_same<add_const_ref<int&>::type, int>::value << endl;
	cout << is_same<add_const_ref<int>::type, const int&>::value << endl;
	return 0;

}



