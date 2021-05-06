#pragma once

#include <algorithm>
#include <string>

#define BIG_INT(X) #X

class BigInt {

  private:
    std::string big_int;

  public:
    BigInt(void);

    BigInt(const char *);

    void operator=(const BigInt);

    BigInt &operator+=(BigInt);

    size_t size() const;

    friend BigInt operator+(BigInt, BigInt);

    friend std::ostream &operator<<(std::ostream &, const BigInt &);

    friend std::istream &operator>>(std::istream &, BigInt &);

    ~BigInt();
};