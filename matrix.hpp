#pragma once
#include<iostream>
#include<array>
#include<vector>
#include<cassert>
#include<algorithm>
#include<iterator>

using namespace std; 
using int_pair = pair<unsigned, unsigned>;


template<class RING>
class Matrix{
public:
    vector<RING> data;
    int_pair shape;

    Matrix(){}
 
    Matrix(const vector<RING> &value, const int_pair &shape): 
    data(value), shape(shape)
    {}

    Matrix<RING>& operator += (Matrix<RING> &other)
    {
        // ensure that both matrices have same shape
        assert(shape.first == other.shape.first);
        assert(shape.second == other.shape.second);

        auto iter = other.data.begin();
        for(auto &e: data)
        {
            e += *iter;
            iter++;
        }
        return *this;
    }

    typename vector<RING>::iterator index(unsigned i, unsigned j)
    {
        auto ptr = data.begin() + (i * shape.first + j);
        return ptr;
    }

    unsigned n_elt()
    {
        return shape.first * shape.second;
    }
};

template<class RING>
void print(const Matrix<RING> &mat)
{// helper func for printing matrix.
    auto iter = mat.data.begin();
    
    auto n_cols = mat.shape.second;
    auto n_rows = mat.shape.first;

    for(size_t i = 0; i < n_rows; i++)
    {
        for(size_t j = 0; j < n_cols; j++)
            {
            cout << *iter << "\t";    
            iter++;
        }
        cout << endl;
    }
  
}
