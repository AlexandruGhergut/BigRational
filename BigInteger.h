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
    void printInteger(Node *current) const;
    static int cmp(int lhs, int rhs);
    static int cmp(Node *l1, Node *l2);
    static int cmp(BigInteger const &lhs, BigInteger const &rhs);
    BigInteger processOp(BigInteger const &lhs, BigInteger const &rhs, bool inputOp) const;
    BigInteger add(BigInteger const &lhs, BigInteger const &rhs) const;
    BigInteger substract(BigInteger const &lhs, BigInteger const &rhs) const;

public:
    BigInteger();
    BigInteger(const char *x);
    BigInteger(BigInteger const &rhs);
    ~BigInteger();

    BigInteger operator+(BigInteger const &rhs) const;
    BigInteger operator-(BigInteger const &rhs);
    BigInteger operator*(BigInteger const &rhs) const;
    BigInteger operator=(BigInteger const &rhs);
    BigInteger operator/(BigInteger const &rhs) const; // TODO const?
    const char * operator=(const char *x);
    friend ostream & operator << (ostream &out, const BigInteger &x);
    static BigInteger getGCD(BigInteger lhs, BigInteger rhs);
};

#endif // BIG_INTEGER
