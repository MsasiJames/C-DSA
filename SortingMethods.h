#ifndef SORTINGMETHODS_H
#define SORTINGMETHODS_H

#include "DoublyLinkedList.h"
#include "Property.h"
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// Swap properties
void swapProperties(Property* a, Property* b){
    Property temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble sort by monthly_rent
void BubbleSortRent(DoublyLinkedList<Property>* propertyList){
    DoublyNode<Property>* current;
    bool swapped;
    do {
        swapped = false;
        for (current = propertyList->getHead(); current->next != nullptr; current = current->next){
            if (stoi(current->data.monthly_rent) < stoi(current->next->data.monthly_rent)){
                swapProperties(&(current->data), &(current->next->data));
                swapped = true;
            }
        }
    } while (swapped);
}

// Bubble sort by size
void BubbleSortSize(DoublyLinkedList<Property>* propertyList){
    DoublyNode<Property>* current;
    bool swapped;
    do {
        swapped = false;
        for (current = propertyList->getHead(); current->next != nullptr; current = current->next){
            if (stoi(current->data.size) < stoi(current->next->data.size)){
                swapProperties(&(current->data), &(current->next->data));
                swapped = true;
            }
        }
    } while (swapped);
}

// Bubble sort by count
void BubbleSortCount(DoublyLinkedList<Property>* propertyList){
    DoublyNode<Property>* current;
    bool swapped;
    do {
        swapped = false;
        for (current = propertyList->getHead(); current->next != nullptr; current = current->next){
            if (current->data.favCount < current->next->data.favCount){
                swapProperties(&(current->data), &(current->next->data));
                swapped = true;
            }
        }
    } while (swapped);
}

// Bubble sort by location
void BubbleSortLocation(DoublyLinkedList<Property>* propertyList){
    DoublyNode<Property>* current;
    bool swapped;
    do {
        swapped = false;
        for (current = propertyList->getHead(); current->next != nullptr; current = current->next){
            if (current->data.location < current->next->data.location){
                swapProperties(&(current->data), &(current->next->data));
                swapped = true;
            }
        }
    } while (swapped);
}

// Partition for quick sort by location
DoublyNode<Property>* partitionLocation(DoublyNode<Property>* low, DoublyNode<Property>* high){
    string pivot = high->data.location;
    DoublyNode<Property>* i = low->prev;
    for (DoublyNode<Property>* j = low; j != high; j = j->next){
        if (j->data.location >= pivot){
            i = (i == nullptr) ? low : i->next;
            swapProperties(&(i->data), &(j->data));
        }
    }
    i = (i == nullptr) ? low : i->next;
    swapProperties(&(i->data), &(high->data));
    return i;
}

// Quick sort by location
void quickSortLocation(DoublyNode<Property>* low, DoublyNode<Property>* high){
    if (high != nullptr && low != high && low != high->next){
        DoublyNode<Property>* p = partitionLocation(low, high);
        quickSortLocation(low, p->prev);
        quickSortLocation(p->next, high);
    }
}

// Partition for quick sort by monthly_rent
DoublyNode<Property>* partitionRent(DoublyNode<Property>* low, DoublyNode<Property>* high){
    string pivot = high->data.monthly_rent;
    DoublyNode<Property>* i = nullptr;
    i = low->prev;
    for (DoublyNode<Property>* j = low; j != high; j = j->next){
        if (stoi(j->data.monthly_rent) >= stoi(pivot)){
            //cout << "i: " << i << ", j: " << j << ", j->data.monthly_rent: " << j->data.monthly_rent << "\n";
            i = (i == nullptr) ? low : i->next;
            //cout << "After assignment, i: " << i << "\n";
            swapProperties(&(i->data), &(j->data));
        }
    }
    //cout << "OK\n";
    i = (i == nullptr) ? low : i->next;
    swapProperties(&(i->data), &(high->data));
    return i;
}

// Quick sort by monthly_rent
void quickSortRent(DoublyNode<Property>* low, DoublyNode<Property>* high){
    if (high != nullptr && low != high && low != high->next){
        DoublyNode<Property>* p = partitionRent(low, high);
        //cout << "\nNEXT";
        quickSortRent(low, p->prev);
        quickSortRent(p->next, high);
    }
}

// Partition for quick sort by size
DoublyNode<Property>* partitionSize(DoublyNode<Property>* low, DoublyNode<Property>* high){
    string pivot = high->data.size;
    DoublyNode<Property>* i = low->prev;
    for (DoublyNode<Property>* j = low; j != high; j = j->next){
        if (stoi(j->data.size) >= stoi(pivot)){
            i = (i == nullptr) ? low : i->next;
            swapProperties(&(i->data), &(j->data));
        }
    }
    i = (i == nullptr) ? low : i->next;
    swapProperties(&(i->data), &(high->data));
    return i;
}

// Quick sort by size
void quickSortSize(DoublyNode<Property>* low, DoublyNode<Property>* high){
    if (high != nullptr && low != high && low != high->next){
        DoublyNode<Property>* p = partitionSize(low, high);
        quickSortSize(low, p->prev);
        quickSortSize(p->next, high);
    }
}

// // Partition for quick sort by count
// DoublyNode<Property>* partitionCount(DoublyNode<Property>* low, DoublyNode<Property>* high){
//     int pivot = high->data.favCount;
//     DoublyNode<Property>* i = low->prev;
//     for (DoublyNode<Property>* j = low; j != high; j = j->next){
//         if (j->data.favCount >= pivot){
//             i = (i == nullptr) ? low : i->next;
//             swapProperties(&(i->data), &(j->data));
//         }
//     }
//     i = (i == nullptr) ? low : i->next;
//     swapProperties(&(i->data), &(high->data));
//     return i;
// }

// // Quick sort by count
// void quickSortCount(DoublyNode<Property>* low, DoublyNode<Property>* high){
//     if (high != nullptr && low != high && low != high->next){
//         DoublyNode<Property>* p = partitionCount(low, high);
//         quickSortCount(low, p->prev);
//         quickSortCount(p->next, high);
//     }
// }

// Partition for quick sort by reqCount
DoublyNode<Property>* partitionRCount(DoublyNode<Property>* low, DoublyNode<Property>* high){
    int pivot = high->data.reqCount;
    DoublyNode<Property>* i = low->prev;
    for (DoublyNode<Property>* j = low; j != high; j = j->next){
        if (j->data.reqCount >= pivot){
            i = (i == nullptr) ? low : i->next;
            swapProperties(&(i->data), &(j->data));
        }
    }
    i = (i == nullptr) ? low : i->next;
    swapProperties(&(i->data), &(high->data));
    return i;
}

// Quick sort by reqCount
void quickSortRCount(DoublyNode<Property>* low, DoublyNode<Property>* high){
    if (high != nullptr && low != high && low != high->next){
        DoublyNode<Property>* p = partitionRCount(low, high);
        quickSortRCount(low, p->prev);
        quickSortRCount(p->next, high);
    }
}

// Bubble sort by monthly_rent in ascending order
void BubbleSortRentAscending(DoublyLinkedList<Property>* propertyList){
    DoublyNode<Property>* current;
    bool swapped;
    do {
        swapped = false;
        for (current = propertyList->getHead(); current->next != nullptr; current = current->next){
            if (stoi(current->data.monthly_rent) > stoi(current->next->data.monthly_rent)){
                swapProperties(&(current->data), &(current->next->data));
                swapped = true;
            }
        }
    } while (swapped);
}

// Bubble sort by size in ascending order
void BubbleSortSizeAscending(DoublyLinkedList<Property>* propertyList){
    DoublyNode<Property>* current;
    bool swapped;
    do {
        swapped = false;
        for (current = propertyList->getHead(); current->next != nullptr; current = current->next){
            if (stoi(current->data.size) > stoi(current->next->data.size)){
                swapProperties(&(current->data), &(current->next->data));
                swapped = true;
            }
        }
    } while (swapped);
}

// Bubble sort by location in ascending order
void BubbleSortLocationAscending(DoublyLinkedList<Property>* propertyList){
    DoublyNode<Property>* current;
    bool swapped;
    do {
        swapped = false;
        for (current = propertyList->getHead(); current->next != nullptr; current = current->next){
            if (current->data.location > current->next->data.location){
                swapProperties(&(current->data), &(current->next->data));
                swapped = true;
            }
        }
    } while (swapped);
}

// Partition for quick sort by location in ascending order
DoublyNode<Property>* partitionLocationAscending(DoublyNode<Property>* low, DoublyNode<Property>* high){
    string pivot = high->data.location;
    DoublyNode<Property>* i = low->prev;
    for (DoublyNode<Property>* j = low; j != high; j = j->next){
        if (j->data.location <= pivot){
            i = (i == nullptr) ? low : i->next;
            swapProperties(&(i->data), &(j->data));
        }
    }
    i = (i == nullptr) ? low : i->next;
    swapProperties(&(i->data), &(high->data));
    return i;
}

// Quick sort by location in ascending order
void quickSortLocationAscending(DoublyNode<Property>* low, DoublyNode<Property>* high){
    if (high != nullptr && low != high && low != high->next){
        DoublyNode<Property>* p = partitionLocationAscending(low, high);
        quickSortLocationAscending(low, p->prev);
        quickSortLocationAscending(p->next, high);
    }
}

// Partition for quick sort by monthly_rent in ascending order
DoublyNode<Property>* partitionRentAscending(DoublyNode<Property>* low, DoublyNode<Property>* high){
    string pivot = high->data.monthly_rent;
    DoublyNode<Property>* i = low->prev;
    for (DoublyNode<Property>* j = low; j != high; j = j->next){
        if (stoi(j->data.monthly_rent) <= stoi(pivot)){
            i = (i == nullptr) ? low : i->next;
            swapProperties(&(i->data), &(j->data));
        }
    }
    i = (i == nullptr) ? low : i->next;
    swapProperties(&(i->data), &(high->data));
    return i;
}

// Quick sort by monthly_rent in ascending order
void quickSortRentAscending(DoublyNode<Property>* low, DoublyNode<Property>* high){
    if (high != nullptr && low != high && low != high->next){
        DoublyNode<Property>* p = partitionRentAscending(low, high);
        quickSortRentAscending(low, p->prev);
        quickSortRentAscending(p->next, high);
    }
}

// Partition for quick sort by size in ascending order
DoublyNode<Property>* partitionSizeAscending(DoublyNode<Property>* low, DoublyNode<Property>* high){
    string pivot = high->data.size;
    DoublyNode<Property>* i = low->prev;
    for (DoublyNode<Property>* j = low; j != high; j = j->next){
        if (stoi(j->data.size) <= stoi(pivot)){
            i = (i == nullptr) ? low : i->next;
            swapProperties(&(i->data), &(j->data));
        }
    }
    i = (i == nullptr) ? low : i->next;
    swapProperties(&(i->data), &(high->data));
    return i;
}

// Quick sort by size in ascending order
void quickSortSizeAscending(DoublyNode<Property>* low, DoublyNode<Property>* high){
    if (high != nullptr && low != high && low != high->next){
        DoublyNode<Property>* p = partitionSizeAscending(low, high);
        quickSortSizeAscending(low, p->prev);
        quickSortSizeAscending(p->next, high);
    }
}

#endif