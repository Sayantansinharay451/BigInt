/**
 * @file BigInt.hpp
 * @author Sayantan Sinharay (s.sinharay.coder451@gmail.com)
 * @brief A c++ header file to handel big integers 
 * @version 0.1
 * @date 2021-05-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <algorithm>
#include <stdint.h>
#include <string>
/**
 * @brief Macro to convert integer literals to string literals.
 * 
 * @param X__ Integer value.
 * @return const char*.
 *
 * @n The @a X__ is stringize.
 */
#define BIG_INT(X__) (#X__)
/**
 * @class BigInt BigInt.hpp 
 * @brief BigInt Class to handel Big Integer.
 * 
 * @tparam ch__ Charecter array.
 * @tparam val__ Integer value.
 * @tparam str__ String of Big Integer operations.
 * 
 * @n Only @c + and @c - operators avaliable now.
 */
class BigInt {
    /**TODO 
	 * -> *, /, % operators.
	 * -> Math fuctions - pow (_bigInt,_bigInt), factorial(_bigInt).
	 * -> Feature - take input from file.
	 * -> Write an exception handeling class. (err)
	 * */

    std::string _bigInt;
    /// tells the value is signed or not.
    bool _signed;

    /// SECTION Utility Funtions.

    void _setDigit(const size_t, const short);

    size_t _getDigit(const size_t) const;

    static char _getDigitCh(const short);

    void _setSign(bool);

    bool _getSign() const;

public:
    // SECTION Costructors
    /**
	 * @brief Default Constructor.
	 */
    BigInt(void);

    /**
	 * @brief Construct a new Big Int object from from a C-style charecter array.
	 * 
	 * @param ch__ Costant charecter array.
	 */
    BigInt(const char* ch__);

    /**
	 * @brief Construct a new Big Int object from from a Integer value.
	 * 
	 * @param val__ Integer value.
	 */
    BigInt(const intmax_t val__);

    /**
	 * @brief Copy Constructor.
	 * 
	 * @param r__ BigInt Object to be copied.
	 */
    BigInt(const BigInt& r__);

    /**
	 * @brief Construct a new Big Int object from a string.
	 * 
	 * @param str__ the BigInt in form of a string.
	 */
    BigInt(const std::string str__);

    /**
	 * @brief Assignment operator. 
	 * 
	 * @param r__ BigInt Object to assign.
	 * @return BigInt& 
	 */
    BigInt& operator=(const BigInt r__);

    // I/O operators
    /// Output stream for BigInt
    friend std::ostream& operator<<(std::ostream& out, const BigInt& o__);

    /// Input stream for BigInt
    friend std::istream& operator>>(std::istream& in, BigInt& i__);

    /**
	 * @brief Negation of a BigInt Object. 
	 * @n Makes the BigInt Object Negative if positive and vice-versa.
	 */
    BigInt& operator-();

    /// SECTION Addition

    /**
     * @brief Addition assignment operator.
	 * 
     * @param r__ BigInt Object.
     */
    BigInt& operator+=(BigInt r__);

    /**
	 * @brief Addition operator.
	 * 
	 * @param l__ left side value of the operator.
	 * @param r__  right side value of the operator.
	 */
    friend BigInt operator+(BigInt l__, BigInt r__);

    // SECTION Substraction

    /**
     * @brief Substraction assignment operator.
	 * 
     * @param r__ BigInt Object.
     */
    BigInt& operator-=(BigInt r__);

    /**
	 * @brief Substraction operator.
	 * 
	 * @param l__ left side value of the operator.
	 * @param r__  right side value of the operator.
	 */
    friend BigInt operator-(BigInt l__, BigInt r__);

    // SECTION Multiplication

    BigInt& operator*=(BigInt r__);

    friend BigInt operator*(BigInt l__, BigInt r__);

    /// TODO
    // BigInt& operator[](size_t r__);

    // BigInt& operator/=(BigInt r__);

    // friend BigInt operator*(BigInt, BigInt);

    // friend BigInt operator/(BigInt, BigInt);

    // SECTION Public methods

    /**
	 * @brief Swaps two BigInt objects.
	 */
    void
    swap(BigInt& l__, BigInt& r__);

    /**
	 * @brief Returns the size of the BigInt (1-based indexing)
	 */
    size_t size() const;

    void reverse();

    ~BigInt();
};
