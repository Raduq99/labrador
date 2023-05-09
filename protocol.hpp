#pragma once

#include "types.hpp"
#include "projection.hpp"

poly_vector<K1> step1(std::array<poly_vector<N>, R> s);

bool step2(std::array<poly_vector<N>, R> s, INT_TYPE beta);

bool step3(
    std::array<std::array<poly_vector<N>, FL>, R> phi_prime, 
    std::array<poly_matrix<R, R>, FL> A_prime,
    std::array<INT_TYPE, FL> b_prime,
    std::array<projection, R> projections, 
    coeff_vector<PROJ_SIZE> p,
    std::array<poly_vector<N>, R> s);

 std::array<poly_vector<N>, R> step4(
    std::array<std::array<poly_vector<N>, FUNC_COUNT>, R> phi_second,
    std::array<std::array<poly_vector<N>, FK>, R> phi);

poly_vector<N> step5(
    std::array<poly_vector<N>, R> phi,
    std::array<poly_vector<N>, R> s);