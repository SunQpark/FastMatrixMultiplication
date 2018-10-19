#pragma once
#include<vector>
#include<chrono>
#include"matrix.hpp"
#include"mm_classic.hpp"
#include"mm_strassen.hpp"
#include"test_tools.hpp"


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

    cout << endl;
}

void test_random_init()
{
    unsigned seed = 123;
    auto rm1 = random_mat_double(4, 0.0, 1.0, seed);
    auto rm2 = random_mat_int(4, 0, 10, seed);
    
    print(rm1);
    print(rm2);
}

pair<double, double> test_comparison_double(unsigned size, unsigned num_experiments)
{
    //initializes chrono for measurement of time
    using clock = chrono::steady_clock;
    chrono::time_point<clock> start;
    chrono::duration<double> duration;

    double total_time_classical = 0.0;
    double total_time_strassen = 0.0;

    Matrix<double> m1(size);
    Matrix<double> m2(size);
    Matrix<double> result_cls(size);
    Matrix<double> result_str(size);

    for(unsigned ex_index = 0; ex_index < num_experiments; ex_index++)
    {
        // use experiment_indices as seed for generating matrices
        unsigned seed = ex_index;
        m1 = random_mat_double(size, 0.0, 2.0, seed);
        m2 = random_mat_double(size, 0.0, 2.0, seed+1);
        
        //measure time: classical matmul
        start = clock::now();
        result_cls = mm_classic(m1, m2);
        duration = clock::now() - start;
        total_time_classical += duration.count();

        //measure time: strassen's matmul
        start = clock::now();
        result_str = mm_strassen(m1, m2);
        duration = clock::now() - start;
        total_time_strassen += duration.count();
    }
    return pair<double, double>(total_time_classical/num_experiments, total_time_strassen/num_experiments);
}