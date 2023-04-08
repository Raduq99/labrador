#pragma once

#include <random>
#include "types.hpp"

using projection = std::array<poly_vector<N>, PROJ_SIZE>;

void init_proj_matrix(projection &pi);
std::array<projection, R> generate_projections();
coeff_vector<PROJ_SIZE> apply_projections(
    std::array<projection, R> proj,  
    std::array<poly_vector<N>, R> s);