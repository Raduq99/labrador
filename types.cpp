#include "types.hpp"

Rq operator*(const INT_TYPE &c, const Rq &p)
{
    Rq res;
    std::array<INT_TYPE, DEGREE> aux;
    int i = 0;
    for(auto &coeff: p)
    {
        aux[i++] = c * coeff;
    }
    res.set(aux.begin(), aux.end(), true);
    return res;
}

Rq operator*(const Rq &p, const INT_TYPE &c)
{
    return c * p;
}

/*
    r(X^-1) = r0 - sum_i( ri * X^(d-i) ), i = 1:d-1
*/
Rq conjugate(Rq &p)
{
    Rq c;
    std::array<INT_TYPE, DEGREE> aux;
    aux[0] = *p.begin();
    size_t i = DEGREE - 1;
    for(auto pi = p.begin() + 1; pi != p.end(); pi++)
    {
        aux[i--] = MODULUS - *pi;
    }
    
    c.set(aux.begin(), aux.end(), true);
    return c;
}