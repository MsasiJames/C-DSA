#include "DoublyLinkedList.h"
#include "Property.h"
#include "SearchingMethods.h"
#include "ImportMethod.h"
#include <iostream>

using namespace std;

int main(){
    DoublyLinkedList<Property> propertyList;

    if(importFromCsv("mudah-apartment-kl-selangor.csv",propertyList)) {
        cout << "Data successfully imported from the CSV file." << endl;
    } else {
        cout << "Failed to import data from the CSV file." << endl;
    }
    cout << propertyList.getSize() << endl;
    int choice;
    cout << "To search using Property name(1), Location(2), Completion year(3): ";
    cin >> choice;

    int algochoice;
    cout << "For linear search (1), binary search (2), use binary search only for completion year search: ";
    cin >> algochoice;
    cin.ignore();
    string data;
    cout << "Enter search data: ";
    getline(cin, data);

    cout << "Current search criteria set to: " << setCriteria(choice) << endl;
    cout << "Searching for: " << data << "... ...\n";

    if(algochoice == 1){
        LinearSearch(propertyList.getHead(),propertyList.getTail(),data,setCriteria(choice-1));
    }else if(algochoice == 2){
        int numData = stoi(data);
        // NEED TO SORT THE DATA FIRST FOR BINARY SEARCH
        quickSortForBinary(propertyList.getHead(), propertyList.getTail(),setCriteria(choice-1));
        displayResults(propertyList.getHead(),numData,setCriteria(choice-1));
    }else{cout << "Wrong Input!!! on choice of algorithm\n";exit(1);};

    return 0;
}