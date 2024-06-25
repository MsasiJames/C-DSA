#ifndef DOUBLYNODE_H
#define DOUBLYNODE_H

#include <stdexcept>

template<typename T>
class DoublyNode {
public:
    T data;
    DoublyNode<T>* next;
    DoublyNode<T>* prev;

    DoublyNode(const T& data) : data(data), next(nullptr), prev(nullptr) {}
};

#endif