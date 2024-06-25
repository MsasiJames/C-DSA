#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include "SinglyNode.h"
#include "DynamicArray.h"
#include <string>
#include <iostream>
#include <functional>

template <typename T>
class SinglyLinkedList {
private:
    SinglyNode<T>* head;
    int size;

public:
    SinglyLinkedList() : head(nullptr), size(0) {}

    SinglyNode<T>* getHead() const {
        return head;
    }

    void displayAllData() const {
        if (!head) {
            cout << "The list is empty." << endl;
            return;
        }
        
        SinglyNode<T>* current = head;
        while (current) {
            cout << current->data << " \n ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }

    // Insert a new singlynode at the end of the list
    void push_back(const T& data) {
        SinglyNode<T>* newSinglyNode = new SinglyNode<T>(data);
        if (!head) {
            head = newSinglyNode;
        } else {
            SinglyNode<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newSinglyNode;
        }
        size++;
    }

    // Remove a singlynode based on key
    void remove(const T& data) {
        if (!head) return;

        if (head->data == data) {
            SinglyNode<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        SinglyNode<T>* prev = nullptr;
        SinglyNode<T>* current = head;
        while (current && current->data != data) {
            prev = current;
            current = current->next;
        }

        if (current) {
            prev->next = current->next;
            delete current;
        }
        size--;
    }

    // Find based on data
    SinglyNode<T>* find(const T& data) const {
        SinglyNode<T>* current = head;
        while (current) {
            if (current->data == data) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    SinglyNode<T>* find(const T& data, std::function<bool(const T&, const T&)> comparator) const {
        SinglyNode<T>* current = head;
        while (current) {
            if (comparator(current->data, data)) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    bool exists(const T& data) const {
        return find(data, [](const T& a, const T& b) { return a == b; }) != nullptr;
    }

    SinglyNode<T>* begin() const {
        return head;
    }

    SinglyNode<T>* end() const {
        return nullptr;
    }

    DynamicArray<T> getAllData() const {
        DynamicArray<T> data;
        SinglyNode<T>* current = head;
        while (current != nullptr) {
            data.add(current->data);
            current = current->next;
        }
        return data;
    }

    ~SinglyLinkedList() {
        while (head) {
            SinglyNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

#endif