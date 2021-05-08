#include "../include/BigInt.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    std::string s(0, '0');
    std::cout << s << std::endl;
    BigInt i = BIG_INT(1);
    BigInt j = BIG_INT(484431389435613);
    BigInt k = BIG_INT(5);
    BigInt h = k - 8 + BIG_INT(1);
    std::cout << -h << std::endl;
    return 0;
}
