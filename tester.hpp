#pragma once
#include<vector>
#include"matrix.hpp"

using namespace std;
using scalar = double;


void test_addition()
{
    vector<scalar> data1 {1.0, 2.0, 3.0, 4.0};
    vector<scalar> data2 {2.0, 4.0, 4.0, 5.0};
    vector<unsigned> shape {2, 2};
    auto mat1 = Matrix<scalar>(data1, shape);
    auto mat2 = Matrix<scalar>(data2, shape);

    mat1 += mat2;
    print(mat1);
}

void test_multiplication()
{
    vector<scalar> data1 {
        1.0, 0.0, 3.0, 
        0.0, 5.0, 0.0, 
        0.0, 0.0, 9.0};
    vector<scalar> data2 {
        2.0, 4.0, 
        4.0, 0.0, 
        0.0, 7.0};
    vector<unsigned> shape1 {3, 3};
    vector<unsigned> shape2 {3, 2};
    auto mat1 = Matrix<scalar>(data1, shape1);
    auto mat2 = Matrix<scalar>(data2, shape2);
    print(mat1);
    print(mat2);
    auto mat3 = mul_classic(mat1, mat2);
    print(mat3);
    cout << *mat3.index(1, 0) << endl;
}

void test_strassen()
{
    vector<unsigned> shape {4, 4};
    vector<scalar> data1 {
        1.0, 0.0, 3.0, 4.0, 
        0.0, 5.0, 0.0, 0.0, 
        0.0, 5.0, 7.0, 0.0, 
        0.0, 0.0, 0.0, 1.0};
    vector<scalar> data2 {
        1.0, 0.0, 0.0, 0.0, 
        0.0, 5.0, 0.0, 0.0, 
        2.0, 5.0, 7.0, 0.0, 
        0.0, 0.0, 0.0, 1.0};
    // cout << data1.begin();
    Matrix<scalar> mat1 (data1, shape);
    cout << *mat1.index(2, 2);
    const vector<unsigned> st {1, 1};
    const vector<unsigned> sh {2, 2};
    print(mat1);
    auto v = View<scalar>(mat1, st, sh);
    cout << *(v.index(1, 0)) << endl;    
    // auto pt = View(mat1, mat1.shape);
    // cout << *(pt.start_point);
    
    // core_strassen(data1.begin(), data1.begin(), data2.begin(), 4);
}