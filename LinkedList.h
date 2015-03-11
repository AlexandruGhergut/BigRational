#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"

class LinkedList
{
    Node *sentinel;
    int size;

public:
    LinkedList();
    LinkedList(int x);
    ~LinkedList();
    Node* getHead();
    void insertToLeft(Node *x);
    void insertToRight(Node *x);
    int getSize();
};

#endif // LINKED_LIST_H
