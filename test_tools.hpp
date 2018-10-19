#pragma once
#include<random>
#include<functional>
#include"matrix.hpp"


using namespace std;

Matrix<double> random_mat_double(unsigned size, double lower, double upper, unsigned seed)
{
    // set random sampler. code ref: https://www.guyrutenberg.com/2014/05/03/c-mt19937-example/
    mt19937 mt_rand(seed);
    auto real_rand = std::bind(std::uniform_real_distribution<double>(lower, upper), mt19937(seed));
    
    // initialize matrix and fill data with random numbers
    Matrix<double> result(size);
    for(auto &e :result.data)
    {
        e = real_rand();
    }
    return result;
}

Matrix<int> random_mat_int(unsigned size, int lower, int upper, unsigned seed)
{
    // set random sampler. code ref: https://www.guyrutenberg.com/2014/05/03/c-mt19937-example/
    mt19937 mt_rand(seed);
    auto int_rand = std::bind(std::uniform_int_distribution<int>(lower, upper), mt19937(seed));
    
    // initialize matrix and fill data with random numbers
    Matrix<int> result(size);
    for(auto &e :result.data)
    {
        e = int_rand();
    }
    return result;
}