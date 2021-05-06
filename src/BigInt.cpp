#include "../include/BigInt.hpp"
#include <iostream>
BigInt::BigInt(void) : BigInt("") {}

BigInt::BigInt(const char *ch) : big_int(ch) {}

size_t BigInt::size() const { return this->big_int.size(); }

void BigInt::operator=(const BigInt lhs) { big_int = lhs.big_int; }

BigInt &BigInt::operator+=(BigInt rhs)
{
    if (this->size() < rhs.size())
        std::swap(*this, rhs);
    std::reverse(rhs.big_int.begin(), rhs.big_int.end());
    std::reverse(big_int.begin(), big_int.end());
    size_t length = std::min(rhs.size(), this->size());
    size_t iterator = 0, carry = 0, digit = 0;
    for (; iterator <= length - 1; iterator += 1) {
        digit = (rhs.big_int[iterator] - '0') +
                (this->big_int[iterator] - '0') + carry;
        carry = digit / 10;
        digit %= 10;
        this->big_int[iterator] = ('0' + digit);
    }
    while (carry && this->size() > iterator) {
        digit = (this->big_int[iterator] - '0') + carry;
        carry = int(digit / 10);
        digit %= 10;
        this->big_int[iterator] = ('0' + digit);
        iterator += 1;
    }
    if (carry)
        this->big_int.push_back(('0' + carry));
    std::reverse(this->big_int.begin(), this->big_int.end());
    return *this;
}

BigInt operator+(BigInt lhs, BigInt rhs)
{
    lhs += rhs;
    return lhs;
}

std::ostream &operator<<(std::ostream &out, const BigInt &output)
{
    out << output.big_int;
    return out;
}

std::istream &operator>>(std::istream &in, BigInt &input)
{
    in >> input.big_int;
    return in;
}

BigInt::~BigInt() {}
