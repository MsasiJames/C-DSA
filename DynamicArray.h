#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int count;

    void resize() {
        T* temp = new T[capacity * 2];
        for (int i = 0; i < count; i++) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        capacity *= 2;
    }

public:
    DynamicArray(int initialCapacity = 2) : capacity(initialCapacity), count(0) {
        data = new T[initialCapacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    void add(const T& item) {
        if (count == capacity) {
            resize();
        }
        data[count++] = item;
    }

    T get(int index) const {
        if (index < 0 || index >= count) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    void remove(int index) {
        if (index < 0 || index >= count) {
            throw out_of_range("Index out of bounds");
        }
        for (int i = index; i < count - 1; i++) {
            data[i] = data[i + 1];
        }
        count--;
    }

    int size() const {
        return count;
    }

    T* begin() {
        return data;  // pointer to first element
    }

    T* end() {
        return data + count;  // pointer to one past the last element
    }
};

#endif