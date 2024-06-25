#include "ImportMethod.h"
#include "SortingMethods.h"
#include "DoublyLinkedList.h"
#include "Property.h"
#include <iostream>

using namespace std;

void display30(DoublyLinkedList<Property>){};

void DisplayProperty(const Property& prop) {

    Property p = prop;

    cout << " ID: "<< p.ads_id << " \n ";
        cout << " Name: "<< p.prop_name << " \n ";
        if (p.completion_year == -1){
            cout << " Completion Year: Unknown\n ";
        }else{
            cout << " Completion Year: "<< p.completion_year << " \n ";
        }
        cout << " Monthly Rent: "<< p.monthly_rent << " \n ";
        cout << " Location: "<< p.location << " \n ";
        cout << " Type: "<< p.property_type << " \n ";
        if (p.rooms == 99){
            cout << " Rooms: More than 10\n ";
        }else if (p.rooms == 88){
            cout << " Rooms: Unknown\n";
        }else{
            cout << " Rooms: "<< p.rooms << " \n ";
        }
        if (p.parking == 99){
            cout << " Parking: Unknown\n ";
        }else{
            cout << " Parking: "<< p.parking << " \n ";
        }
        if (p.bathroom == 99){
            cout << " Bathroom: Unknown\n";
        }else{
            cout << " Bathroom: "<< p.bathroom << " \n ";
        }
        cout << " Size: "<< p.size << " \n ";
        cout << " Furnished: "<< p.furnished << " \n ";
        cout << " Facilities: "<< p.facilities << " \n ";
        cout << " Additional Facilities: "<< p.additional_facilities << " \n ";
        cout << " Region: "<< p.region;
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

int main(){
    DoublyLinkedList<Property> propertyList;

    if(importFromCsv("mudah-apartment-kl-selangor.csv",propertyList)) {
        cout << "Data successfully imported from the CSV file." << endl;
    } else {
        cout << "Failed to import data from the CSV file." << endl;
    }

    int sortChoice;
        do {
            cout << "To sort by monthly rent(1), by square feet(2), by location(3): ";
            cin >> sortChoice;
            if (cin.fail() || sortChoice < 1 || sortChoice > 3) {
                cout << "Invalid choice. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (sortChoice < 1 || sortChoice > 3);

        int algoChoice;
        do {
            cout << "For bubble sort(1) for quick sort(2): ";
            cin >> algoChoice;
            if (cin.fail() || algoChoice < 1 || algoChoice > 2) {
                cout << "Invalid choice. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (algoChoice < 1 || algoChoice > 2);

        int order;
        do {
            cout << "For descending order(1) for ascending order(2): ";
            cin >> order;
            if (cin.fail() || order < 1 || order > 2) {
                cout << "Invalid choice. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (order < 1 || order > 2);

        cout << "Loading..." << endl;

        if (sortChoice == 1){
            if (algoChoice == 1){
                if (order == 1){
                    cout << "Sorting ...\n";
                    BubbleSortRent(propertyList);
                    cout << "Sorted\n";
                }else if (order == 2){
                    cout << "Sorting ...\n";
                    BubbleSortRentAscending(propertyList);
                    cout << "Sorted\n";
                }
            } else if (algoChoice == 2) {
                if (order == 1){
                    cout << "Sorting ...\n";
                    quickSortRent(propertyList.getHead(),propertyList.getTail());
                    cout << "Sorted\n";
                    system("cls");
                }else if (order == 2){
                    cout << "Sorting ...\n";
                    quickSortRentAscending(propertyList.getHead(),propertyList.getTail());
                    cout << "Sorted\n";
                    system("cls");
                }
            }
        } else if (sortChoice == 2){
            if (algoChoice == 1){
                if (order == 1){
                    cout << "Sorting ...\n";
                    BubbleSortSize(propertyList);
                    cout << "Sorted\n";
                    system("cls");
                }else if (order == 2){
                    cout << "Sorting ...\n";
                    BubbleSortSizeAscending(propertyList);
                    cout << "Sorted\n";
                    system("cls");
                }
            } else if (algoChoice == 2) {
                if (order == 1){
                    cout << "Sorting ...\n";
                    quickSortSize(propertyList.getHead(),propertyList.getTail());
                    cout << "Sorted\n";
                    system("cls");
                }else if (order == 2){
                    cout << "Sorting ...\n";
                    quickSortSizeAscending(propertyList.getHead(),propertyList.getTail());
                    cout << "Sorted\n";
                    system("cls");
                }
            }
        } else if (sortChoice == 3){
            if (algoChoice == 1){
                if (order == 1){
                    BubbleSortLocation(propertyList);
                }else if (order == 2){
                    BubbleSortLocationAscending(propertyList);
                }
            } else if (algoChoice == 2) {
                if (order == 1){
                    quickSortLocation(propertyList.getHead(),propertyList.getTail());
                }else if (order == 2){
                    quickSortLocationAscending(propertyList.getHead(),propertyList.getTail());
                }
            }
        }

        display30(propertyList);
}

void display30(DoublyLinkedList<Property> propertyList) {
        int currentPage = 1;
        const int rowsPerPage = 30;
        bool isDisplaying = true;

        while (isDisplaying) {
            system("cls");
            cout << "\t\t\t\t\t\t\t\t\t\tPROPERTY DETAILS\n";
            cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            DoublyNode<Property>* temp = propertyList.getHead();
            
            // Skip nodes to reach the starting doublynode of the currentPage
            for (int i = 0; i < (currentPage - 1) * rowsPerPage && temp; ++i) {
                temp = temp->next;
            }

            // Display up to 30 nodes
            for (int i = 0; i < rowsPerPage && temp; ++i) {
                Property prop = temp->data;
                DisplayProperty(prop);
                temp = temp->next;
            }

            // User prompt for navigation
            char choice;
            cout << "\nCurrent Page: " << currentPage;
            cout << "\n[N]ext page, [P]revious page, [Q]uit: ";
            cin >> choice;

            switch (toupper(choice)) {
                case 'N':
                    currentPage++;
                    break;
                case 'P':
                    if (currentPage > 1) currentPage--;
                    break;
                case 'Q':
                    isDisplaying = false;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
        }
    };