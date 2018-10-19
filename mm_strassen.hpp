#pragma once
#include"matrix.hpp"
#include"mm_classic.hpp"


template<class RING>
void add_partial(Matrix<RING> &target, Matrix<RING> &input, int_pair start)
{// add data of input matrix(smaller than target) into part of target matrix specified by start index.
    assert(start.first + input.shape.first <= target.shape.first);
    assert(start.second + input.shape.second <= target.shape.second);

    auto target_iter = target.index(start.first, start.second);
    auto input_iter = input.index(0, 0);
    for(size_t i = 0; i < input.shape.first; i++)
    {
        target_iter = target.index(start.first + i, start.second);
        input_iter = input.index(i, 0);
        for(size_t j = 0; j < input.shape.second; j++)
        {
            *target_iter++ = *input_iter++;
        }
    }
}

template<class RING>
void subt_partial(Matrix<RING> &target, Matrix<RING> &input, int_pair start)
{// subtract data of input matrix(smaller than target) to part of target matrix specified by start index.
    assert(start.first + input.shape.first <= target.shape.first);
    assert(start.second + input.shape.second <= target.shape.second);

    auto target_iter = target.index(start.first, start.second);
    auto input_iter = input.index(0, 0);
    for(size_t i = 0; i < input.shape.first; i++)
    {
        target_iter = target.index(start.first + i, start.second);
        input_iter = input.index(i, 0);
        for(size_t j = 0; j < input.shape.second; j++)
        {
            *target_iter++ -= *input_iter++;
        }
    }
}

template<class RING>
Matrix<RING> mm_strassen(const Matrix<RING> &m1, const Matrix<RING> &m2)
{
    unsigned threshold = 16;
    unsigned size = m1.shape.first;
    if (size < threshold)
    {
        // use classical MM
        return mm_classic(m1, m2);
    }
    unsigned size_new = (size >> 1);
    
    auto A11 = m1.slice(int_pair(       0,        0), int_pair(size_new, size_new));
    auto A12 = m1.slice(int_pair(       0, size_new), int_pair(size_new, size-size_new));
    auto A21 = m1.slice(int_pair(size_new,        0), int_pair(size-size_new, size_new));
    auto A22 = m1.slice(int_pair(size_new, size_new), int_pair(size-size_new, size-size_new));

    auto B11 = m2.slice(int_pair(       0,        0), int_pair(size_new, size_new));
    auto B12 = m2.slice(int_pair(       0, size_new), int_pair(size_new, size-size_new));
    auto B21 = m2.slice(int_pair(size_new,        0), int_pair(size-size_new, size_new));
    auto B22 = m2.slice(int_pair(size_new, size_new), int_pair(size-size_new, size-size_new));
    
    Matrix<RING> result(size);

    Matrix<RING> temp(size_new);

    temp = mm_strassen(A11 + A22, B11 + B22);
    add_partial(result, temp, int_pair(0, 0)); // to C11
    add_partial(result, temp, int_pair(size_new, size_new)); // to C22
    
    temp = mm_strassen(A21 + A22, B11);
    add_partial(result, temp, int_pair(size_new, 0)); // to C21
    subt_partial(result, temp, int_pair(size_new, size_new)); // to C22
    
    temp = mm_strassen(A11, B12 - B22);
    add_partial(result, temp, int_pair(0, size_new)); // to C12
    add_partial(result, temp, int_pair(size_new, size_new)); // to C22

    temp = mm_strassen(A22, B21 - B11);
    add_partial(result, temp, int_pair(0, 0)); // to C11
    add_partial(result, temp, int_pair(size_new, 0)); // to C21

    temp = mm_strassen(A11 + A12, B22);
    subt_partial(result, temp, int_pair(0, 0)); // to C11
    add_partial(result, temp, int_pair(0, size_new)); // to C12
    
    temp = mm_strassen(A21 - A11, B11 + B12);
    add_partial(result, temp, int_pair(size_new, size_new)); // to C22

    temp = mm_strassen(A12 - A22, B21 + B22);
    add_partial(result, temp, int_pair(0, 0)); // to C11

    return result;
}

