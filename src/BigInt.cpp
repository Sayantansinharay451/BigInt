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
BigInt::BigInt(const char* ch__)
    : _bigInt(ch__)
    , _signed(ch__[0] == '-')
{
    if (this->_getSign())
        this->_bigInt.erase(0, 1);
}
// Integer value costructor.
BigInt::BigInt(const intmax_t val__)
    : _bigInt(std::to_string(abs(val__)))
    , _signed(val__ < 0)
{
}

// Copy constructor.
BigInt::BigInt(const BigInt& r__)
    : _bigInt(r__._bigInt)
    , _signed(r__._getSign())
{
}

// String value constructor.
BigInt::BigInt(const std::string str__)
    : _bigInt(str__)
    , _signed(str__[0] == '-')
{
    if (this->_getSign())
        this->_bigInt.erase(0, 1);
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
    this->_bigInt[pos__] = _getDigitCh(val__);
}

char BigInt::_getDigitCh(const short val__)
{
    return ('0' + val__);
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
    this->reverse();
    r__.reverse();
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
    this->reverse();
    return *this;
}

// SECTION: Substaction

BigInt operator-(BigInt l__, BigInt r__)
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
    this->reverse();
    r__.reverse();
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
    this->reverse();
    return *this;
}

// SECTION Multiplication

BigInt& BigInt::operator*=(BigInt r__)
{
    size_t i = 0, len = r__.size();
    BigInt sum, product[len], temp = *this;
    this->reverse();
    for (; i < len; i++) {
        short int carry = 0;
        size_t digit;
        std::string s(i, '0');
        product[i] = s;
        for (size_t j = 0; j < this->size(); j++) {
            carry = 0;
            digit = this->_getDigit(j) * r__._getDigit(i) + carry;
            carry = digit / 10;
            digit %= 10;
            product[i]._bigInt.push_back(_getDigitCh(digit));
        }
        if (carry)
            product[i]._bigInt.push_back(_getDigitCh(carry));
        product[i].reverse();
        sum += product[i];
    }
    *this = sum;
    this->_setSign(temp._getSign() ^ r__._getSign());
    return *this;
}

BigInt operator*(BigInt l__, BigInt r__)
{
    l__ *= r__;
    return l__;
}

// Returns the size of BigInt Object.
size_t BigInt::size() const
{
    return this->_bigInt.size();
}

// Swaps the BigInt values.
void BigInt::swap(BigInt& l__, BigInt& r__)
{
    BigInt temp = l__;
    l__ = r__;
    r__ = temp;
}

void BigInt::reverse()
{
    std::reverse(this->_bigInt.begin(), this->_bigInt.end());
}

BigInt::~BigInt() { }
