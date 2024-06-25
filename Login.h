#ifndef LOGIN_H
#define LOGIN_H

#include "UserManager.h"
#include "ImportMethod.h"
#include <cstring>
#include <iostream>

using namespace std;

void loginMenu(){
    system("cls");
    UserManager userManager;
    DoublyLinkedList<Property> publicList;
    User* loggedInUser = nullptr;
    string choice;
    string username, password;
    if(importFromCsv("mudah-apartment-kl-selangor.csv", publicList)) {
        cout << "Data successfully imported from the CSV file.\n" << endl;
    } else {
        cout << "Failed to import data from the CSV file.\n" << endl;
    }
    
    while (true) {
        if (!loggedInUser) {
            cout << "Login, Register or Quit? (L/R/Q): ";
            cin >> choice;

            if (choice == "R" || choice == "r") {
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;

                system("cls");
                if (!userManager.registerTenant(username, password)) {
                    cout << "Username already exists or registration failed.\n";
                } else {
                    cout << "Tenant registered successfully!\n";
                }
                //userManager.displayAllUsers();        // To test if the users are stored correctly
            } else if (choice == "L" || choice == "l") {
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                
                system("cls");
                loggedInUser = userManager.loginUser(username, password);
                if (!loggedInUser) {
                    cout << "Login failed. Check username and password.\n";
                } else {
                    cout << "Logged in successfully as " << username << "!\n";
                }
            } else if (choice == "Q" || choice == "q") {
                cout << "\nExiting the program...\n\n";
                break;  // Exit the loop, thus ending the program
            } else {
                system("cls");
                cout << "Invalid Input!!!\n";
            }
        } else {
            Tenant* tenant = dynamic_cast<Tenant*>(loggedInUser);
            Manager* manager = dynamic_cast<Manager*>(loggedInUser);
            Admin* admin = dynamic_cast<Admin*>(loggedInUser);

            if (tenant) {
                tenant->setPropertyList(&publicList);
                tenant->displayMenu();
                int option;
                cin >> option;
                if (option == 5){
                    system("cls");
                    userManager.logoutUser(loggedInUser);
                    loggedInUser = nullptr;
                } else if (option == 1) {
                    system("cls");
                    tenant->sortAndDisplay();
                } else if (option == 2) {
                    system("cls");
                    tenant->searchForProperties();
                } else if (option == 3) {
                    system("cls");
                    tenant->FavoriteProperties();
                } else if (option == 4){
                    system("cls");
                    tenant->RentReqManagement();
                } else if (option == 6){
                    system("cls");
                    tenant->display30();
                }else {
                    system("cls");
                    cout << "invalid input";
                }

            } else if (manager) {
                if (manager->getStatus()){
                    manager->setPropertyList(&publicList);
                    manager->displayMenu();
                    string menuChoice;
                    cin >> menuChoice;
                    if (menuChoice == "1") {
                        system("cls");
                        string newID, newPW;
                        cout << "Enter tenant username: ";
                        cin >> newID;
                        cout << "Enter tenant password: ";
                        cin >> newPW;
                        if(userManager.registerTenant(newID, newPW)){
                            // Manager creates Tenant
                            system("cls");
                            cout << "Tenant " << newID << " created successfully!\n";
                        }else{
                            // Account already exists
                            system("cls");
                            cout << "Failed to create tenant account for " << newID << ". Account already existed.\n";
                        }
                    } else if (menuChoice == "2") {
                        system("cls");
                        userManager.displayAndDeleteUnactiveTenants();
                    } else if (menuChoice == "3") {
                        system("cls");
                        userManager.displayAllTenants();
                        manager->waitForKeyPress();
                    } else if (menuChoice == "4") {
                        system("cls");
                        string searchInput;
                        cout << "Enter the username you wanted to search for: ";
                        cin >> searchInput;
                        userManager.searchAndDisplayTenant(searchInput);
                        manager->waitForKeyPress();
                    } else if (menuChoice == "5") {
                        system("cls");
                        manager->generateReport();
                        manager->waitForKeyPress();
                        system("cls");
                    } else if (menuChoice == "6") {
                        system("cls");
                        manager->chooseProp4RRManage();
                        manager->waitForKeyPress();
                    } else if (menuChoice == "7") {
                        system("cls");
                        userManager.logoutUser(loggedInUser);
                        loggedInUser = nullptr;
                    } else {
                        system("cls");
                        cout << "Invalid choice.\n";
                    }
                } else {
                    system("cls");
                    cout << "Your account has been DEACTIVATED, please ask an admin to activate it\n";
                    loggedInUser = nullptr;
                }

            } else if (admin) {
                admin->setPropertyList(&publicList);
                admin->displayMenu();
                string menuChoice;
                cin >> menuChoice;
                if (menuChoice == "1") {
                    system("cls");
                    string newID, newPW;
                    cout << "Enter manager username: ";
                    cin >> newID;
                    cout << "Enter manager password: ";
                    cin >> newPW;
                    if(userManager.registerManager(newID, newPW)){
                        // Admin creates Manager
                        system("cls");
                        cout << "Manager " << newID << " created successfully!\n";
                    }else{
                        // Account already exists
                        system("cls");
                        cout << "Failed to create manager account for " << newID << ". Account already existed.\n";
                    }
                } else if (menuChoice == "2") {
                    system("cls");
                    userManager.displayAvailableManagers();
                    cout << "\n* Please enter anything other than manager username displayed to go back to menu without any action.\n";
                    cout << "\nEnter manager username to toggle activation: ";
                    cin >> username;
                    if (userManager.isManagerActive(username)) {
                        userManager.deactivateManager(username);
                    } else {
                        userManager.activateManager(username);
                    }
                } else if (menuChoice == "6") {
                    system("cls");
                    userManager.logoutUser(loggedInUser);
                    loggedInUser = nullptr;
                } else if (menuChoice == "3"){
                    system("cls");
                    admin->FilterProperty();
                } else if (menuChoice == "4"){
                    system("cls");
                    string status;
                    do {
                        cout << "Enter status (1 for active, 0 for inactive): ";
                        cin >> status;
                        if (status != "1" && status != "0"){
                            cout << "Invalid Option. Please try again.\n";
                        }
                    } while (status != "1" && status != "0");
                    if (status == "1"){
                        userManager.displayTenantsByStatus(true);
                    } else if (status == "0"){
                        userManager.displayTenantsByStatus(false);
                    }
                    admin->waitForKeyPress();
                } else if (menuChoice == "5"){
                    system("cls");
                    DoublyLinkedList<Property>* propList = admin->getPropertyList();
                    admin->AlgoCompare();
                    admin->waitForKeyPress();
                }else {
                    cout << "Invalid choice.\n";
                }
            }
        }
    }
}

#endif