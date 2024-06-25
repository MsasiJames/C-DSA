#ifndef USER_H
#define USER_H

#include "SortingMethods.h"
#include "SearchingMethods.h"
#include "SinglyLinkedList.h"
#include <iomanip>

using namespace std;

class AccCredential {
private:
    string username;
    string password;

public:
    AccCredential(const string& user, const string& pass)
        : username(user), password(pass) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }

    bool verifyPassword(const string& pass) const {
        return password == pass;
    }
};

class User {
protected:
    AccCredential credentials;

public:

    DoublyLinkedList<Property>* propertyList;

    User(const string& username, const string& password) 
    : credentials(username, password) {}

    virtual ~User() {}

    string getUsername() const {
        return credentials.getUsername();
    }

    DoublyLinkedList<Property>* getPropertyList() {
        return propertyList;
    }

    void setPropertyList(DoublyLinkedList<Property>* list){
        propertyList = list;
    }

    bool verifyPassword(const string& password) const {
        return credentials.verifyPassword(password);
    }

    const AccCredential& getAccCredential() const {
        return credentials;
    }

    void display30() {
        int currentPage = 1;
        const int rowsPerPage = 30;
        bool isDisplaying = true;

        while (isDisplaying) {
            system("cls");
            cout << "\t\t\t\t\t\t\t\t\t\tPROPERTY DETAILS\n";
            cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            DoublyNode<Property>* temp = propertyList->getHead();
            
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
        system("cls");
    }

    void waitForKeyPress() {
        cout << "Press enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the buffer
        cin.get();  // Wait for user input
        system("cls");
    }

};

class HashTable {
private:
    SinglyLinkedList<pair<string, User*>>* table;
    int numBuckets;

    int hashFunction(const string& key) const {
        unsigned long hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % numBuckets;
    }

public:
    HashTable(int numBuckets = 100) : numBuckets(numBuckets) {
        table = new SinglyLinkedList<pair<string, User*>>[numBuckets];
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(const string& key, User* value) {
        pair<string, User*> newPair(key, value);
        int bucketIndex = hashFunction(key) % numBuckets;
        table[bucketIndex].push_back(newPair);
        //debugging purpose
        //cout << "Inserted user with username: " << key << " into bucket: " << bucketIndex << endl;
    }

    User* get(const string& key) const {
        int bucketIndex = hashFunction(key) % numBuckets;
        auto nodeIter = table[bucketIndex].find(
            pair<string, User*>(key, nullptr),
            [](const pair<string, User*>& a, const pair<string, User*>& b) {
                return a.first == b.first;
            }
        );

        if (nodeIter != nullptr) {
            //debugging purpose
            //cout << "Retrieved user with username: " << key << " from bucket: " << bucketIndex << endl;
            return nodeIter->data.second;
        }

        //debugging purpose
        //cout << "Failed to retrieve user with username: " << key << endl;
        return nullptr;
    }

    void remove(const string& key) {
        int bucketIndex = hashFunction(key) % numBuckets;
        auto nodeIter = table[bucketIndex].find(
            pair<string, User*>(key, nullptr),
            [](const pair<string, User*>& a, const pair<string, User*>& b) {
                return a.first == b.first;
            }
        );

        if (nodeIter) {
            table[bucketIndex].remove(nodeIter->data);
        }
    }

    bool exists(const string& key) const {
        int bucketIndex = hashFunction(key) % numBuckets;
        return table[bucketIndex].find(
            pair<string, User*>(key, nullptr),
            [](const pair<string, User*>& a, const pair<string, User*>& b) {
                return a.first == b.first;
            }
        ) != nullptr;
    }

    DynamicArray<string> getAllKeys() const {
        DynamicArray<string> keys;
        for (int i = 0; i < numBuckets; i++) {
            DynamicArray<pair<string, User*>> bucketData = table[i].getAllData();
            for (int j = 0; j < bucketData.size(); j++) {
                keys.add(bucketData.get(j).first);
                //debugging purpose
                //cout << "Added key: " << bucketData.get(j).first << " from bucket: " << i << " to keys" << endl;
            }
        }
        return keys;
    }

    SinglyNode<pair<string, User*>>* begin() const {
        for (int i = 0; i < numBuckets; i++) {
            if (table[i].begin() != nullptr) {
                return table[i].begin();
            }
        }
        return nullptr;
    }

    SinglyNode<pair<string, User*>>* end() const {
        for (int i = numBuckets - 1; i >= 0; i--) {
            if (table[i].end() != nullptr) {
                return table[i].end();
            }
        }
        return nullptr;
    }

};

#endif