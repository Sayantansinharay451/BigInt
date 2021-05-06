#include "../include/BigInt.hpp"
#include <iostream>

int main(int argc, char *argv[])
{

    BigInt i = BIG_INT(99);
    BigInt j = BIG_INT(1);
    BigInt k = BIG_INT(9);
    BigInt c = i + j + k;
    j += k;
    BigInt p;
    std::cout << k << std::endl;
    std::cin >> p;
    k += p;
    std::cout << p << std::endl;
    std::cout << j << std::endl;
    std::cout << i << std::endl;
    std::cout << k << std::endl;
    std::cout << c << std::endl;
    return 0;
}
