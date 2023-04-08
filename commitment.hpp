#pragma once
#include "nfl.hpp"
#include "types.hpp"

template <size_t commit_size, size_t input_size>
poly_vector<commit_size> ajtai_commit(poly_vector<input_size> &s) 
{
    poly_matrix<commit_size, input_size> A;
    init_random_poly_matrix<commit_size>(A);

    return multiply(A, s);
}


template <size_t commit_size>
poly_vector<commit_size> ajtai_commit(Rq &f) 
{
    poly_vector<1> v = {f};
    return ajtai_commit<commit_size, 1>(v);
}

