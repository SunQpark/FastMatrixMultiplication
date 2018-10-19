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

    Matrix(const unsigned &size)
    {// construct empty square matrix having shape (size, size)
        shape = int_pair(size, size);
        data = vector<RING>(size * size, RING(0));
    }

    Matrix(const int_pair &shape):
    shape(shape)
    {// construct empty matrix having given shape
        data = vector<RING>(shape.first*shape.second, RING(0));
    }
 
    Matrix(const vector<RING> &value, const int_pair &shape): 
    data(value), shape(shape)
    {}

    const typename vector<RING>::iterator index(unsigned i, unsigned j)
    {
        // ensure indices are in the right range
        // assert(i < shape.first && j < shape.second); 
        auto ptr = data.begin() + (i * shape.first + j);
        return ptr;
    }

    Matrix<RING> slice(int_pair start, int_pair window) const
    {// copy and return part of matrix specified by start index and return size(window)
        // assert(start.first + window.first <= shape.first);
        // assert(start.second + window.second <= shape.second);

        vector<RING> output_data(window.first * window.second);
        Matrix<RING> result(output_data, window);

        auto input_iter = data.begin();
        auto output_iter = result.index(0, 0);
        for(size_t i = 0; i < window.first; i++)
        {
            input_iter = data.begin() + ((start.first + i) * shape.first + (start.second));
            for(size_t j = 0; j < window.second; j++)
            {
                *output_iter++ += *input_iter++;
            }
        }
        return result;
    }

    Matrix<RING>& operator+= (const Matrix<RING> &other)
    {
        // ensure that both matrices have same shape
        // assert(shape.first == other.shape.first);
        // assert(shape.second == other.shape.second);

        auto iter = other.data.begin();
        for(auto &e: data)
        {
            e += *iter;
            iter++;
        }
        return *this;
    }

    Matrix<RING>& operator-= (const Matrix<RING> &other)
    {
        // ensure that both matrices have same shape
        // assert(shape.first == other.shape.first);
        // assert(shape.second == other.shape.second);

        auto iter = other.data.begin();
        for(auto &e: data)
        {
            e -= *iter;
            iter++;
        }
        return *this;
    }

    bool operator==(const Matrix<RING> &other)
    {
        if (shape.first != other.shape.first) {return false;}
        if (shape.second != other.shape.second) {return false;}
        
        for(size_t i = 0; i < shape.first * shape.second; i++)
        {
            if (data[i] != other.data[i]){return false;}
        }
        return true;
    }
};

template<class RING>
Matrix<RING> operator+(const Matrix<RING> &m1, const Matrix<RING> &m2)
{
    Matrix<RING> result = m1;
    result += m2;
    return result;
}

template<class RING>
Matrix<RING> operator-(const Matrix<RING> &m1, const Matrix<RING> &m2)
{
    Matrix<RING> result = m1;
    result -= m2;
    return result;
}


template<class RING>
void print(const Matrix<RING> &mat)
{// helper func for printing matrix.
    auto iter = mat.data.begin();
    
    auto n_cols = mat.shape.second;
    auto n_rows = mat.shape.first;

    cout << endl;
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
