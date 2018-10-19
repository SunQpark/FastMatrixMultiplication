#pragma once
#include<vector>
#include<chrono>
#include"matrix.hpp"
#include"mm_classic.hpp"
#include"mm_strassen.hpp"


using namespace std;
using scalar = double;


void test_addition()
{
    vector<scalar> data1 {1.0, 2.0, 3.0, 4.0};
    vector<scalar> data2 {2.0, 4.0, 4.0, 5.0};
    int_pair shape {2, 2};
    auto mat1 = Matrix<scalar>(data1, shape);
    auto mat2 = Matrix<scalar>(data2, shape);

    mat1 += mat2;
    print(mat1);
}

void test_classical()
{
    vector<scalar> data1 {
        1.0, 0.0, 3.0, 
        0.0, 5.0, 0.0, 
        0.0, 0.0, 9.0};
    vector<scalar> data2 {
        2.0, 4.0, 
        4.0, 0.0, 
        0.0, 7.0};
    int_pair shape1 {3, 3};
    int_pair shape2 {3, 2};
    auto mat1 = Matrix<scalar>(data1, shape1);
    auto mat2 = Matrix<scalar>(data2, shape2);
    print(mat1);
    print(mat2);
    auto mat3 = mm_classic(mat1, mat2);
    cout << endl;
    print(mat3);
    // cout << *mat3.index(1, 0) << endl;
}

void test_strassen()
{
    int_pair shape {4, 4};
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

    Matrix<scalar> mat1 (data1, shape);
    Matrix<scalar> mat2 (data2, shape);

    print(mat1);
    cout << endl;

    // print(mat2);
    // cout << endl;
    print(mm_classic(mat1, mat2));
    print(mm_strassen(mat1, mat2));

    cout <<endl;
}