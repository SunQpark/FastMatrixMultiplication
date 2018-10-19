#pragma once
#include"matrix.hpp"


template<class RING>
Matrix<RING> mm_classic(const Matrix<RING> &m1, const Matrix<RING> &m2)
{
    // compute shape of result matrix and initialize data as empty vector
    int_pair shape {m1.shape.first, m2.shape.second};
    auto len_iter = m1.shape.second;
 
    // initialize result data of matrix
    unsigned n_elt = shape.first * shape.second;
    vector<RING> data(n_elt, 0.0);

    // compute multiplication result iterating through elts
    unsigned col_idx = 0;
    unsigned row_idx = 0;
    unsigned n_cols = shape.second;
    
    for(auto &elt : data)
    {
        for(size_t i = 0; i < len_iter; i++)
        {
            elt += m1.data[row_idx * len_iter + i] * m2.data[n_cols * i + col_idx];
        }
        col_idx++;
        if (col_idx == n_cols)
        {
            row_idx++;
            col_idx = 0;
        }
    }
    
    Matrix<RING> result(data, shape);
    return result;
}