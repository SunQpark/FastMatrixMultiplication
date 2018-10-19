#pragma once
#include"matrix.hpp"



template<class RING>
Matrix<RING> mm_classic(const Matrix<RING> &m1, const Matrix<RING> &m2)
{
    // compute shape of result matrix and initialize data as empty vector
    int_pair shape {m1.shape.first, m2.shape.second};
    auto len_iter = m1.shape.second;
 
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

template<class RING>
Matrix<RING> mm_classic(View<RING> &m1, View<RING> &m2)
{
    return mm_classic(m1.get_target(), m2.get_target());
}

template<class RING>
Matrix<RING> mul_strassen(Matrix<RING> &m1, Matrix<RING> &m2)
{
    // compute shape of result matrix and initialize data as empty vector
    int_pair shape {m1.shape.first, m2.shape.second};

    unsigned n_elt = shape.first * shape.second;
    vector<RING> data(n_elt, 0.0);
    Matrix<RING> result(data, shape);
    int_pair origin{0, 0};
    View<RING> target (result, origin, shape);
    
    View<RING> mat1 (m1, origin, shape);
    View<RING> mat2 (m2, origin, shape);
    core_strassen(target, mat1, mat2);
    return result;
}

template<class RING>
void core_strassen(View<RING> &target, View<RING> &m1, View<RING> &m2)
{
    // classical multiplication when sizes are small enough
    unsigned n = target.shape[0];
    if (n <= 4) {
        for(size_t i = 0; i < n; i++)
        {
            for(size_t j = 0; j < n; j++)
            {
                auto tar = target.index(i, j);
                *tar = 0.0;
                for(size_t k = 0; k < n; k++)
                {
                    *tar += *m1.index(i, k) * *m2.index(k, j);
                }
            }
        }
    }
}


template<class RING> 
Matrix<RING> operator+(View<RING>& v1, View<RING>& v2){
    int_pair shape = v1.shape;
    vector<RING> data(v1.n_elt());
    Matrix<RING> result(data, shape);

    
}
