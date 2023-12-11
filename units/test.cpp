#include "units.h"
#include <iostream>
using namespace units;

int main()
{
    quantity<length> l1 = 10;
    quantity<length> l2 = 1;
    quantity<velocity> v = 2;
    quantity<units::time> t = 1;
    const auto result =  v*t;
    std::cout<<(l1+l2)()<<std::endl;
    std::cout<<(l1-l2)()<<std::endl;
    std::cout<<std::is_same<decltype(v*t), quantity<length>>::value<<std::endl;
    std::cout<<std::is_same<decltype(l1/t), quantity<velocity>>::value<<std::endl;
    return 0;
}

