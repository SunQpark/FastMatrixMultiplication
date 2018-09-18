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
    vector<scalar> data1 {1.0, 0.0, 3.0, 0.0, 5.0, 0.0, 0.0, 0.0, 9.0};
    vector<scalar> data2 {2.0, 4.0, 4.0, 0.0, 0.0, 7.0};
    vector<unsigned> shape1 {3, 3};
    vector<unsigned> shape2 {3, 2};
    auto mat1 = Matrix<scalar>(data1, shape1);
    auto mat2 = Matrix<scalar>(data2, shape2);
    print(mat1);
    print(mat2);
    auto mat3 = mul_classic(mat1, mat2);
    print(mat3);
}