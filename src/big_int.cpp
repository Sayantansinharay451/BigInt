#include "include/big_int.hpp"

big_int::big_int(void) {}
big_int::big_int(const char *) : Big_int(std::string(Big_int)) {}
void big_int::operator=(const big_int _big_int) { Big_int = _big_int.Big_int; }
big_int &big_int::operator+(const big_int _big_int) const
{
    big_int _init_;
    std::reverse(_big_int.Big_int.begin(), _big_int.Big_int.end());
    std::reverse(Big_int.begin(), Big_int.end());
    long long int length = std::min(_big_int.Big_int.size(), Big_int.size());
    int carry = 0, i = 0, digit;
    for (; i <= length - 1; i++) {
        carry = 0;
        digit = (_big_int.Big_int[i] - '0') + (Big_int[i] - '0') + carry;
        carry = digit / 10;
        digit %= 10;
        _init_.Big_int += ('0' + digit);
    }
    big_int rest = _big_int;
    if (_big_int.Big_int.size() < Big_int.size()) {
        rest = Big_int;
    }
    while (carry) {
        if (rest.Big_int.size() > i)
            digit = (_big_int.Big_int[i] - '0');
        digit += carry;
        carry = digit / 10;
        digit %= 10;
        _init_.Big_int += ('0' + digit);
        i++;
    }
    reverse(_init_.Big_int.begin(), _init_.Big_int.end());
    return _init_;
}
big_int::~big_int() {}
