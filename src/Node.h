#ifndef NODE_H
#define NODE_H

#include <cstddef>

template <class T>
class Node
{
    T value;
    Node *next;

public:
    Node()
    {
        value = 0;
        next = NULL;
    }

    Node(T x)
    {
        value = x;
        next = NULL;
    }

    T getValue()
    {
        return value;
    }

    void setValue(T x)
    {
        value = x;
    }

    Node* getNext()
    {
        return next;
    }

    void setNext(Node *x)
    {
        next = x;
    }
};

template <>
class Node <char>
{
    char value;
    Node *next;

public:
    Node()
    {
        value = '0';
        next = NULL;
    }
    Node(int x)
    {
        value = x + '0';
        next = NULL;
    }
    int getValue() { return value - '0'; }
    void setValue(char x) { value = x; }
    void setValue(int x) { value = x + '0'; }
    Node* getNext() { return next; }
    void setNext(Node *x) { next = x; }
};

#endif // NODE_H

