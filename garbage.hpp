#pragma once
#include "types.hpp"
#include "decompose.hpp"

poly_vector<T2> construct_g(poly_vector<N> s_i, poly_vector<N> s_j);

poly_vector<T1> construct_h(poly_vector<N> s_i, poly_vector<N> s_j, poly_vector<N> phi_i, poly_vector<N> phi_j);