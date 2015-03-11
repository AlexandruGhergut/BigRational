#ifndef NODE_H
#define NODE_H

#include <cstddef>

class Node
{
    int value;
    Node *next;

public:
    Node();
    Node(int x);
    int getValue();
    void setValue(int x);
    Node* getNext();
    void setNext(Node *x);
};
#endif // NODE_H
