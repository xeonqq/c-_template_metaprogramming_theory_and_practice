#include <array>
#include <iostream>
#include <type_traits>

template <int I>
struct Int2Type
{
  enum {value=I};
};


template<typename T, size_t N>
struct Array{
  enum sort_algo {None,MergeSort, QuickSort};
  const static sort_algo algo = N <= 1 ? None: (N>10? QuickSort:MergeSort);
  void sort(std::integral_constant<int,QuickSort>){
    
    std::cout << "quick sort\n";
  }
  void sort(std::integral_constant<int,MergeSort>){
    
    std::cout << "merge sort\n";
  }
  void sort(std::integral_constant<int,None>){
    std::cout << "no sort\n";
  }

  void sort(){
    sort(std::integral_constant<int,algo>());
  }
  std::array<T, N> data;
};
int main()
{
  Array<int,10> a;
  a.sort();
  return 0;
}
