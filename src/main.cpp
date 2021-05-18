#include "../include/big_int.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    bigint::BigInt j = -4525, k = 11, i = 9000;
    // bigint::BigInt::reverse(i);
    std::cout << (j > i) << std::endl;
    return 0;
}