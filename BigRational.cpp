#include "BigRational.h"

BigRational::BigRational()
{
    numerator = "0";
    denominator = "1";
}

BigRational::BigRational(BigInteger a, BigInteger b)
{
    numerator = a;
    denominator = b;
}

BigRational::BigRational(const char *a, const char *b)
{
    numerator = BigInteger(a);
    denominator = BigInteger(b);
}

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
    BigInteger LCM = (denominator * rhs.denominator) / BigInteger::getGCD(denominator, rhs.denominator);
    result.denominator = LCM;
    BigInteger a = numerator * (LCM / denominator);
    BigInteger b = rhs.numerator * (LCM / rhs.denominator);
    result.numerator = numerator * (LCM / denominator) + rhs.numerator * (LCM / rhs.denominator);
    return result;
}

ostream & operator<<(ostream &out,const BigRational &x)
{
    out << x.numerator << " / " << x.denominator;
    return out;
}

istream & operator>>(istream &in, BigRational &x)
{
    in >> x.numerator >> x.denominator;
    if (x.denominator == "0")
        x.denominator = "1";
    return in;
}

BigInteger BigRational::getGCD()
{
    return BigInteger::getGCD(numerator, denominator);
}

void BigRational::reduce()
{
    BigInteger GCD = getGCD();

    numerator = numerator / GCD;
    denominator = denominator / GCD;
}
