#pragma once

#include <algorithm>
#include <stdint.h>
#include <string>

#define BIG_INT(X) #X

class BigInt {

private:
    std::string big_int;

    bool _signed;

    size_t getDigit(const size_t) const;

    void setDigit(const size_t, const short);

    bool getSign() const;

    void setSign(bool);

public:
    BigInt(void);

    BigInt(const char*);

    BigInt(const BigInt&);

    BigInt(const intmax_t);

    BigInt& operator=(const BigInt);

    friend std::ostream& operator<<(std::ostream&, const BigInt&);

    friend std::istream& operator>>(std::istream&, BigInt&);

    size_t size() const;

    BigInt& operator-();

    BigInt& operator+=(BigInt);

    BigInt& operator+=(intmax_t);

    BigInt& operator-=(BigInt);

    BigInt& operator-=(intmax_t);

    BigInt& operator*=(BigInt);
    // TODO operator* && operator/
    BigInt& operator/=(BigInt);

    friend BigInt operator+(BigInt, BigInt);

    friend BigInt operator+(BigInt, intmax_t);

    friend BigInt operator-(BigInt, BigInt);

    friend BigInt operator*(BigInt, BigInt);

    friend BigInt operator/(BigInt, BigInt);

    void swap(BigInt&, BigInt&);

    ~BigInt();
};