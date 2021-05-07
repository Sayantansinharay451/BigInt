#include "../include/BigInt.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    BigInt i = BIG_INT(1);
    BigInt j = BIG_INT(4845346843138943561318635154);
    BigInt k = BIG_INT(1000000000000000000000000000000000);
    BigInt h = k - i;
    std::cout << h << std::endl;
    return 0;
}
