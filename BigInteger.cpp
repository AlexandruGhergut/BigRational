#include "BigInteger.h"

BigInteger::BigInteger()
{
    l = new LinkedList;
    negative = false;
}

BigInteger::BigInteger(const char *x)
{
    bool insertion = false;
    negative = false;
    l = new LinkedList;
    bool leadingZero = true;
    for (int i = 0; i < strlen(x); i++)
    {
        if (x[i] >= '0' && x[i] <= '9')
        {
            if (leadingZero && x[i] != '0')
                leadingZero = false;
            if (!leadingZero)
            {
                l->insertToLeft(new Node(x[i] - '0'));
                insertion = true;
            }
        }
    }

    if (x[0] == '-')
        negative = true;
    if (!insertion)
        l->insertToLeft(new Node(0));
}

BigInteger::BigInteger(BigInteger const &rhs)
{
    l = new LinkedList;
    Node *current = rhs.l->getHead();
    while(current)
    {
        l->insertToRight(new Node(current->getValue()));
        current = current->getNext();
    }
    negative = rhs.negative;
}

BigInteger::~BigInteger()
{
    delete l;
}

bool BigInteger::computeSign(bool s1, bool s2) const
{
    if (s1 != s2)
        return true;
    return false;
}

void BigInteger::printInteger(Node *current) const
{
    if (current->getNext())
        printInteger(current->getNext());
    cout << current->getValue();
}

int BigInteger::cmp(int lhs, int rhs)
{
    if (lhs < rhs)
        return 1;
    else if (lhs == rhs)
        return 0;
    else
        return -1;
}

int BigInteger::cmp(Node *l1, Node *l2)
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

int BigInteger::cmp(BigInteger const &lhs, BigInteger const &rhs)
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

/* inputOp | rhsSign       +| +  -       -| +  -
    ------ | -------       -|-----       -|-----
   lhsSign | resultOp      +| +  -       +| -  +
                           -| -  +       -| +  -    */

// true - addition, false - substraction

BigInteger BigInteger::processOp(BigInteger const &lhs, BigInteger const &rhs, bool inputOp) const
{
    bool outputOp = (lhs.negative == rhs.negative);
    if (inputOp == false)
        outputOp = !outputOp;

    if (outputOp == true)
        return add(lhs, rhs);
    else
        return substract(lhs, rhs);
}

BigInteger BigInteger::add(BigInteger const &lhs, BigInteger const &rhs) const
{
    BigInteger result;

    Node *list1 = lhs.l->getHead();
    Node *list2 = rhs.l->getHead();

    int carry = 0, sum;
    while (list1 && list2)
    {
        sum = list1->getValue() + list2->getValue() + carry;
        result.l->insertToRight(new Node(sum % 10));
        carry = sum / 10;
        list1 = list1->getNext();
        list2 = list2->getNext();
    }

    while (list1)
    {
        sum = list1->getValue() + carry;
        result.l->insertToRight(new Node(sum % 10));
        carry = sum / 10;
        list1 = list1->getNext();
    }

    while (list2)
    {
        sum = list2->getValue() + carry;
        result.l->insertToRight(new Node(sum % 10));
        carry = sum / 10;
        list2 = list2->getNext();
    }

    if (carry)
        result.l->insertToRight(new Node(carry));

    result.negative = lhs.negative;
    return result;
}

BigInteger BigInteger::substract(BigInteger const &lhs, BigInteger const &rhs) const
{
    BigInteger result;

    Node *list1 = lhs.l->getHead(), *list2 = rhs.l->getHead();
    result.negative = lhs.negative;

    int cmpResult = cmp(*this, rhs);

    if (cmpResult == 1)
    {
        Node *aux = list2;
        list2 = list1;
        list1 = aux;
        if (rhs.negative)
            result.negative = false;
        else
            result.negative = true;
    }
    else if (cmpResult == 0)
    {
        result.l->insertToRight(new Node(0));
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
            result.l->insertToRight(new Node(diff));
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
            result.l->insertToRight(new Node(list1->getValue()));
        list1 = list1->getNext();
    }

    return result;
}

BigInteger BigInteger::getGCD(BigInteger lhs, BigInteger rhs)
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

BigInteger BigInteger::operator+(BigInteger const &rhs) const
{
    return processOp(*this, rhs, true);
}

BigInteger BigInteger::operator-(BigInteger const &rhs)
{
    return processOp(*this, rhs, false);
}

BigInteger BigInteger::operator*(BigInteger const &rhs) const
{
    BigInteger result;
    Node *list1, *list2;

    if (l->getSize() > rhs.l->getSize())
        list1 = l->getHead(), list2 = rhs.l->getHead();
    else
        list1 = rhs.l->getHead(), list2 = l->getHead();
    Node *copyList1 = list1;

    int k = -1, carry, i, product;
    // for every digit in list 2...
    while (list2 != NULL)
    {
        BigInteger aux;
        k++;
        carry = 0;

        for (i = 0; i < k; i++)
            aux.l->insertToRight(new Node(0));

        while (list1)
        {
            product = list1->getValue() * list2->getValue() + carry;
            aux.l->insertToRight(new Node(product % 10));
            carry = product / 10;
            list1 = list1->getNext();
        }

        if (carry)
            aux.l->insertToRight(new Node(carry));

        result = result + aux;
        list1 = copyList1;
        list2 = list2->getNext();
    }

    result.negative = computeSign(negative, rhs.negative);
    return result;
}

BigInteger BigInteger::operator=(BigInteger const &rhs)
{
    l = new LinkedList;
    Node *current = rhs.l->getHead();
    while(current)
    {
        l->insertToRight(new Node(current->getValue()));
        current = current->getNext();
    }
    negative = rhs.negative;
    return *this;
}

BigInteger BigInteger::operator/(BigInteger const &rhs) const
{
    // TODO
    BigInteger result = *this;
    BigInteger i;
    BigInteger one;
    one = "1";
    for (i = "1"; cmp(i, rhs) <= 0; i = i + one)
        result = result - rhs;
    return result;
}

const char * BigInteger::operator=(const char *x)
{
    delete l;
    l = new LinkedList;
    bool leadingZero = true, insertion = false;
    for (int i = 0; i < strlen(x); i++)
    {
        if (x[i] >= '0' && x[i] <= '9')
        {
            if (leadingZero && x[i] != '0')
                leadingZero = false;
            if (!leadingZero)
            {
                l->insertToLeft(new Node(x[i] - '0'));
                insertion = true;
            }
        }
    }

    if (x[0] == '-')
        negative = true;

    if (!insertion)
        l->insertToLeft(new Node(0)), negative = false;
    return x;
}

ostream & operator << (ostream &out, const BigInteger &x)
{
    Node *current = x.l->getHead();
    if (current)
    {
        if (x.negative)
            cout << '-';
        x.printInteger(current);
    }
    return out;
}
