#include "../include/BigInt.hpp"
#include <iostream>

int main(int argc, char *argv[])
{

    //! FIX
    BigInt i = BIG_INT(10);
    BigInt j = BIG_INT(6);
    BigInt k = BIG_INT(67);
    BigInt h = i + (j - k);
    std::cout << -h << std::endl;
    return 0;
}
