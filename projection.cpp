#include "projection.hpp"

void init_proj_matrix(projection &pi)
{
    for(size_t i = 0; i < PROJ_SIZE; i++)
    {
        for(size_t j = 0; j < N; j++)
        {
            pi[i][j] = nfl::ZO_dist(0x3F);
        }
    }
}

std::array<projection, R> generate_projections()
{
    std::array<projection, R> projections;
    for (size_t i = 0; i < R; i++)
    {
        projection pi;
        init_proj_matrix(pi);
        projections[i] = pi;
    }
    return projections;
}

coeff_vector<PROJ_SIZE> apply_projections(std::array<projection, R> proj, std::array<poly_vector<N>, R> s)
{
    coeff_vector<PROJ_SIZE> p{};
    for(size_t j = 0; j < PROJ_SIZE; j++)
    {
        for(size_t i = 0; i < R; i++)
        {
            coeff_vector<N * DEGREE> p_coeff = init_coefficient_vector<N, DEGREE>(proj[i][j]);
            coeff_vector<N * DEGREE> s_coeff = init_coefficient_vector<N, DEGREE>(s[i]);
            p[j] = p[j] + inner_product(p_coeff, s_coeff) % MODULUS;
        }
    }
    return p;
}