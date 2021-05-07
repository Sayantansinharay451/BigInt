#include "../include/BigInt.hpp"
// for debuging
#include <iostream>

BigInt::BigInt(void)
    : BigInt("0")
{
    this->_signed = false;
}

BigInt::BigInt(const char* ch)
    : big_int(ch)
{
    if (this->big_int[0] == '-') {
        this->setSign(true);
        this->big_int.erase(0, 1);
    }
    else
        this->setSign(false);
}

BigInt::BigInt(const BigInt& _bigInt)
{
    this->big_int = _bigInt.big_int;
    this->_signed = _bigInt.getSign();
}

BigInt::BigInt(const intmax_t __val)
    : big_int(std::to_string(abs(__val)))
{
    if (__val < 0)
        this->setSign(true);
    else
        this->setSign(false);
}

void BigInt::swap(BigInt& __l, BigInt& __r)
{
    BigInt temp = __l;
    __l = __r;
    __r = temp;
}

BigInt& BigInt::operator-()
{
    this->_signed = this->_signed ^ 1;
    return *this;
}

BigInt& BigInt::operator=(const BigInt __lhs)
{
    this->big_int = __lhs.big_int;
    this->setSign(__lhs.getSign());
    return *this;
}

size_t BigInt::size() const { return this->big_int.size(); }

size_t BigInt::getDigit(const size_t __pos) const
{
    return (this->big_int[__pos] - '0');
}

void BigInt::setDigit(const size_t __pos, const short __val)
{
    this->big_int[__pos] = ('0' + __val);
}

bool BigInt::getSign() const { return this->_signed; }

void BigInt::setSign(bool _sign) { this->_signed = _sign; }

std::ostream& operator<<(std::ostream& out, const BigInt& output)
{
    if (output.getSign())
        out << "-";
    out << output.big_int;
    return out;
}

std::istream& operator>>(std::istream& in, BigInt& input)
{
    in >> input.big_int;
    return in;
}
// Note Addition
BigInt operator+(BigInt __lhs, BigInt __rhs)
{
    __lhs += __rhs;
    return __lhs;
}

BigInt& BigInt::operator+=(BigInt __rhs)
{
    if (this->getSign())
        swap(*this, __rhs);
    if (__rhs.getSign()) {
        __rhs.setSign(false);
        *this -= __rhs;
        return *this;
    }
    if (this->size() < __rhs.size())
        swap(*this, __rhs);
    std::reverse(__rhs.big_int.begin(), __rhs.big_int.end());
    std::reverse(big_int.begin(), big_int.end());
    size_t len = std::min(__rhs.size(), this->size());
    size_t iterator = 0, carry = 0, digit = 0;
    for (; iterator <= len - 1; iterator += 1) {
        digit = __rhs.getDigit(iterator) + this->getDigit(iterator) + carry;
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

BigInt& BigInt::operator+=(intmax_t __rhs)
{
    BigInt rhs = __rhs;
    *this += rhs;
    return *this;
}

BigInt operator+(BigInt __lhs, intmax_t __rhs)
{
    __lhs += __rhs;
    return __lhs;
}

// Note: Substaction
BigInt
operator-(BigInt __lhs, BigInt __rhs)
{
    __lhs -= __rhs;
    return __lhs;
}

BigInt& BigInt::operator-=(BigInt __rhs)
{
    if (__rhs.getSign()) {
        *this += __rhs;
        return *this;
    }
    if (this->size() < __rhs.size()) {
        swap(*this, __rhs);
        this->setSign(true);
    }
    else if (this->size() == __rhs.size()) {
        if (this->getDigit(0) < __rhs.getDigit(0)) {
            swap(*this, __rhs);
            this->setSign(true);
        }
    }
    std::reverse(this->big_int.begin(), this->big_int.end());
    std::reverse(__rhs.big_int.begin(), __rhs.big_int.end());
    size_t len = std::min(this->size(), __rhs.size());
    size_t borrow = 0, iterator = 0;
    signed short digit = 0;
    for (; iterator <= len - 1; iterator += 1) {
        digit = this->getDigit(iterator) - __rhs.getDigit(iterator);
        if (digit < 0) {
            borrow = 10;
            size_t it = iterator + 1;
            while (it < this->size()) {
                short newDigit = this->getDigit(it) - 1;
                if (newDigit >= 0) {
                    this->setDigit(it, newDigit);
                    break;
                }
                else {
                    this->setDigit(it, 9);
                }
                it++;
            }
            if (this->big_int[this->size() - 1] == '0') {
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

BigInt& BigInt::operator-=(intmax_t __rhs)
{
    BigInt rhs = __rhs;
    *this -= rhs;
    return *this;
}

BigInt operator-(BigInt __lhs, intmax_t __rhs)
{
    __lhs -= __rhs;
    return __lhs;
}

BigInt::~BigInt() { }
