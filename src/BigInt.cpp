#include "../include/BigInt.hpp"
// for debuging
#include <iostream>

BigInt::BigInt(void) : BigInt("0") { this->_signed = false; }

BigInt::BigInt(const char *ch) : big_int(ch)
{
    if (this->big_int[0] == '-') {
        this->_signed = true;
        this->big_int.erase(0, 1);
    }
    else
        this->_signed = false;
}

BigInt &BigInt::operator-()
{
    this->_signed = this->_signed ^ 1;
    return *this;
}

BigInt::BigInt(const BigInt &_bigInt)
{
    this->big_int = _bigInt.big_int;
    this->_signed = _bigInt.getSign();
}

BigInt &BigInt::operator=(const BigInt lhs)
{
    big_int = lhs.big_int;
    return *this;
}

size_t BigInt::size() const { return this->big_int.size(); }

size_t BigInt::getDigit(const size_t _pos) const
{
    return (this->big_int[_pos] - '0');
}

void BigInt::setDigit(const size_t _pos, const size_t _val)
{
    this->big_int[_pos] = ('0' + _val);
}

bool BigInt::getSign() const { return this->_signed; }

std::ostream &operator<<(std::ostream &out, const BigInt &output)
{
    if (output.getSign())
        out << "-";
    out << output.big_int;
    return out;
}

std::istream &operator>>(std::istream &in, BigInt &input)
{
    in >> input.big_int;
    return in;
}
// Note Addition
BigInt operator+(BigInt lhs, BigInt rhs)
{
    lhs += rhs;
    return lhs;
}

BigInt &BigInt::operator+=(BigInt rhs)
{
    if (rhs.getSign()) {
        *this -= rhs;
        return *this;
    }
    if (this->size() < rhs.size())
        std::swap(*this, rhs);
    std::reverse(rhs.big_int.begin(), rhs.big_int.end());
    std::reverse(big_int.begin(), big_int.end());
    size_t len = std::min(rhs.size(), this->size());
    size_t iterator = 0, carry = 0, digit = 0;
    for (; iterator <= len - 1; iterator += 1) {
        digit = rhs.getDigit(iterator) + this->getDigit(iterator) + carry;
        carry = digit / 10;
        digit %= 10;
        this->setDigit(iterator, digit);
    }
    while (carry && this->size() > iterator) {
        digit = this->getDigit(iterator) + carry;
        carry = int(digit / 10);
        digit %= 10;
        this->setDigit(iterator, digit);
        iterator += 1;
    }
    if (carry)
        this->big_int.push_back(('0' + carry));
    std::reverse(this->big_int.begin(), this->big_int.end());
    return *this;
}
// Note Substaction
BigInt operator-(BigInt lhs, BigInt rhs)
{
    lhs -= rhs;
    return lhs;
}

BigInt &BigInt::operator-=(BigInt rhs)
{
    if (rhs.getSign()) {
        *this += rhs;
        return *this;
    }
    if (this->size() < rhs.size()) {
        std::swap(*this, rhs);
        this->_signed = true;
    }
    else if (this->size() == rhs.size()) {
        if (this->getDigit(0) < rhs.getDigit(0)) {
            std::swap(*this, rhs);
            this->_signed = true;
        }
    }
    std::reverse(this->big_int.begin(), this->big_int.end());
    std::reverse(rhs.big_int.begin(), rhs.big_int.end());
    size_t len = std::min(this->size(), rhs.size());
    size_t borrow = 0, iterator = 0;
    signed short digit = 0;
    for (; iterator <= len - 1; iterator += 1) {
        digit = this->getDigit(iterator) - rhs.getDigit(iterator);
        if (digit < 0) {
            borrow = 10;
            size_t it = iterator + 1;
            while (it < this->size()) {
                size_t newDigit = this->getDigit(it) - 1;
                if (newDigit > 0) {
                    this->setDigit(it, newDigit);
                    break;
                }
                else {
                    this->setDigit(it, 9);
                }
                it++;
            }
            if (it == this->size()) {
                this->big_int.pop_back();
            }
        }
        digit += borrow;
        this->setDigit(iterator, digit);
        borrow = 0;
    }
    std::reverse(this->big_int.begin(), this->big_int.end());
    return *this;
}

BigInt::~BigInt() {}
