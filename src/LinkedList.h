#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"

template<class T>
class LinkedList
{
    Node<T> *sentinel;
    int size;

public:
    LinkedList()
    {
        size = 0;
        sentinel = new Node<T>;
    }

    LinkedList(T x)
    {
        size = 0;
        sentinel = new Node<T>;
        Node<T> *newEntry = new Node<T>;
        newEntry->setValue(x);
        sentinel->setNext(newEntry);
    }

    ~LinkedList()
    {
        Node<T> *current = sentinel;
        Node<T> *prev;
        while (current)
        {
            prev = current;
            current = current->getNext();
            delete prev;
        }
    }

    Node<T>* getHead() const
    {
        return sentinel->getNext();
    }

    void insertToLeft(Node<T> *x)
    {
        size++;
        x->setNext(sentinel->getNext());
        sentinel->setNext(x);
    }

    void insertToRight(Node<T> *x)
    {
        size++;
        Node<T> *current = sentinel;
        while (current->getNext())
            current = current->getNext();
        current->setNext(x);
    }

    int getSize()
    {
        return size;
    }
};

#endif // LINKED_LIST_H

