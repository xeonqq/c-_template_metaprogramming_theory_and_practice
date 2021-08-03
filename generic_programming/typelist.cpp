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
#define TYPELIST4(T1,T2,T3,T4) TypeList<T1, TYPELIST3(T2,T3,T4)>  


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


template <class TList, typename T> struct Append
{
  using type = TypeList<typename TList::HEAD, typename Append<typename TList::TAIL,T>::type>;
};

template <typename HEAD, typename TAIL> struct Append<NullType, TypeList<HEAD,TAIL>>
{
  using type=TypeList<HEAD, TAIL>;
};

template <> struct Append<NullType, NullType>
{
  using type=NullType;
};

template <typename T> struct Append<NullType, T>
{
  using type=TypeList<T, NullType>;
};

template <class TList, typename T> struct Erase;
template <class HEAD, class TAIL>
struct Erase<TypeList<HEAD, TAIL>,HEAD>
{
  using type = typename TList::TAIL;
};

template <class TList, typename T>
struct Erase<TList,T>
{
  using type = TypeList<typename TList::HEAD, typename Erase<typename TList::TAIL, T>::type>;
};


int main()
{
  std::cout << TypeListLen<MyTypes>::value << std::endl;
  std::cout << std::is_same<TypeAt<MyTypes, 1>::type, float>::value << std::endl;
  std::cout << IndexOf<MyTypes, double>::value<< std::endl;
  std::cout << IndexOf<MyTypes, unsigned int>::value<< std::endl;
  std::cout <<std::is_same<Append<MyTypes, long>::type, TYPELIST4(int, float, double, long)>::value <<std::endl;;
  std::cout <<std::is_same<Append<TYPELIST2(float, double), TYPELIST2(int, long)>::type, TYPELIST4(float, double, int, long)>::value <<std::endl;;
  std::cout << std::is_same<Erase<MyTypes,long>::type, TYPELIST2(float, double)>::value<< std::endl;
  return 0;
}
