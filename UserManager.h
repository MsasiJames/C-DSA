#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "admin.h"
#include "manager.h"
#include "tenant.h"

using namespace std;

class UserManager {
private:
    HashTable users;

public:
    UserManager() {
        // Default users for the system
        users.insert("admin1", new Admin("admin1", "password1"));
        users.insert("admin2", new Admin("admin2", "password2"));
    }

    User* loginUser(const string& username, const string& password) {
        if (users.exists(username)) {
            User* user = users.get(username);
            if (user->verifyPassword(password)) {
                Tenant* tenant = dynamic_cast<Tenant*>(user);
                if (tenant) {
                    tenant->markAsLoggedIn();  // Mark tenant as having logged in
                }
                return user;
            }
        }
        return nullptr;
    }

    // Function to display all exisiting users, for debugging purpose
    void displayAllUsers() {
        cout << "Displaying Users: \n";
        DynamicArray<string> allKeys = users.getAllKeys();
        // Debug: Print the total number of users.
        //cout << "[Debug] Total users: " << allKeys.size() << "\n";

        for (int i = 0; i < allKeys.size(); i++) {
            string username = allKeys.get(i);

            // Debug: Print the current user's username.
            //cout << "[Debug] Current username: " << username << "\n";

            User* user = users.get(username);
            if (user != nullptr) {
                cout << "Username: " << username
                    << ", Password: " << user->getAccCredential().getPassword() << "\n";
            } else {
                // Debug: If the user is null for some reason, print this.
                //cout << "[Debug] User object for username: " << username << " is nullptr.\n";
            }
        }
    }

    void displayAllTenants() {
        cout << "Displaying Tenants: \n\n";
        DynamicArray<string> allKeys = users.getAllKeys();
        for (int i = 0; i < allKeys.size(); i++) {
            string username = allKeys.get(i);
            User* user = users.get(username);
            Tenant* tenant = dynamic_cast<Tenant*>(user);
            if (tenant) {  // If the user is a tenant
                cout << "Username: " << username << "\n";
                cout << "Password: " << tenant->getAccCredential().getPassword() << "\n";
                cout << "Status: " << tenant->getStatus() << "\n\n";
            }
        }
    }

    void searchAndDisplayTenant(const string& searchUsername) {
        cout << "\n Search Results:\n\n";
        User* user = users.get(searchUsername);
        Tenant* tenant = dynamic_cast<Tenant*>(user);
        if (tenant) {  // If the user is a tenant
            cout << "Username: " << tenant->getUsername() << "\n";
            cout << "Password: " << tenant->getAccCredential().getPassword() << "\n";
            cout << "Status: " << tenant->getStatus() << "\n\n";
        } else {
            cout << "Tenant with username '" << searchUsername << "' not found.\\n";
        }
    }


    bool registerTenant(const string& username, const string& password) {
        if(!users.exists(username)) {
            Tenant* newTenant = new Tenant(username, password);
            users.insert(username, newTenant);  // Storing the new tenant in the users map
            return true;
        }
        return false;
    }

    bool registerManager(const string& username, const string& password) {
        if(!users.exists(username)) {
            Manager* newManager = new Manager(username, password);
            users.insert(username, newManager);  // Storing the new manager in the users map
            return true;
        }
        return false;
    }

    bool isManagerActive(const string& username) {
        Manager* manager = dynamic_cast<Manager*>(users.get(username));
        if (manager) {
            return manager->getStatus();
        }
        return false;  // Return false if user not found
    }

    void displayAvailableManagers() {
        cout << "\nAvailable Managers:\n";
        DynamicArray<string> usernames = users.getAllKeys();
        for(const auto& username : usernames) {
            User* user = users.get(username);
            if (user != nullptr) {
                //dp
                //cout << "Retrieved user with username: " << username << "\n";  // Debug print statement
                Manager* manager = dynamic_cast<Manager*>(user);
                if (manager) {
                    cout << manager->getUsername() << " (";
                    cout << (manager->getStatus() ? "Active" : "Inactive") << ")\n";
                }
            } else {
                cout << "Failed to retrieve user with username: " << username << "\n";  // Debug print statement
            }
        }
    }

    void displayTenantsByStatus(bool isActive) {
        cout << (isActive ? "Active Tenants:" : "Inactive Tenants:");
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"; 
        DynamicArray<string> allUsernames = users.getAllKeys();
        
        for (const auto& username : allUsernames) {
            User* user = users.get(username);
            Tenant* tenant = dynamic_cast<Tenant*>(user);
            
            if (tenant && tenant->getStatus() == isActive) {
                cout << "\nUsername: " << tenant->getUsername() << "\n";
                cout << "Password: " << tenant->getAccCredential().getPassword() << "\n";
                cout << "Status: ";
                if (tenant->getStatus()){cout << "Active\n";} 
                else {cout << "Inactive\n";}
                cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"; 
            }
        }
    }

    void deactivateManager(string username) {
        Manager* manager = dynamic_cast<Manager*>(users.get(username));
        system("cls");
        if (manager) {
            manager->deactivate();
            cout << "Manager " << username << " deactivated.\n";
        } else {
            cout << "Manager not found.\n";
        }
    }

    void activateManager(string username) {
        Manager* manager = dynamic_cast<Manager*>(users.get(username));
        system("cls");
        if (manager) {
            manager->activate();
            cout << "Manager " << username << " activated.\n";
        } else {
            cout << "Manager not found.\n";
        }
    }


    void displayAndDeleteUnactiveTenants() {
        cout << "\nUnactive Tenants:\n";
        DynamicArray<string> usernames = users.getAllKeys();
        for(const auto& username : usernames) {
            User* user = users.get(username);
            if (user != nullptr) {
                //debugging purpose (dp)
                //cout << "Retrieved user with username: " << username << "\n";  // Debug print statement
                Tenant* tenant = dynamic_cast<Tenant*>(user);
                if (tenant && !tenant->getStatus()) {
                    cout << tenant->getUsername() << "\n";
                }
            } else {
                cout << "Failed to retrieve user with username: " << username << "\n";  // Debug print statement
            }
        }
        string usernameToDelete;
        cout << "\n* Please enter anything other than manager username displayed to go back to menu without any action.\n\n";
        cout << "Enter the username of the tenant to delete (or type 'exit' to return): ";
        cin >> usernameToDelete;
        if (usernameToDelete != "exit") {
            if (users.exists(usernameToDelete)) {
                users.remove(usernameToDelete);
                system("cls");
                cout << "Tenant " << usernameToDelete << " deleted.\n";
            } else {
                system("cls");
                cout << "Tenant not found.\n";
            }
        } else system("cls");
    }

    void logoutUser(User* user) {
        cout << "User " << user->getUsername() << " logged out.\n";
    }
};

#endif