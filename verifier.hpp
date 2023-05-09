#include "types.hpp"

class Verifier
{
public:
    std::array<poly_vector<N>, R> s;
    // f
    std::array<std::array<poly_vector<N>, FL>, R> phi;
    std::array<poly_matrix<R, R>, FK> A;
    std::array<INT_TYPE, FK> b;
    // f'
    std::array<std::array<poly_vector<N>, FL>, R> phi_prime;
    std::array<poly_matrix<R, R>, FL> A_prime;
    std::array<INT_TYPE, FL> b_prime;

    // garbage
    poly_matrix<R, R> g;
    poly_matrix<R, R> h;

    // commits
    std::array<poly_vector<K>, R> t;
    poly_vector<K1> u1;
    poly_vector<K2> u2;

    
};