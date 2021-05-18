#include "../include/big_int.hpp"

// for debuging
#include <iostream>

namespace bigint {

// SECTION Constructor.

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

// String value constructor.
BigInt::BigInt(const std::string str__)
    : _bigInt(str__)
    , _signed(str__[0] == '-')
{
    if (this->_getSign())
        this->_bigInt.erase(0, 1);
}

// Copy constructor.
BigInt::BigInt(const BigInt& r__)
    : _bigInt(r__._bigInt)
    , _signed(r__._getSign())
{
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

// SECTION Private member functions.

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

/**
 * @brief Converts a integer digit to a charecter
 * 
 * @param val__ integer digit
 * @return char digit in charecter
 */
char BigInt::_getDigitCh(const short val__)
{
    return ('0' + val__);
}

/**
 * @brief Returns the digit at a position of a BigInt Object.
 * 
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

/**
 * @brief [TODO]
 * 
 * @param bi__ BigInt 
 * @param bi_arr__ Array of products.
 * @return size_t 
 */
size_t BigInt::_binarySearch(BigInt bi__, std::vector<BigInt> bi_arr__)
{
    int hi = 9, lo = 0, mid, index = 0;

    while (hi >= lo) {
        mid = lo + (hi - lo) / 2;

        if (bi_arr__[mid] > bi__)
            hi = mid - 1;

        else if (bi_arr__[mid] < bi__) {
            index = mid;
            lo = mid + 1;
        }

        else
            return mid;
    }

    return index;
}

// SECTION I/O operators

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

// SECTION Comparision operator.

bool BigInt::operator>(BigInt r__)
{
    if (!this->_getSign() && !r__._getSign())
        return (this->_bigInt > r__._bigInt);
    if (this->_getSign() && r__._getSign())
        return (this->_bigInt < r__._bigInt);
    if (!this->_getSign() && r__._getSign())
        return true;
    return false;
}

bool BigInt::operator<(BigInt r__)
{
    if (!this->_getSign() && !r__._getSign())
        return (this->_bigInt < r__._bigInt);
    if (this->_getSign() && r__._getSign())
        return (this->_bigInt > r__._bigInt);
    if (this->_getSign() && !r__._getSign())
        return true;
    return false;
}

bool BigInt::operator==(BigInt r__)
{
    return (this->_bigInt == r__._bigInt && !(this->_getSign() ^ r__._getSign()));
}

bool BigInt::operator<=(BigInt r__)
{
    return (*this < r__ || *this == r__);
}

bool BigInt::operator>=(BigInt r__)
{
    return (*this > r__ || *this == r__);
}

// SECTION : Addition

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
        carry = digit / 10;
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
    while (this->_bigInt[0] == '0' && this->size() > 1)
        this->_bigInt.erase(0, 1);
    return *this;
}

// SECTION Multiplication

BigInt& BigInt::operator*=(BigInt r__)
{
    size_t i = 0, len = r__.size();
    BigInt sum, temp = *this;
    std::vector<BigInt> product(len);

    this->reverse();
    r__.reverse();

    for (; i < len; i++) {

        short int carry = 0;

        size_t digit;
        std::string s(i, '0');
        product[i] = s;

        for (size_t j = 0; j < this->size(); j++) {

            digit = this->_getDigit(j) * r__._getDigit(i) + carry;
            carry = digit / 10;
            digit %= 10;
            product[i]._bigInt.push_back(_getDigitCh(digit));
        }

        if (carry) {

            product[i]._bigInt.push_back(_getDigitCh(carry));
            carry = 0;
        }

        product[i].reverse();
        while (product[i]._bigInt[0] == '0' && product[i].size() > 1)
            product[i]._bigInt.erase(0, 1);
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

// SECTION Division

BigInt& BigInt::operator/=(BigInt r__)
{
    std::vector<BigInt> product(10);

    for (int i = 0; i <= 9; i++) {
        product[i] = r__ * i;
    }

    BigInt remender = "\0", quotient = "\0", temp = *this;
    size_t len = 0, index = 0;

    for (size_t i = 0; i <= this->size(); i++) {

        if (len < r__.size()) {

            quotient._bigInt.push_back(_getDigitCh(0));
            remender._bigInt.push_back(_getDigitCh(this->_getDigit(i)));
            len++;
            continue;
        }

        index = _binarySearch(remender, product);
        remender -= product[index];
        quotient._bigInt.push_back(_getDigitCh(index));
        remender._bigInt.push_back(_getDigitCh(this->_getDigit(i)));
        len = remender.size();
    }
    *this = quotient;
    this->_setSign(temp._getSign() ^ r__._getSign());
    while (this->_bigInt[0] == '0' && this->size() > 1)
        this->_bigInt.erase(0, 1);
    return *this;
}

BigInt operator/(BigInt l__, BigInt r__)
{
    l__ /= r__;
    return l__;
}

// SECTION Public Methods

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

// Revese a BigInt object.
BigInt& BigInt::reverse()
{
    std::reverse(this->_bigInt.begin(), this->_bigInt.end());
    return *this;
}

void BigInt::reverse(BigInt& bi__)
{
    bi__.reverse();
    while (bi__._bigInt[0] == '0' && bi__.size() > 1)
        bi__._bigInt.erase(0, 1);
}
// Destructor
BigInt::~BigInt() { }
}
