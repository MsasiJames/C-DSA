#ifndef TENANT_H
#define TENANT_H

#include "User.h"
#include "SinglyLinkedList.h"

using namespace std;

class Tenant : public User {
private:
    bool status;
    bool hasLoggedIn;
    DoublyLinkedList<Property> FavList;
    SinglyLinkedList<RentRequest*> ReqList;

public:
    Tenant(const string& username, const string& password) 
    : User(username, password), status(false) {}
    
    void displayMenu() {
        cout << "\n--- TENANT MENU ---\n";
        cout << "1. Display Property Details\n";
        cout << "2. Search for Properties\n";
        cout << "3. Save Favorite Properties\n";
        cout << "4. Manage Rent Request\n";
        cout << "5. Logout\n";
        cout << "Enter choice: ";
    }

    void sortAndDisplay(){
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
                    quickSortRent(propertyList->getHead(),propertyList->getTail());
                    cout << "Sorted\n";
                    system("cls");
                }else if (order == 2){
                    cout << "Sorting ...\n";
                    quickSortRentAscending(propertyList->getHead(),propertyList->getTail());
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
                    quickSortSize(propertyList->getHead(),propertyList->getTail());
                    cout << "Sorted\n";
                    system("cls");
                }else if (order == 2){
                    cout << "Sorting ...\n";
                    quickSortSizeAscending(propertyList->getHead(),propertyList->getTail());
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
                    quickSortLocation(propertyList->getHead(),propertyList->getTail());
                }else if (order == 2){
                    quickSortLocationAscending(propertyList->getHead(),propertyList->getTail());
                }
            }
        }

        display30();
    }

    void searchForProperties(){
        int searchChoice;
        int algoChoice;

        do {
            // Prompt and get input for searchChoice
            cout << "To search using Property name(1), Location(2), Completion year(3): ";
            cin >> searchChoice;

            // Prompt and get input for algoChoice
            cout << "For linear search (1), binary search (2), use binary search only for completion year search: ";
            cin >> algoChoice;
            cin.ignore();

            // Check if the user provided valid input
            if ((searchChoice >= 1 && searchChoice <= 3) &&
                (algoChoice == 1 || (algoChoice == 2 && searchChoice == 3))) {
                break;  // Exit the loop if input is valid
            } else {
                cout << "Invalid input. Please try again.\n";
            }
        } while (true);

        string data;
        cout << "Enter search data: ";
        getline(cin, data);

        system("cls");

        cout << "Current search criteria set to: " << setCriteria(searchChoice-1) << endl;
        cout << "Searching for: " << data << "... ...\n";

        if(algoChoice == 1){
            LinearSearch(propertyList->getHead(),data,setCriteria(searchChoice-1));
        }else if(algoChoice == 2){
            int numData = stoi(data);
            // NEED TO SORT THE DATA FIRST FOR BINARY SEARCH
            quickSortForBinary(propertyList->getHead(), propertyList->getTail(),setCriteria(searchChoice-1));
            displayResults(propertyList->getHead(),numData,setCriteria(searchChoice-1));
        }
    }

    void savePropertyToList(){
        string searchInput;
        cout << "Enter Property ID to save: ";
        cin >> searchInput;
        if(SpecificSearch(propertyList->getHead(),searchInput)){
            string confirm;
            cout << "\nAre you sure you want to save this as favorite?\n";
            cout << "Press any key to proceed, or press 'no' to cancel: ";
            cin >> confirm;
            if (!(confirm == "no")){
                system("cls");
                DoublyNode<Property>* target = SearchForNode(propertyList->getHead(),searchInput);
                if(FavList.exists(target->data)){
                    cout << "Failed to add property, the Property is already in your favorite list.\n";
                } else{
                    FavList.append(target->data);
                    target->data.incrementFavCount();
                    cout << "Property " << target->data.ads_id << " has been added to your favorite list.\n";
                }
            }
        }
    }

    void removePropertyFromList(){
        string searchInput;
        cout << "Enter Property ID to remove: ";
        cin >> searchInput;
        if(SpecificSearch(FavList.getHead(),searchInput)){
            cout << "After SpecificSearch, before SearchForNode" << endl;
            string confirm;
            cout << "\nAre you sure you want to remove this from favorite?\n";
            cout << "Press any key to proceed, or press 'no' to cancel: ";
            cin >> confirm;
            if (!(confirm == "no")){
                system("cls");
                DoublyNode<Property>* target = SearchForNode(FavList.getHead(),searchInput);
                DoublyNode<Property>* foundNode = FavList.find(target->data);
                if (foundNode != nullptr) {
                    cout << "Property found with ID: " << foundNode->data.ads_id << endl;
                } else {
                    cout << "Property not found using find method." << endl;
                }
                if(!FavList.exists(target->data)){
                    cout << "Failed to remove property, the property is not in your favorite list.\n";
                } else{
                    FavList.remove(target->data);
                    target->data.decrementFavCount();
                    cout << target->data.favCount << endl;
                    cout << "Property " << target->data.ads_id << " has been removed from your favorite list.\n";
                }
            }   
        }
        
    }

    void displayAllFavorites(){
        cout << "\t\t\t\t\t\t\t\t\t\tFavorite List of " << getUsername();
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"; 
        if (!FavList.getHead()){
            cout << "The list is empty." << endl;
            return;
        }

        DoublyNode<Property>* current = FavList.getHead();
        while (current){
            Property prop = current->data;
            DisplayProperty(prop);
            current = current->next;
        }
    }

    void FavoriteProperties(){
        system("cls");
        int option;
        while (true) {  // This will loop until the user decides to exit
            cout << "To add a favorite property (1), to remove a favorite property(2), to print current list(3), exit(4): ";
            cin >> option;
            switch(option) {
                case 1:
                    savePropertyToList();
                    break;
                case 2:
                    displayAllFavorites();
                    removePropertyFromList();
                    break;
                case 3:
                    displayAllFavorites();
                    break;
                case 4:
                    return;  // Exit the function
                default:
                    cout << "Wrong option!!!\n";
                    break;
            }
        }
    }

    void placeRequest(){
        system("cls");
        displayAllFavorites();
        string input;
        cout << "Enter the property ID of which you wanted to place request: ";
        cin >> input;
        //cout << "Before calling searchNode\n";

        DoublyNode<Property>* target = SearchForNode(FavList.getHead(),input);
        if (target == nullptr){
            system("cls");
            cout << "Failed to place rent request. There was no such property in your favorite list.\n";
        } else {
            DoublyNode<Property>* actual = SearchForNode(propertyList->getHead(),input);
            if (actual == nullptr){
                system("cls");
                cout << "Failed to place rent request. Unable to access the property.";
            } else {
                system("cls");
                RentRequest newReq = RentRequest(actual->data.generateNewReqID(),getUsername(),to_string(actual->data.ads_id));
                // cout << "rr done\n";
                Property* prop = &(actual->data);
                // cout << "prop done\n";
                Queue<RentRequest>* qPtr = prop->requestQ;
                // if (qPtr == nullptr){
                //     cout << "debug\n";
                // } else {
                //     cout << "ok\n";
                // }
                // cout << "q done\n";
                qPtr->push(newReq);
                // cout << "push done\n";
                prop->incrementReqCount();
                // cout << "incre done\n";
                ReqList.push_back(&newReq);
                // cout << "push2 done\n";
                cout << "You have successfully placed a request for " << actual->data.ads_id << endl;
                cout << "Request count for " << actual->data.ads_id << " is now " << actual->data.reqCount << endl;
            }
            
        }

    }

    void displayAllRequests(){
        cout << "\t\t\t\t\t\t\t\t\t\tRequest List of " << getUsername();
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"; 
        if (!ReqList.getHead()){
            cout << "The list is empty." << endl;
            return;
        }
        try{
            SinglyNode<RentRequest*>* current = ReqList.getHead();
            while (current != nullptr){
                RentRequest* reqPtr = current->data;
                RentRequest req = *reqPtr;
                DisplayRentRequestForTenant(req);
                current = current->next;
            }
        } catch (exception& e){
            cout << e.what() << endl;
        }
    }
    
    void RentReqManagement() {
        int choice;
        while (true) {  // This will loop until the user decides to exit
            do {
                cout << "To see current request list(1), to place a request(2), to exit(3): ";
                cin >> choice;
                if (cin.fail() || choice < 1 || choice > 3) {
                    cout << "Invalid choice. Please try again." << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } while (choice < 1 || choice > 3);

            switch(choice) {
                case 1:
                    displayAllRequests();
                    break;
                case 2:
                    placeRequest();
                    break;
                case 3:
                system("cls");
                    return;  // Exit the function
                default:
                    cout << "Wrong option!!!\n";
                    break;
            }
        }
    }
    
    void deactivate() {
        status = false;
    }

    void activate() {
        status = true;
    }

    void markAsLoggedIn() {
        hasLoggedIn = true;
        status = true;
    }

    bool getStatus() const{
        return status && hasLoggedIn;  // Active only if registered and has logged in
    };
};

#endif