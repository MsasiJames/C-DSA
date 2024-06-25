#ifndef MANAGER_H
#define MANAGER_H

#include "User.h"

using namespace std;

class Manager : public User {
private:
    bool isActive;
    DoublyLinkedList<Property>* demandProp;

public:
    Manager(const string& username, const string& password) 
    : User(username, password), isActive(true) {}

    void displayMenu() {
        cout << "\n--- MANAGER MENU ---\n";
        cout << "1. Create Tenant\n";
        cout << "2. Display and Delete Unactive Tenants\n";
        cout << "3. Display all Tenant's Details\n";
        cout << "4. Search for Tenant by username\n";
        cout << "5. Generate Report\n";
        cout << "6. Manage Tenancy Process\n";
        cout << "7. Logout\n";
        cout << "Enter choice: ";
    }

    bool getStatus() const {
        return isActive;
    }

    void deactivate() {
        isActive = false;
    }

    void activate() {
        isActive = true;
    }

    void generateReport(){
        BubbleSortCount(propertyList);
        string cont;

        cout << "\t\t\t\t\t\t\t\t\tTop 10 Favored Properties:" << endl;
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        for(int i = 0; i < 10; i++){
            Property prop = propertyList->getNode(i)->data;
            cout << "Rank: " << i + 1 << endl;
            cout << "\nFavored by: " << prop.favCount << " users\n";
            DisplayProperty(prop);
        }
        cout << "\t\t\t\t\t\t\t\t\t\tEnd of Report\n";
    }

    bool showDemandProp(){
        bool empty = false;
        demandProp = getPropWReq(propertyList->getHead());
        //cout << propertyList->getSize() << endl;
        DoublyNode<Property>* p = propertyList->getHead();
        Property prop = p->data;
        cout << prop.ads_id << "\t||\t" <<prop.reqCount << endl;
        quickSortRCount(demandProp->getHead(),demandProp->getTail());
        cout << "\t\t\t\t\t\t\t\t\t\tList of Properties in Demand - User: " << getUsername();
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"; 
        if (demandProp->getHead() == nullptr){
            cout << "The list is empty." << endl;
            cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            empty = true;
            return empty;
        }

        DoublyNode<Property>* current = demandProp->getHead();
        while (current){
            Property prop = current->data;
            cout << "\n\t\t\t\t\t\t\t\t\t\tREQUEST COUNT: " << prop.reqCount;
            DisplayProperty(prop);
            current = current->next;
        }
        return empty;
    }
    
    bool RRManage(Property* propPtr) {
        Queue<RentRequest>* qPtr = propPtr->requestQ;
        RentRequest* req = qPtr->peek(); // Assuming front() returns a pointer to the actual RentRequest
        bool DLT = false;
        cout << "\t\t\t\t\t\t\t\t\t\tCURRENT RENT REQUEST OF " << propPtr->ads_id;
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        DisplayRentRequestForManager(*req);
        if (req->status == "Pending") {
            string confirm;
            cout << "\nThe request is pending, are you sure you want to approve this request?\n";
            cout << "Press any key to proceed, or press 'no' to cancel: ";
            cin >> confirm;
            if (!(confirm == "no")) {
                system("cls");
                req->setApproved();
                req->updateTimestamp();
                cout << "The Request " << req->id << " has been approved.\n";
            }
        } else if (req->status == "Approved, Pending for Payment") {
            string confirm;
            cout << "\nPayment is pending, are you sure you want to approve the payment this request?\n";
            cout << "Press any key to proceed, or press 'no' to cancel: ";
            cin >> confirm;
            if (!(confirm == "no")) {
                system("cls");
                req->setPaid();
                req->updateTimestamp();
                cout << "The Payment of " << req->id << " has been approved.\n";
            }
        } else {
            string confirm;
            cout << "\nThe rent is in progress, are you sure you want to terminate this request?\n";
            cout << "Press any key to proceed, or press 'no' to cancel: ";
            cin >> confirm;
            if (!(confirm == "no")) {
                system("cls");
                DLT = true;
                return DLT;
            }
        }

        return DLT;
    }

    void chooseProp4RRManage(){
        system("cls");
        if(!showDemandProp()){
            string searchInput;
            cout << "Enter property ID of which property's request you wanted to manage: ";
            cin >> searchInput;
            if(SpecificSearch(demandProp->getHead(),searchInput)){
                string confirm;
                cout << "\nIs this the property you want to manage?\n";
                cout << "Press any key to proceed, or press 'no' to cancel: ";
                cin >> confirm;
                if (!(confirm == "no")){
                    system("cls");
                    DoublyNode<Property>* target = SearchForNode(demandProp->getHead(),searchInput);
                    if(!demandProp->exists(target->data)){
                        system("cls");
                        cout << "Failed to access the request of this property.\n";
                    } else{
                        DoublyNode<Property>* actual = SearchForNode(propertyList->getHead(),searchInput);
                        system("cls");
                        cout << "Managing rent request of property " << actual->data.ads_id << " ...\n";
                        if(RRManage(&(actual->data))){
                            Property* pPtr = &(actual->data);
                            Queue<RentRequest>* qPtr = pPtr->requestQ;
                            RentRequest terminatedReq = *(qPtr->peek());  // Copy the data before deleting
                            qPtr->popOut();
                            pPtr->decrementReqCount();
                            cout << "The request " << terminatedReq.id << " has been terminated and deleted.\n";
                        }
                    }
                }
            }
        }       
    }

};

#endif