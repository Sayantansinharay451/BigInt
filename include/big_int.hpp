#pragma once

/**======================
 *    Header Files
 *========================**/
#include <algorithm>
#include <string>

/**----------------------
 *    Basic defines
 *------------------------**/
#define BIG_INT(X) #X

/**============================================
 *               Class Definations
 *=============================================**/
class big_int {
  private:
    std::string Big_int;

  public:
    big_int(void);
    big_int(const char *);
    void operator=(const big_int _big_int);
    big_int &operator+(const big_int _big_int) const;
    ~big_int();
};