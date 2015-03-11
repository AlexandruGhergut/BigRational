#include "BigRational.h"

BigRational BigRational::operator*(BigRational const &rhs)
{
    BigRational result;
    result.numerator = numerator * rhs.numerator;
    result.denominator = denominator * rhs.denominator;
    return result;
}

BigRational BigRational::operator+(BigRational const &rhs)
{
    // TO DO
    BigRational result;
    BigInteger GCD = BigInteger::getGCD(denominator, rhs.denominator);
    BigInteger LCM = (denominator * rhs.denominator) / GCD;
    BigInteger test = rhs.denominator;
    result.denominator = LCM;
    result.numerator = numerator * (LCM / denominator) + rhs.numerator * (LCM / rhs.denominator);
}
