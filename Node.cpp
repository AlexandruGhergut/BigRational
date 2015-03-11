#include "Node.h"

Node::Node()
{
    value = 0;
    next = NULL;
}

Node::Node(int x)
{
    value = x;
    next = NULL;
}

int Node::getValue()
{
    return value;
}

void Node::setValue(int x)
{
    value = x;
}

Node* Node::getNext()
{
    return next;
}

void Node::setNext(Node *x)
{
    next = x;
}
