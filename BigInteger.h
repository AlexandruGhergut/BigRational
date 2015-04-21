#ifndef BIG_INTEGER
#define BIG_INTEGER

#include "LinkedList.h"

#include <cstring>
#include <iostream>
using namespace std;

class BigInteger
{
    LinkedList *l;
    bool negative;

    bool computeSign(bool s1, bool s2) const;
    void printInteger(ostream &out, Node *current) const;
    static int cmp(int lhs, int rhs);
    static int cmp(Node *l1, Node *l2);
    static int cmp(const BigInteger &lhs, const BigInteger &rhs);
    BigInteger processOp(const BigInteger &lhs, const BigInteger &rhs, bool inputOp);
    BigInteger add(const BigInteger &lhs, const BigInteger &rhs);
    BigInteger substract(const BigInteger &lhs, const BigInteger &rhs);

public:
    BigInteger();
    BigInteger(const char *x);
    BigInteger(const BigInteger &rhs);
    ~BigInteger();

    BigInteger operator+(const BigInteger &rhs);
    BigInteger operator+(const char *c);
    BigInteger operator-(const BigInteger &rhs);
    BigInteger operator-(const char *c);
    BigInteger operator*(const BigInteger &rhs) const; // TODO const?
    BigInteger operator*(const char *c) const;
    BigInteger operator=(const BigInteger &rhs);
    const char * operator=(const char *x);
    BigInteger operator+=(const BigInteger &rhs);
    BigInteger operator+=(const char *c);
    BigInteger operator-=(const BigInteger &rhs);
    BigInteger operator-=(const char *c);
    BigInteger operator*=(const BigInteger &rhs);
    BigInteger operator*=(const char *c);
    BigInteger operator++();
    BigInteger operator++(int x);
    BigInteger operator--();
    BigInteger operator--(int x);
    BigInteger operator/(const BigInteger &rhs);
    BigInteger operator/(const char *c);
    BigInteger operator%(const BigInteger &rhs);
    BigInteger operator%(const char *c);
    BigInteger properDivision(const BigInteger &lhs, const BigInteger &rhs); // prototype
    BigInteger operator/=(const BigInteger &rhs);
    BigInteger operator/=(const char *c);
    BigInteger operator-();
    bool operator==(const BigInteger &rhs);
    bool operator!=(const BigInteger &rhs);
    bool operator<(const BigInteger &rhs);
    bool operator<=(const BigInteger &rhs);
    bool operator>(const BigInteger &rhs);
    bool operator>=(const BigInteger &rhs);
    friend ostream & operator<< (ostream &out, const BigInteger &x);
    friend istream & operator>> (istream &in, BigInteger &x);
    static BigInteger getGCD(BigInteger lhs, BigInteger rhs);
};

#endif // BIG_INTEGER
