#include <iostream>
#include <random>
#include "types.hpp"
#include "protocol.hpp"
#include "aggregation.hpp"

int main()
{
    Rq p{ 82399373UL, 736657621UL, 532192006UL, 581473157UL };
    poly_vector<1> v{p};
    std::cout << v << std::endl;
    std::cout << conjugate(v);
}