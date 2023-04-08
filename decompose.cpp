#include "decompose.hpp"

std::array<poly_vector<K>, T1> decompose(poly_vector<K> &t)
{
    std::array<std::array<std::array<INT_TYPE, DEGREE>, K>, T1> temp;
    size_t poly_index = 0, coeff_index = 0, base_index = 0;
    for (Rq &ti : t)
    {
        coeff_index = 0;
        for (auto coeff : ti)
        {
            base_index = 0;
            while (coeff)
            {
                temp[base_index][poly_index][coeff_index] = coeff % B1;
                coeff /= B1;
                base_index++;
            }
            coeff_index++;
        }
        poly_index++;
    }
    std::array<poly_vector<K>, T1> res;
    for (int i = 0; i < T1; i++)
    {
        for (int j = 0; j < K; j++)
        {
            res[i][j].set(temp[i][j].begin(), temp[i][j].end(), true);
        }
    }
    return res;
}

poly_vector<T2> decompose(Rq &f)
{
    std::array<std::array<uint32_t, DEGREE>, T2> temp;
    size_t coeff_index = 0, base_index = 0;
    for (auto coeff : f)
    {
        base_index = 0;
        while (coeff)
        {
            temp[base_index][coeff_index] = coeff % B2;
            coeff /= B2;
            base_index++;
        }
        coeff_index++;
    }

    poly_vector<T2> res;
    for (int i = 0; i < T1; i++)
    {
        res[i].set(temp[i].begin(), temp[i].end(), true);
    }
    return res;
}
