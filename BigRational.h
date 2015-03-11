#ifndef BIG_RATIONAL
#define BIG_RATIONAL

#include "BigInteger.h"

// TO DO
class BigRational
{
    BigInteger numerator;
    BigInteger denominator;

public:
    BigRational operator*(BigRational const &rhs);
    BigRational operator+(BigRational const &rhs);
};

#endif // BIG_RATIONAL
