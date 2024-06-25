#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "ImportMethod.h"
#include <chrono>

using namespace std;

class Admin : public User {
public:Admin(const string& username, const string& password) : User(username, password) {}

    void displayMenu() {
        cout << "\n--- ADMIN MENU ---\n";
        cout << "1. Create Manager\n";
        cout << "2. Activate/Deactivate Manager Account\n";
        cout << "3. Display Property Details with Filtering\n";
        cout << "4. Display Tenant Details with Filtering\n";
        cout << "5. Perform Algorithm Test\n";
        cout << "6. Logout\n";
        cout << "Enter choice: ";
    }

    enum FilterType {
        NONE,
        BY_PROPERTY_TYPE,
        BY_RENT,
        BY_SIZE
    };

   void displayFiltered(FilterType type, const string& filterString = "", int minValue = 0, int maxValue = 0) {
        int currentPage = 1;
        const int rowsPerPage = 30;
        bool isDisplaying = true;

        DoublyLinkedList<Property> displayList;
        
        switch (type) {
            case BY_PROPERTY_TYPE:
                displayList = filterByPropertyType(propertyList->getHead(),filterString);
                break;
            case BY_RENT:
                displayList = filterByMonthlyRent(propertyList->getHead(),minValue, maxValue);
                break;
            case BY_SIZE:
                displayList = filterBySize(propertyList->getHead(),minValue, maxValue);
                break;
            default:
                break;
        }

        // Pagination Logic
        while (isDisplaying) {
            system("cls");
            cout << "\t\t\t\t\t\t\t\t\t\tPROPERTY DETAILS\n";
            cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

            DoublyNode<Property>* temp = displayList.getHead();
        
            // Skip nodes to reach the starting node of the currentPage
            for (int i = 0; i < (currentPage - 1) * rowsPerPage && temp; ++i) {
                temp = temp->next;
            }

            // Display up to 30 nodes
            for (int i = 0; i < rowsPerPage && temp; ++i) {
                Property prop = temp->data;

                // Display the property details
                DisplayPropertywCount(prop);
                temp = temp->next;
            }

            // If this is the only page, break out of the loop
            if (displayList.getSize() <= rowsPerPage) {
                cout << "\nPress any key and then Enter to continue...";
                char userInput;
                cin >> userInput;
                break;
            }

            cout << "\nPage " << currentPage << " of " << (displayList.getSize() + rowsPerPage - 1) / rowsPerPage << endl;
            cout << "Enter N for next, P for previous, Q to quit: ";
            char choice;
            cin >> choice;

            switch (toupper(choice)) {
                case 'N':
                    if (currentPage * rowsPerPage < displayList.getSize()) {
                        currentPage++;
                    } else {
                        cout << "You're on the last page." << endl;
                    }
                    break;
                case 'P':
                    if (currentPage > 1) {
                        currentPage--;
                    } else {
                        cout << "You're on the first page." << endl;
                    }
                    break;
                case 'Q':
                    isDisplaying = false;
                    break;
                default:
                    cout << "Invalid choice. Please choose N, P, or Q." << endl;
                    break;
            }
        }
    }

    void FilterProperty(){
        cout << "Choose filter type:\n";
        cout << "1. Filter by property type\n";
        cout << "2. Filter by monthly rent\n";
        cout << "3. Filter by size\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Choose property type:\n";
            cout << "1. Apartment\n";
            cout << "2. Bungalow House\n";
            cout << "3. Condo / Services residence / Penthouse / Townhouse\n";
            cout << "4. Condominium\n";
            cout << "5. Duplex\n";
            cout << "6. Flat\n";
            cout << "7. Houses\n";
            cout << "8. Others\n";
            cout << "9. Residential\n";
            cout << "10. Service Residence\n";
            cout << "11. Soho\n";
            cout << "12. Studio\n";
            cout << "13. Townhouse Condo\n";

            int typeChoice;
            cin >> typeChoice;

            string type;
            switch (typeChoice) {
                case 1:
                    type = "Apartment";
                    break;
                case 2:
                    type = "Bungalow House";
                    break;
                case 3:
                    type = "Condo / Services residence / Penthouse / Townhouse";
                    break;
                case 4:
                    type = "Condominium";
                    break;
                case 5:
                    type = "Duplex";
                    break;
                case 6:
                    type = "Flat";
                    break;
                case 7:
                    type = "Houses";
                    break;
                case 8:
                    type = "Others";
                    break;
                case 9:
                    type = "Residential";
                    break;
                case 10:
                    type = "Service Residence";
                    break;
                case 11:
                    type = "Soho";
                    break;
                case 12:
                    type = "Studio";
                    break;
                case 13:
                    type = "Townhouse Condo";
                    break;
                
                default:
                    cout << "Invalid type choice.\n";
                    break;
            }
            displayFiltered(BY_PROPERTY_TYPE,type,0,0);

        } else if (choice == 2) {
            cout << "Enter minimum rent: ";
            int minRent;
            cin >> minRent;

            cout << "Enter maximum rent: ";
            int maxRent;
            cin >> maxRent;

            
            displayFiltered(BY_RENT,"",minRent, maxRent);

        } else if (choice == 3) {
            cout << "Enter minimum size: ";
            int minSize;
            cin >> minSize;

            cout << "Enter maximum size: ";
            int maxSize;
            cin >> maxSize;

            displayFiltered(BY_SIZE,"",minSize, maxSize);

        } else {
            cout << "Invalid choice.\n";
        }
    }

    void AlgoCompare(){
        cout << "\n\nBooting Doubly Linked Lists...\n";
        DoublyLinkedList<Property> list1;
        if(importFromCsv("mudah-apartment-kl-selangor.csv", list1)) {
            cout << "Data successfully imported from the CSV file.\n" << endl;
        } else {
            cout << "Failed to import data from the CSV file.\n" << endl;
        }
        cout << "List 1 Ready\n\n";
        DoublyLinkedList<Property> list2;
        if(importFromCsv("mudah-apartment-kl-selangor.csv", list2)) {
            cout << "Data successfully imported from the CSV file.\n" << endl;
        } else {
            cout << "Failed to import data from the CSV file.\n" << endl;
        }
        cout << "List 2 Ready\n";
        
        string algoChoice;
        do {
            cout << "\nEnter which algorithms to test, [1]Sort or [2]Search: ";
            cin >> algoChoice;
            if (algoChoice != "1" && algoChoice != "2"){
                cout << "Invalid option, please try again.\n\n";
            }
        } while (algoChoice != "1" && algoChoice != "2");      

        if (algoChoice == "1"){
            string sortCriteria;
            do {
                cout << "\n\nSelect sorting criteria, [1]Monthly Rent or [2]Size or [3]Location: ";
                cin >> sortCriteria;
                if (sortCriteria != "1" && sortCriteria != "2" && sortCriteria != "3"){
                    cout << "Invalid option, please try again.\n\n";
                }
            } while (sortCriteria != "1" && sortCriteria != "2" && sortCriteria != "3");

            string orderChoice;
            do {
                cout << "\n\nChoose order, [1]Descending or [2]Ascending: ";
                cin >> orderChoice;
                if (orderChoice != "1" && orderChoice != "2"){
                    cout << "Invalid option, please try again.\n\n";
                }
            } while (orderChoice != "1" && orderChoice != "2");

            if (orderChoice == "1"){
                if (sortCriteria == "1"){

                    // Quick Sort
                    chrono::high_resolution_clock::time_point startQuick = chrono::high_resolution_clock::now();
                    cout << "\nPerforming Quick Sort...\n";
                    quickSortRentAscending(list1.getHead(),list1.getTail());
                    cout << "\nFinished Quick Sorting\n";
                    chrono::high_resolution_clock::time_point stopQuick = chrono::high_resolution_clock::now();
                    chrono::milliseconds durationQuick = chrono::duration_cast<chrono::milliseconds>(stopQuick - startQuick);

                    // Bubble Sort
                    chrono::high_resolution_clock::time_point startBubble = chrono::high_resolution_clock::now();
                    cout << "\nPerforming Bubble Sort...\n";
                    BubbleSortRentAscending(&list2);
                    cout << "\nFinished Bubble Sorting\n";
                    chrono::high_resolution_clock::time_point stopBubble = chrono::high_resolution_clock::now();
                    chrono::milliseconds durationBubble = chrono::duration_cast<chrono::milliseconds>(stopBubble - startBubble);
                    
                    // Displaying outcome
                    cout << "\n[Quick Sort Time: " << (durationQuick.count()/1000) << " seconds]\t";
                    cout << "[Bubble Sort Time: " << (durationBubble.count()/1000) << " seconds]" << endl;

                } else if (sortCriteria == "2"){
                    // Quick Sort
                    chrono::high_resolution_clock::time_point startQuick = chrono::high_resolution_clock::now();
                    cout << "\nPerforming Quick Sort...\n";
                    quickSortSizeAscending(list1.getHead(),list1.getTail());
                    cout << "\nFinished Quick Sorting\n";
                    chrono::high_resolution_clock::time_point stopQuick = chrono::high_resolution_clock::now();
                    chrono::milliseconds durationQuick = chrono::duration_cast<chrono::milliseconds>(stopQuick - startQuick);

                    // Bubble Sort
                    chrono::high_resolution_clock::time_point startBubble = chrono::high_resolution_clock::now();
                    cout << "\nPerforming Bubble Sort...\n";
                    BubbleSortSizeAscending(&list2);
                    cout << "\nFinished Bubble Sorting\n";
                    chrono::high_resolution_clock::time_point stopBubble = chrono::high_resolution_clock::now();
                    chrono::milliseconds durationBubble = chrono::duration_cast<chrono::milliseconds>(stopBubble - startBubble);
                    
                    // Displaying outcome
                    cout << "\n[Quick Sort Time: " << (durationQuick.count()/1000) << " seconds]\t";
                    cout << "[Bubble Sort Time: " << (durationBubble.count()/1000) << " seconds]" << endl;
                } else {
                    // Quick Sort
                    chrono::high_resolution_clock::time_point startQuick = chrono::high_resolution_clock::now();
                    cout << "\nPerforming Quick Sort...\n";
                    quickSortLocationAscending(list1.getHead(),list1.getTail());
                    cout << "\nFinished Quick Sorting\n";
                    chrono::high_resolution_clock::time_point stopQuick = chrono::high_resolution_clock::now();
                    chrono::milliseconds durationQuick = chrono::duration_cast<chrono::milliseconds>(stopQuick - startQuick);

                    // Bubble Sort
                    chrono::high_resolution_clock::time_point startBubble = chrono::high_resolution_clock::now();
                    cout << "\nPerforming Bubble Sort...\n";
                    BubbleSortLocationAscending(&list2);
                    cout << "\nFinished Bubble Sorting\n";
                    chrono::high_resolution_clock::time_point stopBubble = chrono::high_resolution_clock::now();
                    chrono::milliseconds durationBubble = chrono::duration_cast<chrono::milliseconds>(stopBubble - startBubble);
                    
                    // Displaying outcome
                    cout << "\n[Quick Sort Time: " << (durationQuick.count()/1000) << " seconds]\t";
                    cout << "[Bubble Sort Time: " << (durationBubble.count()/1000) << " seconds]" << endl;
                }
                
                // cout << "Would you like to display the results for checking?: ";
                // string choice;
                // cin >> choice;
                // if (!(choice == "no")){
                //     display30();
                // }

            } else {
                if (sortCriteria == "1"){

                    // Quick Sort
                    chrono::high_resolution_clock::time_point startQuick = chrono::high_resolution_clock::now();
                    cout << "\nPerforming Quick Sort...\n";
                    quickSortRentAscending(list1.getHead(),list1.getTail());
                    cout << "\nFinished Quick Sorting\n";
                    chrono::high_resolution_clock::time_point stopQuick = chrono::high_resolution_clock::now();
                    chrono::milliseconds durationQuick = chrono::duration_cast<chrono::milliseconds>(stopQuick - startQuick);

                    // Bubble Sort
                    chrono::high_resolution_clock::time_point startBubble = chrono::high_resolution_clock::now();
                    cout << "\nPerforming Bubble Sort...\n";
                    BubbleSortRentAscending(&list2);
                    cout << "\nFinished Bubble Sorting\n";
                    chrono::high_resolution_clock::time_point stopBubble = chrono::high_resolution_clock::now();
                    chrono::milliseconds durationBubble = chrono::duration_cast<chrono::milliseconds>(stopBubble - startBubble);
                    
                    // Displaying outcome
                    cout << "\n[Quick Sort Time: " << (durationQuick.count()/1000) << " seconds]\t";
                    cout << "[Bubble Sort Time: " << (durationBubble.count()/1000) << " seconds]" << endl;

                } else if (sortCriteria == "2"){
                    // Quick Sort
                    chrono::high_resolution_clock::time_point startQuick = chrono::high_resolution_clock::now();
                    cout << "\nPerforming Quick Sort...\n";
                    quickSortSizeAscending(list1.getHead(),list1.getTail());
                    cout << "\nFinished Quick Sorting\n";
                    chrono::high_resolution_clock::time_point stopQuick = chrono::high_resolution_clock::now();
                    chrono::milliseconds durationQuick = chrono::duration_cast<chrono::milliseconds>(stopQuick - startQuick);

                    // Bubble Sort
                    chrono::high_resolution_clock::time_point startBubble = chrono::high_resolution_clock::now();
                    cout << "\nPerforming Bubble Sort...\n";
                    BubbleSortSizeAscending(&list2);
                    cout << "\nFinished Bubble Sorting\n";
                    chrono::high_resolution_clock::time_point stopBubble = chrono::high_resolution_clock::now();
                    chrono::milliseconds durationBubble = chrono::duration_cast<chrono::milliseconds>(stopBubble - startBubble);
                    
                    // Displaying outcome
                    cout << "\n[Quick Sort Time: " << (durationQuick.count()/1000) << " seconds]\t";
                    cout << "[Bubble Sort Time: " << (durationBubble.count()/1000) << " seconds]" << endl;
                } else {
                    // Quick Sort
                    chrono::high_resolution_clock::time_point startQuick = chrono::high_resolution_clock::now();
                    cout << "\nPerforming Quick Sort...\n";
                    quickSortLocationAscending(list1.getHead(),list1.getTail());
                    cout << "\nFinished Quick Sorting\n";
                    chrono::high_resolution_clock::time_point stopQuick = chrono::high_resolution_clock::now();
                    chrono::milliseconds durationQuick = chrono::duration_cast<chrono::milliseconds>(stopQuick - startQuick);

                    // Bubble Sort
                    chrono::high_resolution_clock::time_point startBubble = chrono::high_resolution_clock::now();
                    cout << "\nPerforming Bubble Sort...\n";
                    BubbleSortLocationAscending(&list2);
                    cout << "\nFinished Bubble Sorting\n";
                    chrono::high_resolution_clock::time_point stopBubble = chrono::high_resolution_clock::now();
                    chrono::milliseconds durationBubble = chrono::duration_cast<chrono::milliseconds>(stopBubble - startBubble);
                    
                    // Displaying outcome
                    cout << "\n[Quick Sort Time: " << (durationQuick.count()/1000) << " seconds]\t";
                    cout << "[Bubble Sort Time: " << (durationBubble.count()/1000) << " seconds]" << endl;
                }
            }            
        } else {
            string searchCriteria;
            do {
                cout << "\n\nSelect searching criteria, [1]Completion Year or [2]Property ID: ";
                cin >> searchCriteria;
                if (searchCriteria != "1" && searchCriteria != "2"){
                    cout << "Invalid option, please try again.\n\n";
                }
            } while (searchCriteria != "1" && searchCriteria != "2");

            long searchInput;
            cout << "Enter search key (integers only): ";

            while (!(cin >> searchInput)) {
                // Clear the error flag set by the failed input
                cin.clear();

                // Remove invalid input from the stream
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Invalid input. Please enter an integer: ";
            }

            if (searchCriteria == "1"){

                // Linear Search
                auto startLinearTime = chrono::high_resolution_clock::now();
                cout << "\nPerforming Linear Search...\n";
                LinearSearchTest(list1.getHead(),to_string(searchInput),BY_YEAR);
                auto endLinearTime = chrono::high_resolution_clock::now();
                auto durationLinear = chrono::duration_cast<chrono::milliseconds>(endLinearTime-startLinearTime);
                cout << "\nFinished Linear Searching\n";

                // Binary Search
                quickSortForBinary(list1.getHead(),list1.getTail(), BY_YEAR);// so that the time for this to complete is not taken into account
                auto startBinaryTime = chrono::high_resolution_clock::now();
                cout << "\nPerforming Binary Search...\n";
                displayResults4Test(list1.getHead(),searchInput,BY_YEAR);
                auto endBinaryTime = chrono::high_resolution_clock::now();
                auto durationBinary = chrono::duration_cast<chrono::milliseconds>(endBinaryTime-startBinaryTime);
                cout << "\nFinished Binary Searching\n";
                
                // Displaying outcome
                cout << "\n[Linear Search Time: " << (durationLinear.count()) << " milliseconds]\t";
                cout << "[Binary Search Time: " << (durationBinary.count()) << " milliseconds]" << endl;

            } else {

                // Linear Search
                auto startLinearTime = chrono::high_resolution_clock::now();
                cout << "\nPerforming Linear Search...\n";
                LinearSearchTest(list1.getHead(),to_string(searchInput),BY_ID);
                auto endLinearTime = chrono::high_resolution_clock::now();
                auto durationLinear = chrono::duration_cast<chrono::milliseconds>(endLinearTime-startLinearTime);
                cout << "\nFinished Linear Searching\n";

                // Binary Search
                quickSortForBinary(list1.getHead(),list1.getTail(), BY_ID);// so that the time for this to complete is not taken into account
                auto startBinaryTime = chrono::high_resolution_clock::now();
                cout << "\nPerforming Binary Search...\n";
                displayResults4Test(list1.getHead(),searchInput,BY_ID);
                auto endBinaryTime = chrono::high_resolution_clock::now();
                auto durationBinary = chrono::duration_cast<chrono::milliseconds>(endBinaryTime-startBinaryTime);
                cout << "\nFinished Binary Searching\n";
                
                
                // Displaying outcome
                cout << "\n[Linear Search Time: " << (durationLinear.count()) << " milliseconds]\t";
                cout << "[Binary Search Time: " << (durationBinary.count()) << " milliseconds]" << endl;
            
            }
        }
    }
    
};

#endif