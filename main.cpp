#include<iostream>
#include<vector>
#include"matrix.hpp"
#include"tester.hpp"


int main(){
    //experiment on matrices of size 16, repeat multiplication 10 times
    unsigned size = 64;
    auto result = test_comparison_double(size, 100);

    cout << "classical matmul: " << result.first << "\t" << "strassen's matmul: " << result.second << endl;
    return 0;
}

