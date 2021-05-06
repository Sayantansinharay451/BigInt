#pragma once

#include <algorithm>
#include <string>

#define BIG_INT(X) #X

class BigInt {

  private:
    std::string big_int;

    bool _signed;

    size_t getDigit(const size_t) const;

    void setDigit(const size_t, const size_t);

    bool getSign() const;

  public:
    BigInt(void);

    BigInt(const char *);

    BigInt(const BigInt &);

    BigInt &operator=(const BigInt);

    friend std::ostream &operator<<(std::ostream &, const BigInt &);

    friend std::istream &operator>>(std::istream &, BigInt &);

    size_t size() const;

    BigInt &operator-();

    BigInt &operator+=(BigInt);

    BigInt &operator-=(BigInt);
    // TODO operator* && operator/ //
    BigInt &operator*=(BigInt);

    BigInt &operator/=(BigInt);

    friend BigInt operator+(BigInt, BigInt);

    friend BigInt operator-(BigInt, BigInt);

    friend BigInt operator*(BigInt, BigInt);

    friend BigInt operator/(BigInt, BigInt);

    ~BigInt();
};