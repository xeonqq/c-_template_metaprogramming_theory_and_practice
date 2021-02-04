#include <type_traits>
#include <cassert>

using namespace std;

struct A {virtual ~A() {}};
struct B : A {};

template <class Target, class Source>
inline Target polymorphic_downcast(Source* x)
{
	assert( dynamic_cast<Target>(x) == x );
	return static_cast<Target>(x);
}

template <class Target, class Source>
inline Target polymorphic_downcast(Source& x)
{
	assert( dynamic_cast<std::add_pointer_t<Target>>(&x) == &x );
	return static_cast<Target>(x);
}


int main()
{
	B b;
	A* a_ptr = &b;
	B* b_ptr = polymorphic_downcast<B*>(a_ptr);

	A & a_ref = b;
	B & b_ref = polymorphic_downcast<B &>(a_ref);
	return 0;
}
