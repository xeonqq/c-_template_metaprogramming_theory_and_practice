#include <iostream>
#include <type_traits>
template<typename U, typename V>
struct TypeList{
  using HEAD = U;
  using TAIL = V;
};

struct NullType {};

#define TYPELIST1(T1) TypeList<T1, NullType>  
#define TYPELIST2(T1,T2) TypeList<T1, TYPELIST1(T2)>  
#define TYPELIST3(T1,T2,T3) TypeList<T1, TYPELIST2(T2,T3)>  


using MyTypes = TYPELIST3(int, float, double);


template <typename T>
struct TypeListLen;

template <typename U, typename V>
struct TypeListLen<TypeList<U, V>>
{
  enum {value=1+TypeListLen<V>::value};
};

template <>
struct TypeListLen<NullType>
{
  enum {value=0};
};

template <class TList, unsigned int index> struct TypeAt
{
  using type = typename TypeAt<typename TList::TAIL, index-1>::type;
};

template <class TList>
struct TypeAt<TList, 0>{
  using type = typename TList::HEAD;
};

template <class TList, typename T> struct IndexOf
{
  private:
    enum {temp=IndexOf<typename TList::TAIL, T>::value};
  public:
    enum {value=temp == -1? -1: 1+temp};
};

template <class HEAD, class TAIL> struct IndexOf<TypeList<HEAD, TAIL>, HEAD>
{
  enum {value=0};
};

template <typename T> struct IndexOf<NullType, T>
{
  enum {value=-1};
};

struct A{};
struct B{};


template<typename T>
T get()
{
  return T{};
}


void run(const A&) {std::cout<<"Run a\n";}
void run(const B&) {std::cout<<"Run b\n";}


template<typename TList>
struct Dispatcher{
  static void fire()
    {
    run(get<typename TList::HEAD>());

    Dispatcher<typename TList::TAIL>::fire();
    }
};

template<>
struct Dispatcher<NullType>{
  static void fire() {};
};


int main()
{
  //std::cout << TypeListLen<MyTypes>::value << std::endl;
  //std::cout << std::is_same<TypeAt<MyTypes, 1>::type, float>::value << std::endl;
  //std::cout << IndexOf<MyTypes, double>::value<< std::endl;
  //std::cout << IndexOf<MyTypes, unsigned int>::value<< std::endl;

  Dispatcher<TYPELIST2(A, B)>::fire();
  return 0;
}
