#include "aggregation.hpp"

std::array<std::array<poly_vector<N>, FUNC_COUNT>, R> compute_phi_second(
    std::array<coeff_vector<FL>, FUNC_COUNT> psi,
    std::array<coeff_vector<256>, FUNC_COUNT> omega,
    std::array<std::array<poly_vector<N>, FL>, R> phi_prime,
    std::array<projection, R> pi)
{
    std::array<std::array<poly_vector<N>, FUNC_COUNT>, R> res;
    for(size_t i = 0; i < R; i++)
    {
        for(size_t k; k < FUNC_COUNT; k++)
        {
            poly_vector<N> phi = res[i][k];
        
            for(size_t l = 0; l < FL; l++)
            {
                INT_TYPE psi_l = psi[k][l];
                poly_vector<N> phi_l = phi_prime[i][l];
                phi = phi + psi_l * phi_l;
            }

            for(size_t j = 0; j < 256; j++)
            {
                INT_TYPE omega_j = omega[k][j];
                poly_vector<N> inv_proj = conjugate(pi[i][j]);
                phi = phi + omega_j * inv_proj;
            }
        }
    }
    return res;
}


std::array<Rq, FUNC_COUNT> compute_b_second(
    std::array<coeff_vector<FL>, FUNC_COUNT> psi,
    std::array<poly_matrix<R, R>, FL> A_prime,
    std::array<std::array<poly_vector<N>, FUNC_COUNT>, R> phi_second,
    std::array<poly_vector<N>, R> s)
{
    // compute a_second
    std::array<poly_matrix<R, R>, FUNC_COUNT> A_second;
    for(size_t k = 0; k < FUNC_COUNT; k++)
    {

        for(size_t i = 0; i < R; i++)
        {
            for(size_t j = 0; j < R; j++)
            {
                Rq a = A_second[k][i][j];
                for(size_t l = 0; l < FL; l++)
                {
                    a = a + psi[k][l] * A_prime[l][i][j];
                }
            }
        }
    }
    
    std::array<Rq, FUNC_COUNT> b_second;
    for(size_t k = 0; k < FUNC_COUNT; k++)
    {
        Rq b = b_second[k];
        for(size_t i = 0; i < R; i++)
        {
            for(size_t j = 0; j < R; j++)
            {
                b = b + A_second[k][i][j] * inner_product(s[i], s[j]);
            }
        }
        for(size_t i = 0; i < R; i++)
        {
            poly_vector<N> phi = phi_second[i][k];
            b = b + inner_product(phi, s[i]);
        }
    }
    return b_second;
}

bool check_b0(std::array<Rq, FUNC_COUNT> b_second,
    std::array<INT_TYPE, FL> b_prime,
    std::array<coeff_vector<FL>, FUNC_COUNT> psi,
    std::array<coeff_vector<256>, FUNC_COUNT> omega,
    coeff_vector<PROJ_SIZE> p
)
{
    for(size_t k = 0; k < FUNC_COUNT; k++)
    {
        INT_TYPE b0_second = *b_second[k].begin();
        INT_TYPE inner_prod = inner_product(omega[k], p);
        INT_TYPE b0_prime = 0;
        for(size_t l = 0; l < FL; l++)
        {
            b0_prime += b_prime[l] * psi[k][l];
        }
        
        if(b0_second != inner_prod + b0_prime)
        {
            return false;
        }
    }
    return true;
}

 std::array<poly_vector<N>, R> compute_phi_aggregated(
    poly_vector<FK> alpha,
    poly_vector<FUNC_COUNT> beta,
    std::array<std::array<poly_vector<N>, FK>, R> phi,
    std::array<std::array<poly_vector<N>, FUNC_COUNT>, R> phi_second
)
{
    std::array<poly_vector<N>, R> phi_aggregated;
    for(size_t i = 0; i < R; i++)
    {
        poly_vector<N> phi_i = phi_aggregated[i];
        for(size_t k = 0; k < FK; k++)
        {
            phi_i = phi_i + alpha[k] * phi[i][k];
        }
        for(size_t k = 0; k < FUNC_COUNT; k++)
        {
            phi_i = phi_i + beta[k] * phi_second[i][k];
        }
    }
    return phi_aggregated;
}