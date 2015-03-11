#ifndef BIG_RATIONAL
#define BIG_RATIONAL

#include "BigInteger.h"

class BigRational
{
    BigInteger numerator;
    BigInteger denominator;

public:
    BigRational();
    BigRational(BigInteger a, BigInteger b);
    BigRational(const char *a, const char *b);
    BigRational operator*(BigRational const &rhs);
    BigRational operator+(BigRational const &rhs);
    friend ostream & operator<<(ostream &out, const BigRational &x);
    friend istream & operator>>(istream &in, BigRational &x);
    BigInteger getGCD();
    void reduce();
};

#endif // BIG_RATIONAL
