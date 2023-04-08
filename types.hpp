#pragma once
#include "nfl.hpp"

#define INT_TYPE uint32_t
#define DEGREE 4
#define COEFF_BITS 30
#define N 2
#define R 1 // number of witnesses s_i
#define K 2
#define K1 3
#define K2 3
#define T1 2
#define T2 2
#define B1 33000
#define B2 33000
#define PROJ_SIZE 256 // 3
#define FK 3 // K - number of function f 
#define FL 3 // L - number of function f'

using Rq = nfl::poly_from_modulus<INT_TYPE, DEGREE, COEFF_BITS>;
const INT_TYPE MODULUS = Rq::get_modulus(0); // 1073479681

Rq operator*(const INT_TYPE &c, const Rq &p);
Rq operator*(const Rq &p, const INT_TYPE &c);
Rq conjugate(Rq &p);


//////////// POLYNOMIAL VECTOR

template <size_t size>
using poly_vector = std::array<Rq, size>;

template <size_t size>
void init_random_poly_vector(poly_vector<size> &v)
{
    for (size_t i = 0; i < size; i++)
        v[i] = Rq(nfl::uniform());
}

template <size_t size>
Rq inner_product(poly_vector<size> &a, poly_vector<size> &b)
{
    Rq res;
    for (size_t i = 0; i < size; i++)
        res = res + a[i] * b[i];
    return res;
}

template <size_t size>
poly_vector<size> conjugate(poly_vector<size> &v)
{
    poly_vector<size> res;
    for(auto v_coeff = v.begin(), res_coeff = res.begin(); v_coeff != v.end(); v_coeff++, res_coeff++)
    {
        *res_coeff = conjugate(*v_coeff);
    }
    return res;
}

template <size_t size>
poly_vector<size> operator+(const poly_vector<size> &v1, const poly_vector<size> &v2)
{
    poly_vector<size> sum;
    for (size_t i = 0; i < size; i++)
    {
        sum[i] = v1[i] + v2[i];
    }
    return sum;
}

template <size_t size>
poly_vector<size> operator*(const INT_TYPE &c, const poly_vector<size> &v)
{
    poly_vector<size> res;
    for (size_t i = 0; i < size; i++)
    {
        res[i] = c * v[i];
    }
    return res;
}

template <size_t size>
std::ostream& operator<<(std::ostream& os, const poly_vector<size> &v)
{
    for (auto &vi: v)
    {
        os << vi << "\n";
    }
    return os;
}

//////////// COEFFICIENTS VECTOR

template <size_t size>
using coeff_vector = std::array<INT_TYPE, size>;

template <size_t vector_size, size_t poly_degree>
coeff_vector<vector_size * poly_degree> init_coefficient_vector(poly_vector<vector_size> &v)
{
    coeff_vector<vector_size * poly_degree> s;
    for (size_t i = 0; i < v.size(); i++)
    {
        std::copy(v[i].begin(), v[i].end(), s.begin() + (i * poly_degree));
    }
    return s;
}

template <size_t size>
void init_random_coeff_vector(coeff_vector<size> &v)
{
    // we take advantage of fastrandombytes() used in nfl::uniform
    nfl::poly_from_modulus<INT_TYPE, size, COEFF_BITS> p = nfl::uniform();
    std::copy(p.begin(), p.end(), v.begin());
}

template <size_t size>
INT_TYPE inner_product(coeff_vector<size> &a, coeff_vector<size> &b)
{
    uint64_t res = 0;
    for (size_t i = 0; i < size; i++)
        res += ((uint64_t)a[i] * b[i]) % MODULUS;

    return (INT_TYPE)res % MODULUS;
}

template <size_t size>
std::ostream& operator<<(std::ostream& os, const coeff_vector<size> &v)
{
    os << "[";
    for (auto &vi: v)
    {
        os << vi << " ";
    }
    os << "]\n";
    return os;
}

/* We use the squared norm so we don't have to deal with floating numbers
    ||v|| = √<v, v> => ||v||^2 = <v, v>
*/
template <size_t size>
INT_TYPE norm_squared(coeff_vector<size> &v)
{
    return inner_product(v, v);
}

//////////// POLYNOMIAL MATRIX

template <size_t row_size, size_t column_size>
using poly_matrix = std::array<std::array<Rq, column_size>, row_size>;

template <size_t row_size, size_t column_size>
void init_random_poly_matrix(poly_matrix<row_size, column_size> &A)
{
    for (size_t i = 0; i < row_size; i++)
    {
        init_random_poly_vector<column_size>(A[i]);
    }
}

template <size_t row_size, size_t column_size>
poly_vector<row_size> multiply(poly_matrix<row_size, column_size> &A, poly_vector<column_size> &v)
{
    poly_vector<row_size> res;
    for (size_t i = 0; i < row_size; i++)
    {
        res[i] = Rq();
        for (size_t j = 0; j < column_size; j++)
        {
            res[i] = res[i] + A[i][j] * v[j];
        }
    }

    return res;
}

// template <size_t row_size, size_t column_size>
// poly_vector<row_size> multiply(poly_matrix<row_size, column_size> &A, Rq &f)
// {
//     poly_vector<1> v = {f};
//     return multiply(A, v);
// }