#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "DoublyNode.h"
#include <iostream>

template <typename T>
class DoublyLinkedList {
private:
    DoublyNode<T> *head;
    DoublyNode<T> *tail;
    int size;

public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}  // Initialized size to 0

    // Destructor
    ~DoublyLinkedList() {
        DoublyNode<T> *temp = head;
        while (head) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    DoublyNode<T> * getHead(){
        return this->head;
    }

    DoublyNode<T> * getTail(){
        return this->tail;
    }

    // Fetch current size
    int getSize() const {
        return size;
    }

    // Append a doublynode ensuring prev pointer is correctly set
    void append(const T& data) {
        DoublyNode<T> *newNode = new DoublyNode<T>(data);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;  // Increment size
    }

    // Find based on data
    DoublyNode<T>* find(const T& data) const {
        DoublyNode<T>* current = head;
        while (current) {
            if (current->data == data) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    bool exists(const T& data) const {
        return find(data) != nullptr;
    }

    void remove(const T& data) {
        DoublyNode<T>* nodeToRemove = find(data);
        if (!nodeToRemove) {
            return; // The data isn't in the list.
        }

        // Decrement the size of the list.
        size--;

        // If the node to remove is the only node in the list.
        if (nodeToRemove == head && nodeToRemove == tail) {
            delete nodeToRemove;
            head = nullptr;
            tail = nullptr;
            return;
        }

        // If the node to remove is the head node.
        if (nodeToRemove == head) {
            head = nodeToRemove->next;
            head->prev = nullptr;
            delete nodeToRemove;
            return;
        }

        // If the node to remove is the tail node.
        if (nodeToRemove == tail) {
            tail = nodeToRemove->prev;
            tail->next = nullptr;
            delete nodeToRemove;
            return;
        }

        // If the node to remove is somewhere in the middle of the list.
        DoublyNode<T>* prevNode = nodeToRemove->prev;
        DoublyNode<T>* nextNode = nodeToRemove->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        delete nodeToRemove;
    }

    // Retrieve the node at the given index
    DoublyNode<T>* getNode(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        
        DoublyNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current;
    }

};


#endif
