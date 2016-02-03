#ifndef BIG_INTEGER
#define BIG_INTEGER

#include "LinkedList.h"

#include <cstring>
#include <iostream>
using namespace std;

template <class T = int>
class BigInteger
{
protected:
    LinkedList<T> *l;
    bool negative;

    bool computeSign(bool s1, bool s2) const
    {
        if (s1 != s2)
            return true;
        return false;
    }

    void printInteger(ostream &out, Node<T> *current) const
    {
        if (current->getNext())
            printInteger(out, current->getNext());
        out << current->getValue();
    }

    static int cmp(T lhs, T rhs)
    {
         if (lhs < rhs)
            return 1;
        else if (lhs == rhs)
            return 0;
        else
            return -1;
    }

    static int cmp(Node<T> *l1, Node<T> *l2)
    {
        int k = 0;
        if (l1->getNext())
            k = cmp(l1->getNext(), l2->getNext());
        else
            return cmp(l1->getValue(), l2->getValue());

        if (!k)
            return cmp(l1->getValue(), l2->getValue());

        return k;
    }

    /* inputOp | rhsSign       +| +  -       -| +  -
        ------ | -------       -|-----       -|-----
       lhsSign | resultOp      +| +  -       +| -  +
                               -| -  +       -| +  -    */

    // true - addition, false - substraction
    static int cmp(const BigInteger<T> &lhs, const BigInteger<T> &rhs)
    {
         /* returns 1 if lhs < rhs
               0 if lhs == rhs
              -1 if lhs > rhs */

        if (lhs.l->getSize() < rhs.l->getSize())
            return 1;
        else if (lhs.l->getSize() == rhs.l->getSize())
            return cmp(lhs.l->getHead(), rhs.l->getHead());
        else
            return -1;
    }

    BigInteger processOp(const BigInteger<T> &lhs, const BigInteger<T> &rhs, bool inputOp) const
    {
        bool outputOp = (lhs.negative == rhs.negative);
        if (inputOp == false)
            outputOp = !outputOp;

        if (outputOp == true)
            return add(lhs, rhs);
        else
            return substract(lhs, rhs);
    }

    BigInteger add(const BigInteger<T> &lhs, const BigInteger<T> &rhs) const
    {
        BigInteger result;

        Node<T> *list1 = lhs.l->getHead();
        Node<T> *list2 = rhs.l->getHead();

        int carry = 0, sum;
        while (list1 && list2)
        {
            sum = list1->getValue() + list2->getValue() + carry;
            result.l->insertToRight(new Node<T>(sum % 10));
            carry = sum / 10;
            list1 = list1->getNext();
            list2 = list2->getNext();
        }

        while (list1)
        {
            sum = list1->getValue() + carry;
            result.l->insertToRight(new Node<T>(sum % 10));
            carry = sum / 10;
            list1 = list1->getNext();
        }

        while (list2)
        {
            sum = list2->getValue() + carry;
            result.l->insertToRight(new Node<T>(sum % 10));
            carry = sum / 10;
            list2 = list2->getNext();
        }

        if (carry)
            result.l->insertToRight(new Node<T>(carry));

        result.negative = lhs.negative;
        return result;
    }

    BigInteger substract(const BigInteger<T> &lhs, const BigInteger<T> &rhs) const
    {
        BigInteger result;

        Node<T> *list1 = lhs.l->getHead(), *list2 = rhs.l->getHead();
        result.negative = lhs.negative;

        int cmpResult = cmp(*this, rhs);

        if (cmpResult == 1)
        {
            Node<T> *aux = list2;
            list2 = list1;
            list1 = aux;
            result.negative = rhs.negative;
        }
        else if (cmpResult == 0)
        {
            result.l->insertToRight(new Node<T>(0));
            return result;
        }

        int carry = 0, diff;
        while (list2)
        {
            if (carry)
            {
                if (!list1->getValue())
                    list1->setValue(9);
                else
                {
                    list1->setValue(list1->getValue() - 1);
                    carry = 0;
                }
            }

            diff = list1->getValue() - list2->getValue();
            if (diff < 0)
            {
                carry = 1;
                diff = 10 + list1->getValue() - list2->getValue();
            }
            // manage leading zero case
            if (!(!list1->getNext() && !diff))
                result.l->insertToRight(new Node<T>(diff));
            list1 = list1->getNext();
            list2 = list2->getNext();
        }

        while (list1)
        {
            if (carry)
            {
                if (!list1->getValue())
                    list1->setValue(9);
                else
                {
                    list1->setValue(list1->getValue() - 1);
                    carry = 0;
                }
            }


            if (!(!list1->getNext() && !list1->getValue()))
                result.l->insertToRight(new Node<T>(list1->getValue()));
            list1 = list1->getNext();
        }

        return result;
    }

public:
    BigInteger()
    {
        l = new LinkedList<T>;
        negative = false;
    }

    BigInteger(const char *x)
    {
        bool insertion = false;
        negative = false;
        l = new LinkedList<T>;
        bool leadingZero = true;
        for (int i = 0; i < strlen(x); i++)
        {
            if (x[i] >= '0' && x[i] <= '9')
            {
                if (leadingZero && x[i] != '0')
                    leadingZero = false;
                if (!leadingZero)
                {
                    l->insertToLeft(new Node<T>(x[i] - '0'));
                    insertion = true;
                }
            }
        }

        if (x[0] == '-')
            negative = true;
        if (!insertion)
            l->insertToLeft(new Node<T>(0));
    }

    BigInteger(const BigInteger &rhs)
    {
        l = new LinkedList<T>;
        Node<T> *current = rhs.l->getHead();
        while(current)
        {
            l->insertToRight(new Node<T>(current->getValue()));
            current = current->getNext();
        }
        negative = rhs.negative;
    };

    virtual ~BigInteger()
    {
        delete l;
    }

    virtual BigInteger operator+(const BigInteger &rhs)
    {
        return processOp(*this, rhs, true);
    }

    virtual BigInteger operator+(const char *c)
    {
        return processOp(*this, BigInteger(c), true);
    }

    BigInteger operator-(const BigInteger &rhs) const
    {
        return processOp(*this, rhs, false);
    }

    BigInteger operator-(const char *c)
    {
        return processOp(*this, BigInteger(c), false);
    }

    BigInteger operator*(const BigInteger &rhs) const
    {
        BigInteger result;
        Node<T> *list1, *list2;

        if (l->getSize() > rhs.l->getSize())
            list1 = l->getHead(), list2 = rhs.l->getHead();
        else
            list1 = rhs.l->getHead(), list2 = l->getHead();
        Node<T> *copyList1 = list1;

        int k = -1, carry, i, product;
        // for every digit in list 2...
        while (list2 != NULL)
        {
            BigInteger aux;
            k++;
            carry = 0;

            for (i = 0; i < k; i++)
                aux.l->insertToRight(new Node<T>(0));

            while (list1)
            {
                product = list1->getValue() * list2->getValue() + carry;
                aux.l->insertToRight(new Node<T>(product % 10));
                carry = product / 10;
                list1 = list1->getNext();
            }

            if (carry)
                aux.l->insertToRight(new Node<T>(carry));

            result = result + aux;
            list1 = copyList1;
            list2 = list2->getNext();
        }

        result.negative = computeSign(negative, rhs.negative);
        return result;
    }

    BigInteger operator*(const char *c) const
    {
        return *this * BigInteger(c);
    }

    BigInteger operator=(const BigInteger &rhs)
    {
        delete l;
        l = new LinkedList<T>;
        Node<T> *current = rhs.l->getHead();
        while(current)
        {
            l->insertToRight(new Node<T>(current->getValue()));
            current = current->getNext();
        }
        negative = rhs.negative;
        return *this;
    }

    const char * operator=(const char *x)
    {
        delete l;
        l = new LinkedList<T>;
        negative = false;
        bool leadingZero = true, insertion = false;
        for (int i = 0; i < strlen(x); i++)
        {
            if (x[i] >= '0' && x[i] <= '9')
            {
                if (leadingZero && x[i] != '0')
                    leadingZero = false;
                if (!leadingZero)
                {
                    l->insertToLeft(new Node<T>(x[i] - '0'));
                    insertion = true;
                }
            }
        }

        if (x[0] == '-')
            negative = true;

        if (!insertion)
            l->insertToLeft(new Node<T>(0)), negative = false;
        return x;
    }

    BigInteger operator+=(const BigInteger &rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    BigInteger operator+=(const char *c)
    {
        *this = *this + BigInteger(c);
        return *this;
    }

    BigInteger operator-=(const BigInteger &rhs)
    {
        *this = *this - rhs;
        return *this;
    }

    BigInteger operator-=(const char *c)
    {
        *this = *this - BigInteger(c);
        return *this;
    }

    BigInteger operator*=(const BigInteger &rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    BigInteger operator*=(const char *c)
    {
        *this = *this * BigInteger(c);
        return *this;
    }

    BigInteger operator++()
    {
        *this = *this + "1";
        return *this;
    }

    BigInteger operator++(int x)
    {
        BigInteger result = *this;
        *this = *this + "1";
        return result;
    }

    BigInteger operator--()
    {
        *this = *this - "1";
        return *this;
    }

    BigInteger operator--(int x)
    {
        BigInteger result = *this;
        *this = *this - "1";
        return result;
    }

    BigInteger operator/(const BigInteger &rhs)
    {
        // TODO - faster and smarter implementation
        BigInteger<T> result = "0";
        BigInteger<T> lhs = *this;
        while (cmp(lhs, rhs) <= 0)
        {
            lhs = lhs - rhs;
            result = result + BigInteger("1");
        }

        return result;
    }

    BigInteger operator/(const char *c)
    {
        return *this / BigInteger(c);
    }

    BigInteger operator%(const BigInteger &rhs)
    {
        return *this - (*this / rhs) * rhs;
    }

    BigInteger operator%(const char *c)
    {
        BigInteger rhs(c);
        return *this - (*this / rhs) * rhs;
    }

    BigInteger properDivision(const BigInteger &lhs, const BigInteger &rhs)
    {
        BigInteger result = "0";
    } // prototype

    BigInteger operator/=(const BigInteger &rhs)
    {
        *this = *this / rhs;
        return *this;
    }

    BigInteger operator/=(const char *c)
    {
        *this = *this / BigInteger(c);
        return *this;
    }

    BigInteger operator-()
    {
        BigInteger result = *this;
        result.negative = !result.negative;
        return result;
    }

    bool operator==(const BigInteger &rhs)
    {
        if (cmp(*this, rhs) == 0)
            return true;
        return false;
    }

    bool operator!=(const BigInteger &rhs)
    {
        return !(*this == rhs);
    }

    bool operator<(const BigInteger &rhs) const
    {
        if (cmp(*this, rhs) == 1)
            return true;
        return false;
    }

    bool operator<=(const BigInteger &rhs)
    {
        return (*this < rhs || *this == rhs);
    }

    bool operator>(const BigInteger &rhs) const
    {
        if (cmp(*this, rhs) == -1)
            return true;
        return false;
    }

    bool operator>=(const BigInteger &rhs)
    {
        return (*this > rhs || *this == rhs);
    }

    Node<T> &operator[](int pos)
    {
        if (l->getSize() >= pos)
        throw "Array index out of bounds!\n";

        Node<T> current = l->getHead();
        for (int i = 1; i < pos; i++)
            current = current->getNext();
        return current;
    }

    template <class U>
    friend ostream & operator<< (ostream &out, const BigInteger<U> &x)
    {
        Node<T> *current = x.l->getHead();
        if (current)
        {
            if (x.negative)
                out << '-';
            x.printInteger(out, current);
        }
        return out;
    }

    template <class U>
    friend istream & operator>> (istream &in, BigInteger<U> &x)
    {
        char str[999999]; // need a better way of doing this
        in >> str;
        x = str;

        return in;
    }

    static BigInteger<T> getGCD(BigInteger<T> lhs, BigInteger<T> rhs)
    {
        lhs.negative = rhs.negative = false;

        while (cmp(lhs, rhs))
        {
            if (cmp(lhs, rhs) == 1)
                rhs = rhs - lhs;
            else
                lhs = lhs - rhs;
        }

        return lhs;
    }
};

#endif

