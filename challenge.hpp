#include "types.hpp"

poly_vector<R> generate_c();
poly_vector<N> compute_z(poly_vector<R> c, std::array<poly_vector<N>, R> s);

// PRIVATE
Rq sample_challenge_polynomial();