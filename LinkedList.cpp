#include "LinkedList.h"

LinkedList::LinkedList()
{
    size = 0;
    sentinel = new Node;
}

LinkedList::LinkedList(int x)
{
    size = 0;
    sentinel = new Node;
    Node *newEntry = new Node;
    newEntry->setValue(x);
    sentinel->setNext(newEntry);
}

LinkedList::~LinkedList()
{
    Node *current = sentinel;
    Node *prev;
    while (current)
    {
        prev = current;
        current = current->getNext();
        delete prev;
    }
}

Node* LinkedList::getHead()
{
    return sentinel->getNext();
}

void LinkedList::insertToLeft(Node *x)
{
    size++;
    x->setNext(sentinel->getNext());
    sentinel->setNext(x);
}

void LinkedList::insertToRight(Node *x)
{
    size++;
    Node *current = sentinel;
    while (current->getNext())
        current = current->getNext();
    current->setNext(x);
}

int LinkedList::getSize()
{
    return size;
}
