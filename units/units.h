#include <type_traits>
#include<utility>
#include<tuple>
namespace units{

template<int... Ints>
using int_ = std::integer_sequence<int, Ints...>;

template<int... Ints>
using vector_c = std::tuple<int_<Ints>...>;

typedef vector_c<1,0,0, 0> mass;
typedef vector_c<0,1,0, 0> length;
typedef vector_c<0,0,1, 0> time;
typedef vector_c<0,1,-1, 0> velocity;


struct plus_f
{
    template<int Int1, int Int2 >
    static constexpr int_<Int1+Int2> apply(int_<Int1>, int_<Int2>)
    {
        return {};
    }
};

struct minus_f
{
    template<int Int1, int Int2 >
    static constexpr int_<Int1-Int2> apply(int_<Int1>, int_<Int2>)
    {
        return {};
    }
};

template<typename Seq1, typename Seq2, typename BinaryOperation>
struct transform
{
  template<typename...Ts1, typename...Ts2>
  static constexpr auto apply(const std::tuple<Ts1...>& t1, const std::tuple<Ts2...>& t2)
  {
      return std::make_tuple(BinaryOperation::apply(Ts1(), Ts2())...);
  }
  using type = decltype(transform<Seq1,Seq2, BinaryOperation>::apply(Seq1(), Seq2()));  
};


template<typename Dimension, typename T=double>
class quantity
{
    public:
        quantity(T v): value_{v}{}
        T operator()() const
        {
            return value_;
        }

        T& operator()()
        {
            return value_;
        }

    private:
    T value_;
};

template<typename D, typename T>
quantity<D, T>
operator+(quantity<D, T> lhs, quantity<D, T> rhs)
{
    return quantity<D, T>(lhs() + rhs());
}

template<typename D, typename T>
quantity<D, T>
operator-(quantity<D, T> lhs, quantity<D, T> rhs)
{
    return quantity<D, T>(lhs() - rhs());
}

template<typename D1, typename D2, typename T>
quantity<typename transform<D1, D2, plus_f>::type, T>
operator*(quantity<D1, T> lhs, quantity<D2, T> rhs)
{
    return quantity<typename transform<D1, D2, plus_f>::type, T>(lhs() * rhs());
}

template<typename D1, typename D2, typename T>
quantity<typename transform<D1, D2, minus_f>::type, T>
operator/(quantity<D1, T> lhs, quantity<D2, T> rhs)
{
    return quantity<typename transform<D1, D2, plus_f>::type, T>(lhs() / rhs());
}
}
