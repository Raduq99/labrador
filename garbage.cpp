#include "garbage.hpp"

poly_vector<T2> construct_g(poly_vector<N> s_i, poly_vector<N> s_j)
{
    Rq p = inner_product(s_i, s_j);
    return decompose<T2>(p);
}

poly_vector<T1> construct_h(poly_vector<N> s_i, poly_vector<N> s_j, poly_vector<N> phi_i, poly_vector<N> phi_j)
{
    Rq r1 = inner_product(phi_i, s_j);
    Rq r2 = inner_product(phi_j, s_i);
    Rq res = 0.5 * (r1 + r2);
    return decompose<T1>(res);
}