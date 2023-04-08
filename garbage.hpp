#pragma once
#include "types.hpp"
#include "decompose.hpp"

template <size_t size>
poly_vector<T2> construct_g(poly_vector<size> si, poly_vector<size> sj)
{
    Rq p = inner_product(si, sj);
    return decompose(p);
}