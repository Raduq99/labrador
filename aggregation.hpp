#include "nfl.hpp"
#include "types.hpp"
#include "projection.hpp"


template <size_t count>
std::array<coeff_vector<count>, FUNC_COUNT> generate_challenges()
{
    std::array<coeff_vector<count>, FUNC_COUNT> challenges;
    for(size_t k = 0; k < FUNC_COUNT; k++)
    {
        init_random_coeff_vector<count>(challenges[k]);
    }
    return challenges;
}

std::array<std::array<poly_vector<N>, FUNC_COUNT>, R> compute_phi_second(
    std::array<coeff_vector<FL>, FUNC_COUNT>, 
    std::array<coeff_vector<256>, FUNC_COUNT>, 
    std::array<std::array<poly_vector<N>, FL>, R>,
    std::array<projection, R>);

std::array<Rq, FUNC_COUNT> compute_b_second(
    std::array<coeff_vector<FL>, FUNC_COUNT>,
    std::array<poly_matrix<R, R>, FL>,
    std::array<std::array<poly_vector<N>, FL>, R>,
    std::array<poly_vector<N>, R>);

bool check_b0(std::array<Rq, FUNC_COUNT> b_second,
    std::array<INT_TYPE, FL> b_prime,
    std::array<coeff_vector<FL>, FUNC_COUNT> psi,
    std::array<coeff_vector<256>, FUNC_COUNT> omega,
    coeff_vector<PROJ_SIZE> p
);

 std::array<poly_vector<N>, R> compute_phi_aggregated(
    poly_vector<FK> alpha,
    poly_vector<FUNC_COUNT> beta,
    std::array<std::array<poly_vector<N>, FK>, R> phi,
    std::array<std::array<poly_vector<N>, FUNC_COUNT>, R> phi_second
);