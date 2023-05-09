#include "types.hpp"
#include "protocol.hpp"
#include "commitment.hpp"
#include "decompose.hpp"
#include "garbage.hpp"
#include "projection.hpp"
#include "aggregation.hpp"
#include "challenge.hpp"

poly_vector<K1> step1(std::array<poly_vector<N>, R> s)
{
    poly_vector<K1> u1;
    poly_vector<K> t;
    // ADD INNER COMMITMENTS OF s
    for (size_t i = 0; i < R; i++)
    {
        t = ajtai_commit<K, N>(s[i]);
        std::array<poly_vector<K>, T1> t_decomp = decompose<T1>(t);
        for (size_t k = 0; k < T1; k++)
        {
            u1 = u1 + ajtai_commit<K1, K>(t_decomp[k]);
        }
    }
    // ADD INNER COMMITMENTS OF GARBAGE G
    for (size_t i = 0; i < R; i++)
    {
        for (size_t j = i; j < R; j++)
        {
            poly_vector<T2> g_decomp = construct_g(s[i], s[j]);
            for (size_t k; k < T2; k++)
            {
                u1 = u1 + ajtai_commit<K2>(g_decomp[k]);
            }
        }
    }

    return u1;
}

bool step2(std::array<poly_vector<N>, R> s, INT_TYPE beta)
{
    // VERIFIER: generate r PI matrices
    std::array<projection, R> proj = generate_projections();
    // PROVER: compute projections
    coeff_vector<PROJ_SIZE> p = apply_projections(proj, s);
    // VERIFIER: check projection norms (with modulo)
    INT_TYPE norm = norm_squared(p);
    return norm <= 128 * beta * beta;
}

bool step3(
    std::array<std::array<poly_vector<N>, FL>, R> phi_prime, 
    std::array<poly_matrix<R, R>, FL> A_prime,
    std::array<INT_TYPE, FL> b_prime,
    std::array<projection, R> projections, 
    coeff_vector<PROJ_SIZE> p,
    std::array<poly_vector<N>, R> s)
{
    // k = 1, ..., 128/log(q)
    // VERIFIER: generate k challenges psi, omega
    std::array<coeff_vector<FL>, FUNC_COUNT> psi = generate_challenges<FL>();
    std::array<coeff_vector<256>, FUNC_COUNT> omega = generate_challenges<256>();
    // PROVER: compute k phi''
    std::array<std::array<poly_vector<N>, FUNC_COUNT>, R> phi_second = compute_phi_second(psi, omega, phi_prime, projections);
    // PROVER: compute k b'' 
    std::array<Rq, FUNC_COUNT> b_second = compute_b_second(psi, A_prime, phi_second, s);
    // VERIFIER: check constant of b''
    return check_b0(b_second, b_prime, psi, omega, p);
}

 std::array<poly_vector<N>, R> step4(
    std::array<std::array<poly_vector<N>, FUNC_COUNT>, R> phi_second,
    std::array<std::array<poly_vector<N>, FK>, R> phi)
{
    // generate challenges alpha, beta
    poly_vector<FK> alpha;
    init_random_poly_vector(alpha);
    poly_vector<FUNC_COUNT> beta;
    init_random_poly_vector(beta);
    //compute phi
    return compute_phi_aggregated(alpha, beta, phi, phi_second);
}


poly_vector<N> step5(
    std::array<poly_vector<N>, R> phi,
    std::array<poly_vector<N>, R> s)
{
    // compute commitment u2
    poly_vector<K2> u2;

    for(size_t i = 0; i < R; i++)
    {
        for(size_t j = 0; j < R; j++)
        {
            // compute garbage h
            poly_vector<T1> h_decomp = construct_h(s[i], s[j], phi[i], phi[j]);
            for(size_t k = 0; k < T1; k++)
            {
                u2 = u2 + ajtai_commit<K2>(h_decomp[k]);
            }
        }
    }

    // generate challenge c
    poly_vector<R> c = generate_c();
    // compute z
    return compute_z(c, s);
}