#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <stdexcept>
#include "SinglyNode.h"

using namespace std;

template <typename T>
class Queue
{
private:
    SinglyNode<T>* head = nullptr;
    SinglyNode<T>* tail = nullptr;
    size_t size = 0; // Added size attribute

public:
    // Constructor
    Queue(){
        head = nullptr;
        tail = nullptr;
    }

    // Destructor
    ~Queue(){
        SinglyNode<T>* temp = head;
        while(temp != nullptr){
            SinglyNode<T>* nextNode = temp->next;
            // delete temp;  // Uncomment this if you want to delete nodes when the Queue is destroyed
            temp = nextNode;
        }
        head = nullptr;
        tail = nullptr;
    }

    // Get first node
    SinglyNode<T>* getHead(){
        return head;
    }

    // Get last node
    SinglyNode<T>* getTail(){
        return tail;
    }

    // Get size of the queue
    size_t getSize() {
        return size;
    }

    // Check if the queue is empty
    bool isEmpty(){
        return head == nullptr;
    }

    // Push a new SinglyNode into the queue
    void push(const T& data){
        SinglyNode<T>* newNode = new SinglyNode<T>(data);
        if(isEmpty()){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->setNext(newNode);
            tail = newNode;
        }
        size++;  // Increase the size
    }

    // Pop a SinglyNode from the queue
    SinglyNode<T>* pop(){
        if(isEmpty()){
            throw out_of_range("No data in the queue!");
        }
        else{
            SinglyNode<T>* result = head;
            head = head->next;
            size--;  // Decrease the size
            return result;
        }
    }

    void popOut(){
        if(isEmpty()){
            throw out_of_range("No data in the queue!");
        }
        SinglyNode<T>* result = head;
        head = head->next;
        if (head == nullptr) {  // If the last element was popped
            tail = nullptr;
        }
        delete result;  // Deleting the node to prevent memory leak
        size--;  // Decrease the size
    }

    // Peek at the front of the queue without removing it
    T* peek() {
        if (isEmpty()) {
            throw out_of_range("Queue is empty!");
        }
        return &(head->data);
    }
};

#endif