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
    BigRational result;
    BigInteger GCD = BigInteger::getGCD(denominator, rhs.denominator);
    BigInteger LCM = (denominator * rhs.denominator) / GCD;
    BigInteger test = rhs.denominator;
    result.denominator = LCM;
    result.numerator = numerator * (LCM / denominator) + rhs.numerator * (LCM / rhs.denominator);
    return result;
}

ostream & operator<<(ostream &out,const BigRational &x)
{
    out << x.numerator << "/" << x.denominator;
}

istream & operator>>(istream &in, BigRational &x)
{
    in >> x.numerator >> x.denominator;
}

BigInteger BigRational::getGCD()
{
    return BigInteger::getGCD(numerator, denominator);
}
