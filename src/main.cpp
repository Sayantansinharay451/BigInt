#include "../include/big_int.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    bigint::BigInt j = -4, k = 11, i = -90;
    std::cout << i / j << std::endl;
    return 0;
}