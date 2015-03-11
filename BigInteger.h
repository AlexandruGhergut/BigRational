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
    static int cmp(BigInteger const &lhs, BigInteger const &rhs);
    BigInteger processOp(BigInteger const &lhs, BigInteger const &rhs, bool inputOp);
    BigInteger add(BigInteger const &lhs, BigInteger const &rhs);
    BigInteger substract(BigInteger const &lhs, BigInteger const &rhs);

public:
    BigInteger();
    BigInteger(const char *x);
    BigInteger(BigInteger const &rhs);
    ~BigInteger();

    BigInteger operator+(BigInteger const &rhs);
    BigInteger operator+(const char *c);
    BigInteger operator-(BigInteger const &rhs);
    BigInteger operator-(const char *c);
    BigInteger operator*(BigInteger const &rhs) const; // TODO const?
    BigInteger operator*(const char *c) const;
    BigInteger operator=(BigInteger const &rhs);
    const char * operator=(const char *x);
    BigInteger operator+=(BigInteger const &rhs);
    BigInteger operator+=(const char *c);
    BigInteger operator-=(BigInteger const &rhs);
    BigInteger operator-=(const char *c);
    BigInteger operator*=(BigInteger const &rhs);
    BigInteger operator*=(const char *c);
    BigInteger operator++();
    BigInteger operator++(int x);
    BigInteger operator--();
    BigInteger operator--(int x);
    BigInteger operator/(BigInteger const &rhs);
    BigInteger operator/(const char *c);
    friend ostream & operator<< (ostream &out, const BigInteger &x);
    friend istream & operator>> (istream &in, BigInteger &x);
    static BigInteger getGCD(BigInteger lhs, BigInteger rhs);
};

#endif // BIG_INTEGER
