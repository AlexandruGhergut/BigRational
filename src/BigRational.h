#ifndef BIG_RATIONAL
#define BIG_RATIONAL

#include "BigInteger.h"

template <class T = int>
class BigRational
{
    BigInteger<T> numerator;
    BigInteger<T> denominator;

public:
    BigRational()
    {
        numerator = "0";
        denominator = "1";
    }

    BigRational(BigInteger<T> a, BigInteger<T> b)
    {
        numerator = a;
        denominator = b;
    }

    BigRational(const char *a, const char *b)
    {
        numerator = BigInteger<T>(a);
        denominator = BigInteger<T>(b);
    }

    BigRational operator*(BigRational<T> const &rhs)
    {
        BigRational result;
        result.numerator = numerator * rhs.numerator;
        result.denominator = denominator * rhs.denominator;
        return result;
    }

    BigRational operator+(BigRational<T> const &rhs)
    {
        BigRational result;
        BigInteger<T> LCM = (denominator * rhs.denominator) / BigInteger<T>::getGCD(denominator, rhs.denominator);
        result.denominator = LCM;
        BigInteger<T> a = numerator * (LCM / denominator);
        BigInteger<T> b = rhs.numerator * (LCM / rhs.denominator);
        result.numerator = numerator * (LCM / denominator) + rhs.numerator * (LCM / rhs.denominator);
        return result;
    }

    template <class U>
    friend ostream & operator<<(ostream &out, const BigRational<U> &x)
    {
        out << x.numerator << " / " << x.denominator;
        return out;
    }

    template <class U>
    friend istream & operator>>(istream &in, BigRational<U> &x)
    {
        in >> x.numerator >> x.denominator;
        if (x.denominator == "0")
            x.denominator = "1";
        return in;
    }

    BigInteger<T> getGCD()
    {
        return BigInteger<T>::getGCD(numerator, denominator);
    }

    void reduce()
    {
        BigInteger<T> GCD = getGCD();

        numerator = numerator / GCD;
        denominator = denominator / GCD;
    }
};

#endif // BIG_RATIONAL

