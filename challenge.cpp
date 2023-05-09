#include "challenge.hpp"

poly_vector<R> generate_c()
{
    poly_vector<R> c;
    for(size_t i = 0; i < R; i++)
    {
        // do {
        c[i] = sample_challenge_polynomial();
        // } while(operator_norm(c[i]) > 15);
    }
    return c;
}

poly_vector<N> compute_z(poly_vector<R> c, std::array<poly_vector<N>, R> s)
{
    poly_vector<N> z;
    for(size_t i = 0; i < R; i++)
    {
        z = z + c[i] * s[i];
    }
}

Rq sample_challenge_polynomial()
{
    // zero_coeffs = 23, one_coeffs = 31, two_coeffs = 10;
    size_t coeffs_freq[3] = {23, 31, 10};
    coeff_vector<DEGREE> f;
    for(size_t i = 0; i < DEGREE; i++)
    {
        // rejection sample until either 0, 1 or 2 and only if still needed (keeping count in coeffs_freq)
        unsigned char coeff;
        do 
        {
            nfl::fastrandombytes(&coeff, 1);
        } while( (coeff & 0b11) == 3 || !coeffs_freq[(coeff & 0b11)]);
        coeff = (coeff & 0b11);
        unsigned char sign;
        nfl::fastrandombytes(&sign, 1);
        f[i] = coeff == 0 || (sign & 1) == 0 ? coeff : MODULUS - coeff;
        coeffs_freq[coeff]--;
    }
    Rq res;
    res.set(f.begin(), f.end(), false);
    return res;
}
