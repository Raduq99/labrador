#include <iostream>
#include <random>
#include "types.hpp"
#include "protocol.hpp"
#include "aggregation.hpp"
#include "challenge.hpp"

#define beta 100 // norm constraint


int main()
{
    std::array<std::array<poly_vector<N>, FL>, R> phi_prime;
    std::array<std::array<poly_vector<N>, FK>, R> phi;
    std::array<poly_matrix<R, R>, FL> A_prime;
    std::array<INT_TYPE, FL> b_prime;
    std::array<poly_vector<N>, R> s;

    poly_vector<K1> u1 = step1(s);

    bool norm_ok = step2(s, beta);

    bool b_second_ok = step3(phi_prime, A_prime, b_prime, proj, p, s); // proj and p from step 2

    std::array<poly_vector<N>, R> phi_aggregated = step4(phi_second, phi); // phi_second from step3

    poly_vector<N> z = step5(phi_aggregated, s);
    poly_vector<R> c = generate_c();
    std::cout << c;
}