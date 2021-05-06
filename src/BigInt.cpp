#include "../include/BigInt.hpp"

BigInt::BigInt(void) : BigInt("") {}

BigInt::BigInt(const char *ch) : big_int(ch) {}

BigInt::BigInt(const BigInt &_bigInt) { this->big_int = _bigInt.big_int; }

size_t BigInt::size() const { return this->big_int.size(); }

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

BigInt &BigInt::operator=(const BigInt lhs)
{
    big_int = lhs.big_int;
    return *this;
}

BigInt &BigInt::operator+=(BigInt lhs)
{
    if (this->size() < lhs.size())
        std::swap(*this, lhs);
    std::reverse(lhs.big_int.begin(), lhs.big_int.end());
    std::reverse(big_int.begin(), big_int.end());
    size_t length = std::min(lhs.size(), this->size());
    size_t iterator = 0, carry = 0, digit = 0;
    for (; iterator <= length - 1; iterator += 1) {
        digit = (lhs.big_int[iterator] - '0') +
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

BigInt::~BigInt() {}
