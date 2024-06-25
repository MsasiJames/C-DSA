#ifndef SINGLYNODE_H
#define SINGLYNODE_H

#include <stdexcept>

template <typename T>
class SinglyNode {
public:
    T data;
    SinglyNode* next;

    SinglyNode(const T& data) : data(data), next(nullptr) {}

    void setNext(SinglyNode* nextNode) {
        next = nextNode;
    }
};

#endif