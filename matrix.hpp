#pragma once
#include<iostream>
#include<array>
#include<vector>
#include<cassert>
#include<algorithm>
#include<iterator>

using namespace std; 


template<class T>
class Matrix{
public:
    vector<unsigned> shape;
    vector<T> data;

    Matrix()
    {

    }

    Matrix(const vector<T> &value): data(value)
    {
        shape.push_back(data.size());
    }

    Matrix(const vector<T> &value, const vector<unsigned> &shape): 
    data(value), shape(shape)
    {}

    Matrix<T>& operator += (Matrix<T> &other)
    {
        auto iter = other.data.begin();
        for(auto &e: data)
        {
            e += *iter;
            iter++;
        }
        return *this;
    }

    void reshape(vector<unsigned> sh)
    {
        shape = sh;

        unsigned n_elt = 1;
        for(auto & dim:sh)
        {
            n_elt *= dim;
        }
        vector<T> data(n_elt);
    }

    typename vector<T>::iterator index(unsigned i, unsigned j)
    {
        auto ptr = data.begin() + (i * shape[1] + j);
        return ptr;
    }
};


template<class T> 
class View
{
private:
    vector<unsigned> shape;
    vector<unsigned> start_pt;
    Matrix<T>* target;
public:

    View(const Matrix<T> &mat, const vector<unsigned> &shape):
    shape(shape), target(&mat)
    {
        vector<T> start_pt {0, 0};
    }

    View(Matrix<T> &mat, const vector<unsigned> &start, const vector<unsigned> &shape):
    target(&mat), start_pt(start), shape(shape)
    {}

    typename vector<T>::iterator index(unsigned i, unsigned j)
    {
        auto ptr = target->index(start_pt[0] + i, start_pt[1] + j);
        return ptr;
    }
};


template<class T>
void print(const Matrix<T> &mat)
{// helper func for printing matrix. only support 2d matrices for now
    auto iter = mat.data.begin();
    
    auto col_iter = mat.shape.rbegin();
    auto row_iter = mat.shape.rbegin() + 1;

    for(size_t i = 0; i < *row_iter; i++)
    {
        for(size_t j = 0; j < *col_iter; j++)
            {
            cout << *iter << "\t";    
            iter++;
        }
        cout << endl;
    }
  
}

template<class T>
Matrix<T> mul_classic(const Matrix<T> &m1, const Matrix<T> &m2)
{
    // compute shape of result matrix and initialize data as empty vector
    vector<unsigned> shape = m1.shape;
    auto len_iter = shape.back();
    shape.pop_back();
    shape.insert(shape.end(), m2.shape.begin() + 1, m2.shape.end());
 
    unsigned n_elt = 1;
    for(auto &dim:shape)
    {
        n_elt *= dim;
    }
    vector<T> data(n_elt, 0.0);

    // compute multiplication result iterating through elts
    unsigned col_idx = 0;
    unsigned row_idx = 0;
    unsigned num_col = shape.back();
    
    for(auto &elt : data)
    {
        
        for(size_t i = 0; i < len_iter; i++)
        {
            elt += m1.data[row_idx * len_iter + i] * m2.data[num_col * i + col_idx];
        }
        
        col_idx++;
        if (col_idx == num_col)
        {
            row_idx++;
            col_idx = 0;
        }
    }
    Matrix<T> result(data, shape);
    return result;
}

template<class T>
Matrix<T>& mul_strassen(Matrix<T> &m1, Matrix<T> &m2)
{
    // compute shape of result matrix and initialize data as empty vector
    vector<unsigned> shape = m1.shape;
    auto len_iter = shape.back();
    shape.pop_back();
    shape.insert(shape.end(), m2.shape.begin() + 1, m2.shape.end());
 
    unsigned n_elt = 1;
    for(auto &dim:shape)
    {
        n_elt *= dim;
    }
    vector<T> data(n_elt, 0.0);
}

template<class iterator>
void core_strassen(iterator target, iterator m1, iterator m2, unsigned n)
{
    cout << *m1 << endl;
    if (n <= 2)
    {
        // TODO: classical mult.
    }
    // TODO: recursive call

    // return *m1;
}
