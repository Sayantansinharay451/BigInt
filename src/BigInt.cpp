#include "../include/BigInt.hpp"
// for debuging
#include <iostream>

/// Constructor.
// Default constructor.
BigInt::BigInt()
    : BigInt("0")
{
    this->_signed = false;
}

// Charecter array constructor.
BigInt::BigInt(const char* __ch)
    : _bigInt(__ch)
{
    if (this->_bigInt[0] == '-') {
        this->_setSign(true);
        this->_bigInt.erase(0, 1);
    }
    else
        this->_setSign(false);
}

// Integer value costructor.
BigInt::BigInt(const intmax_t val__)
    : _bigInt(std::to_string(abs(val__)))
{
    if (val__ < 0)
        this->_setSign(true);
    else
        this->_setSign(false);
}

// Copy constructor.
BigInt::BigInt(const BigInt& r__)
{
    this->_bigInt = r__._bigInt;
    this->_signed = r__._getSign();
}

// Assignment operator.
BigInt& BigInt::operator=(const BigInt r__)
{
    this->_bigInt = r__._bigInt;
    this->_setSign(r__._getSign());
    return *this;
}
// Negation operator.
BigInt& BigInt::operator-()
{
    this->_signed = this->_signed ^ 1;
    return *this;
}

///Private member functions.
/**
 * @brief Sets a digit at a position of Bigint Object.
 * 
 * @param pos__ Position (0 - base indexing) of the BigInt Object.
 * @param val__ Digit to be inserted.
 */
void BigInt::_setDigit(const size_t pos__, const short val__)
{
    this->_bigInt[pos__] = ('0' + val__);
}

/**
 * @brief Returns the digit at a position of a BigInt Object.
 * @param pos__ Position (0 - base indexing) of the  
 */
size_t BigInt::_getDigit(const size_t pos__) const
{
    return (this->_bigInt[pos__] - '0');
}

/**
 * @brief Sets the value of BigInt Object negative or positive.
 * 
 * @param sign__ set True to make the value Negative.
 */
void BigInt::_setSign(bool sign__) { this->_signed = sign__; }

/**
 * @brief Returns True if a Number is negative.
 * 
 * @return true 
 * @return false 
 */
bool BigInt::_getSign() const { return this->_signed; }

/// I/O operators
std::ostream& operator<<(std::ostream& out, const BigInt& o__)
{
    if (o__._getSign())
        out << "-";
    out << o__._bigInt;
    return out;
}

std::istream& operator>>(std::istream& in, BigInt& i__)
{
    in >> i__._bigInt;
    return in;
}

//SECTION : Addition

BigInt operator+(BigInt l__, BigInt r__)
{
    l__ += r__;
    return l__;
}

BigInt& BigInt::operator+=(BigInt r__)
{
    if (this->_getSign())
        swap(*this, r__);
    if (r__._getSign()) {
        r__._setSign(false);
        *this -= r__;
        return *this;
    }
    if (this->size() < r__.size())
        swap(*this, r__);
    std::reverse(r__._bigInt.begin(), r__._bigInt.end());
    std::reverse(_bigInt.begin(), _bigInt.end());
    size_t len = std::min(r__.size(), this->size());
    size_t iterator = 0, carry = 0, digit = 0;
    for (; iterator <= len - 1; iterator += 1) {
        digit = r__._getDigit(iterator) + this->_getDigit(iterator) + carry;
        carry = digit / 10;
        digit %= 10;
        this->_setDigit(iterator, digit);
    }
    while (carry && this->size() > iterator) {
        digit = this->_getDigit(iterator) + carry;
        carry = int(digit / 10);
        digit %= 10;
        this->_setDigit(iterator, digit);
        iterator += 1;
    }
    if (carry)
        this->_bigInt.push_back(('0' + carry));
    std::reverse(this->_bigInt.begin(), this->_bigInt.end());
    return *this;
}

BigInt& BigInt::operator+=(intmax_t r__)
{
    BigInt rhs = r__;
    *this += rhs;
    return *this;
}

BigInt operator+(BigInt l__, intmax_t r__)
{
    l__ += r__;
    return l__;
}

// SECTION: Substaction
BigInt
operator-(BigInt l__, BigInt r__)
{
    l__ -= r__;
    return l__;
}

BigInt& BigInt::operator-=(BigInt r__)
{
    if (r__._getSign()) {
        *this += r__;
        return *this;
    }
    if (this->size() < r__.size()) {
        swap(*this, r__);
        this->_setSign(true);
    }
    else if (this->size() == r__.size()) {
        if (this->_getDigit(0) < r__._getDigit(0)) {
            swap(*this, r__);
            this->_setSign(true);
        }
    }
    std::reverse(this->_bigInt.begin(), this->_bigInt.end());
    std::reverse(r__._bigInt.begin(), r__._bigInt.end());
    size_t len = std::min(this->size(), r__.size());
    size_t borrow = 0, iterator = 0;
    signed short digit = 0;
    for (; iterator <= len - 1; iterator += 1) {
        digit = this->_getDigit(iterator) - r__._getDigit(iterator);
        if (digit < 0) {
            borrow = 10;
            size_t it = iterator + 1;
            while (it < this->size()) {
                short newDigit = this->_getDigit(it) - 1;
                if (newDigit >= 0) {
                    this->_setDigit(it, newDigit);
                    break;
                }
                else {
                    this->_setDigit(it, 9);
                }
                it++;
            }
            if (this->_bigInt[this->size() - 1] == '0') {
                this->_bigInt.pop_back();
            }
        }
        digit += borrow;
        this->_setDigit(iterator, digit);
        borrow = 0;
    }
    std::reverse(this->_bigInt.begin(), this->_bigInt.end());
    return *this;
}

BigInt& BigInt::operator-=(intmax_t r__)
{
    BigInt rhs = r__;
    *this -= rhs;
    return *this;
}

BigInt operator-(BigInt l__, intmax_t r__)
{
    l__ -= r__;
    return l__;
}

// Returns the size of BigInt Object.
size_t BigInt::size() const { return this->_bigInt.size(); }

// Swaps the BigInt values.
void BigInt::swap(BigInt& l__, BigInt& r__)
{
    BigInt temp = l__;
    l__ = r__;
    r__ = temp;
}

BigInt::~BigInt() { }
