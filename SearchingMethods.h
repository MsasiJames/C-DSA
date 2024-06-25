#ifndef SEARCHINGMETHODS_H
#define SEARCHINGMETHODS_H

#include "DoublyLinkedList.h"
#include "Property.h"
#include "RentRequest.h"
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

void DisplayProperty(const Property& prop) {

    Property p = prop;

    cout << " ID: "<< p.ads_id << " \n ";
        cout << " Name: "<< p.prop_name << " \n ";
        if (p.completion_year == -1){
            cout << " Completion Year: Unknown\n ";
        }else{
            cout << " Completion Year: "<< p.completion_year << " \n ";
        }
        if (p.monthly_rent == "-1"){
            cout << " Monthly Rent (RM per month): Unknown\n ";
        }else{
            cout << " Monthly Rent (RM per month): "<< p.monthly_rent << " \n ";
        }
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
        if (p.size == "-1"){
            cout << " Size (sq.ft.): Unknown\n";
        }else{
            cout << " Size (sq.ft.): "<< p.size << " \n ";
        }
        cout << " Furnished: "<< p.furnished << " \n ";
        cout << " Facilities: "<< p.facilities << " \n ";
        cout << " Additional Facilities: "<< p.additional_facilities << " \n ";
        cout << " Region: "<< p.region;
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void DisplayPropertywCount(const Property& prop) {

    Property p = prop;

    cout << " ID: "<< p.ads_id << " \n ";
        cout << " Name: "<< p.prop_name << " \n ";
        if (p.completion_year == -1){
            cout << " Completion Year: Unknown\n ";
        }else{
            cout << " Completion Year: "<< p.completion_year << " \n ";
        }
        if (p.monthly_rent == "-1"){
            cout << " Monthly Rent (RM per month): Unknown\n ";
        }else{
            cout << " Monthly Rent (RM per month): "<< p.monthly_rent << " \n ";
        }
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
        if (p.size == "-1"){
            cout << " Size (sq.ft.): Unknown\n";
        }else{
            cout << " Size (sq.ft.): "<< p.size << " \n ";
        }
        cout << " Furnished: "<< p.furnished << " \n ";
        cout << " Facilities: "<< p.facilities << " \n ";
        cout << " Additional Facilities: "<< p.additional_facilities << " \n ";
        cout << " Region: "<< p.region << "\n";
        cout << " Favored by: " << p.favCount << " users\n";
        cout << " Number of Queuing Rent Request(s): " << p.reqCount;
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void DisplayRentRequestForTenant(const RentRequest& req){
    cout << "ID: " << req.id << endl;
    cout << "Property ID: " << req.pID << endl;
    cout << "Last Modified Time: " << req.timeStamp << endl;
    cout << "Status: " << req.status << endl;
    cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void DisplayRentRequestForManager(const RentRequest& req){
    cout << "ID: " << req.id << endl;
    cout << "Tenant ID: " << req.tID << endl;
    cout << "Last Modified Time: " << req.timeStamp << endl;
    cout << "Status: " << req.status << endl;
    cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

enum SearchCriteria {
    BY_NAME,
    BY_LOCATION,
    BY_YEAR,
    BY_ID
};

SearchCriteria setCriteria(int choice) {
    switch (choice) {
        case 0:
            return SearchCriteria::BY_NAME;
        case 1:
            return SearchCriteria::BY_LOCATION;
        case 2:
            return SearchCriteria::BY_YEAR;
        default:
            throw std::invalid_argument("Invalid choice for search criterion.");
    }
}

// LINEAR SEARCH
void LinearSearch(DoublyNode<Property> *low, string searchInput, SearchCriteria option) {
    DoublyLinkedList<DoublyNode<Property>*> results;  // Using DoublyLinkedList to store matching results

    for (DoublyNode<Property> *i = low; i != nullptr; i = i->next) {
        Property prop = i->data;
        bool match = false;
        

        switch (option) {
            case BY_NAME:
                match = (searchInput.compare(prop.prop_name) == 0);
                break;
            case BY_LOCATION:
                match = (searchInput.compare(prop.location) == 0);
                break;
            case BY_YEAR:
                try {
                    int year = stoi(searchInput);
                    match = (year == prop.completion_year);
                } catch (exception&) {
                    cout << "Invalid year input. Please ensure it's a number." << endl;
                    return;
                }
                break;
            default:
                cout << "Invalid search criteria." << endl;
                return;
        }

        if (match) {
            results.append(i);
        }
    }

    if (results.getSize() == 0) {
        cout << "Search term not found\n";
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        return;
    }

    // Pagination Logic
    int currentPage = 0;
    int totalResults = results.getSize();
    int totalPages = (totalResults + 29) / 30;  // Calculate how many pages there are

    while (true) {
        system("cls");
        cout << "\t\t\t\t\t\t\t\t\t\tSEARCH RESULT(S)\n";
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

        // Display the current page's results
        for (int i = currentPage * 30; i < (currentPage + 1) * 30 && i < totalResults; i++) {
            DoublyNode<Property>* resultNode = results.getNode(i)->data;
            DisplayProperty(resultNode->data);
        }

        // If this is the only page, break out of the loop
        if (totalPages <= 1) {
            cout << "\nPress any key and then Enter to continue...";
            char userInput;
            cin >> userInput;
            break;
        }

        cout << "\nPage " << (currentPage + 1) << " of " << totalPages << endl;
        cout << "Enter N for next, P for previous, Q to quit: ";
        char choice;
        cin >> choice;
        switch (toupper(choice)) {
            case 'N':
                if (currentPage < totalPages - 1) {
                    currentPage++;
                } else {
                    cout << "You're on the last page." << endl;
                }
                break;
            case 'P':
                if (currentPage > 0) {
                    currentPage--;
                } else {
                    cout << "You're on the first page." << endl;
                }
                break;
            case 'Q':
                return;
            default:
                cout << "Invalid choice. Please choose N, P, or Q." << endl;
                break;
        }
    }
    system("cls");
}

void LinearSearchTest(DoublyNode<Property> *low, string searchInput, SearchCriteria option) {
    DoublyLinkedList<DoublyNode<Property>*> results;  // Using DoublyLinkedList to store matching results

    for (DoublyNode<Property> *i = low; i != nullptr; i = i->next) {
        Property prop = i->data;
        bool match = false;
        
        switch (option) {
            case BY_YEAR:
                try {
                    int year = stoi(searchInput);
                    match = (year == prop.completion_year);
                } catch (exception&) {
                    cout << "Invalid year input. Please ensure it's a number." << endl;
                    return;
                }
                break;
            case BY_ID:
                try {
                    long id = stoul(searchInput);
                    match = (id == prop.ads_id);
                } catch (exception&) {
                    cout << "Invalid year input. Please ensure it's a number." << endl;
                    return;
                }
                break;
            default:
                cout << "Invalid search criteria." << endl;
                return;
        }

        if (match) {
            results.append(i);
        }
    }

    if (results.getSize() == 0) {
        cout << "Search term not found\n";
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        return;
    }

    cout << "\t\t\t\t\t\t\t\t\t\tSEARCH RESULT(S)\n";
    cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < results.getSize(); i++) {
        DoublyNode<Property>* resultNode = results.getNode(i)->data;
        DisplayProperty(resultNode->data);
    }
}

// BINARY SEARCH (SORTING IN ASCENDING ORDER)
DoublyNode<Property>* partitionForBinary(DoublyNode<Property> *low, DoublyNode<Property> *high, SearchCriteria option){
    int pivotValue;
    //cout << "Pivot value: " << pivotValue << endl;

    switch (option) {
        case BY_YEAR: pivotValue = high->data.completion_year; break;
        case BY_ID: pivotValue = high->data.ads_id;break;
        default: throw invalid_argument("Invalid option for partitioning.");
    }

    DoublyNode<Property> *i = low->prev;
    for(DoublyNode<Property> *j = low; j != high; j = j->next){
        int compareValue;
        //cout << "Midpoint value: " << compareValue << endl;

        switch (option) {
            case BY_YEAR: compareValue = j->data.completion_year; break;
            case BY_ID: compareValue = j->data.ads_id; break;
            default: throw invalid_argument("Invalid option for comparison.");
        }

        if(compareValue <= pivotValue){
            i = (i == nullptr) ? low : i->next;
            swap(i->data, j->data);
        }
    }

    i = (i == nullptr) ? low : i->next;
    swap(i->data, high->data);
    return i;
}

void quickSortForBinary(DoublyNode<Property> *low, DoublyNode<Property> *high, SearchCriteria option){
    if(high != nullptr && low != high && low != high->next){
        DoublyNode<Property> *p = partitionForBinary(low, high, option);
        quickSortForBinary(low, p->prev, option);
        quickSortForBinary(p->next, high, option);
    }
}

DoublyNode<Property>* middle(DoublyNode<Property>* start, DoublyNode<Property>* last)
{
    if (start == NULL)
        return NULL;

    DoublyNode<Property>* slow = start;
    DoublyNode<Property>* fast = start->next;

    while (fast != last)
    {
        fast = fast->next;
        if (fast != last)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    return slow;
}

DoublyNode<Property>* binarySearch(DoublyNode<Property> *head, int value, SearchCriteria option)
{
    DoublyNode<Property>* start = head;
    DoublyNode<Property>* last = nullptr;

    do
    {
        DoublyNode<Property>* mid = middle(start, last);
        if (mid == NULL)
            return NULL;

        int compareValue;

        switch (option) {
            case BY_YEAR: compareValue = mid->data.completion_year; break;
            case BY_ID: compareValue = mid->data.ads_id; break;
            default: throw std::invalid_argument("Invalid option for binary search.");
        }

        if (compareValue == value)
            return mid;
        else if (compareValue < value)
            start = mid->next;
        else
            last = mid;

    } while (last == NULL || last != start);

    return NULL;
}

void displayResults(DoublyNode<Property> *header, int value, SearchCriteria option) {
    DoublyNode<Property>* node = binarySearch(header, value, option);
    DoublyLinkedList<DoublyNode<Property>*> results;  // Using DoublyLinkedList

    if (node != nullptr) {
        results.append(node);
    } else {
        cout << "Search result with value " << value << " not found" << endl;
        return;
    }

    DoublyNode<Property>* currentNode = node->next;

    while (currentNode != nullptr) {
        switch (option) {
            case SearchCriteria::BY_YEAR:
                if (currentNode->data.completion_year == value) {
                    results.append(currentNode);
                }
                break;
            case SearchCriteria::BY_ID:
                if (currentNode->data.ads_id == value) {
                    results.append(currentNode);
                }
                break;
            default:
                break;
        }
        currentNode = currentNode->next;
    }

    // Pagination Logic
    int currentPage = 0;
    int totalResults = results.getSize();
    int totalPages = (totalResults + 29) / 30;  // Calculate how many pages there are

    while (true){
        for (int i = 0; i < results.getSize(); i++) {
            DoublyNode<Property>* resultNode = results.getNode(i)->data;
            const Property& prop = resultNode->data;
            DisplayProperty(prop);
        }

        // If this is the only page or no pages at all
        if (totalPages <= 1) {
            cout << "\nPress any key and then Enter to continue...";
            char userInput;
            cin >> userInput;
            break;
        }

        cout << "\nPage " << (currentPage + 1) << " of " << totalPages << endl;
        cout << "Enter N for next, P for previous, Q to quit: ";
        char choice;
        cin >> choice;
        switch (toupper(choice)) {
            case 'N':
                if (currentPage < totalPages - 1) {
                    currentPage++;
                } else {
                    cout << "You're on the last page." << endl;
                }
                break;
            case 'P':
                if (currentPage > 0) {
                    currentPage--;
                } else {
                    cout << "You're on the first page." << endl;
                }
                break;
            case 'Q':
                return;
            default:
                cout << "Invalid choice. Please choose N, P, or Q." << endl;
                break;
        }
    }
    system("cls");
    
}

void displayResults4Test(DoublyNode<Property> *header, int value, SearchCriteria option) {
    DoublyNode<Property>* node = binarySearch(header, value, option);
    DoublyLinkedList<DoublyNode<Property>*> results;  // Using DoublyLinkedList

    if (node != nullptr) {
        results.append(node);
    } else {
        cout << "Search result with value " << value << " not found" << endl;
        return;
    }

    DoublyNode<Property>* currentNode = node->next;

    while (currentNode != nullptr) {
        switch (option) {
            case SearchCriteria::BY_YEAR:
                if (currentNode->data.completion_year == value) {
                    results.append(currentNode);
                }
                break;
            case SearchCriteria::BY_ID:
                if (currentNode->data.ads_id == value) {
                    results.append(currentNode);
                }
                break;
            default:
                break;
        }
        currentNode = currentNode->next;
    }

    for (int i = 0; i < results.getSize(); i++) {
        DoublyNode<Property>* resultNode = results.getNode(i)->data;
        const Property& prop = resultNode->data;
        DisplayProperty(prop);
    }
}

// LINEAR SEARCH
bool SpecificSearch(DoublyNode<Property> *low, string searchInput) {
    bool Fmatch = false;
    cout << "\nSearching for the property ... \n";
    cout << "\n\t\t\t\t\t\t\t\t\t\tProperty Details";
    cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"; 

    for (DoublyNode<Property> *i = low; i != nullptr; i = i->next) {
        Property prop = i->data;
        bool match = false;
        
        try {
            long id = stol(searchInput);
            match = (id == prop.ads_id);
        } catch (exception&) {
            cout << "Invalid ID input. Please ensure it's a number." << endl;
            return Fmatch;
        }

        if (match) {;
            DisplayProperty(prop);
            Fmatch = true;
            return Fmatch;
        } else {
        }
    }

    if (!Fmatch) {
        cout << "Search term not found\n";
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        return Fmatch;
    }
}

DoublyNode<Property>* SearchForNode(DoublyNode<Property> *low, string searchInput){
    // cout << "Searching for property ID: " << searchInput << endl;
    // cout << "Starting traversal" << endl;
    for (DoublyNode<Property> *i = low; i != nullptr; i = i->next) {
        Property prop = i->data;
        // cout << "Checking property with ID: " << prop.ads_id << endl; // Debugging statement
        bool match = false;
        // cout << "Comparing " << prop.ads_id << " with " << searchInput << endl;
        try {
            long id = stol(searchInput);
            cout << "Converted ID: " << id << endl;
            match = (id == prop.ads_id);
        } catch (exception&) {
            cout << "Invalid ID input. Please ensure it's a number." << endl;
            return nullptr;
        }

        // if (prop.ads_id == 100323185) {
        //     cout << "Found the target property with ID: " << prop.ads_id << endl;
        // }

        if (match) {
            // cout << "Found property with ID: " << prop.ads_id << endl;
            return i;
        } else {
            cout << "Property not found in this iteration." << endl;
        }
    }
    // cout << "Finished traversal" << endl;
    return nullptr;
}

DoublyLinkedList<Property>* getPropWReq(DoublyNode<Property> *low){
    //cout << "Getting list of dp";
    DoublyLinkedList<Property>* results = new DoublyLinkedList<Property>();
    DoublyNode<Property>* current;

    for (DoublyNode<Property> *i = low; i != nullptr; i = i->next){
        Property* propPtr = &(i->data);
        //cout << "prop check\n";

        if(propPtr->reqCount != 0){
            //cout << "appending\n";
            results->append(i->data);
            //cout << "OK\n";
        }
    }

    return results;
}

DoublyLinkedList<Property> filterByPropertyType(DoublyNode<Property> *low, const string& type){
    DoublyLinkedList<Property> result;;
    for(DoublyNode<Property>* node = low; node != nullptr; node = node->next) {
        if (node->data.property_type == type) {
            result.append(node->data);
        }
    }
    return result;

}

DoublyLinkedList<Property> filterByMonthlyRent(DoublyNode<Property> *low, int minRent, int maxRent) {
    DoublyLinkedList<Property> result;
    for (DoublyNode<Property>* node = low; node != nullptr; node = node->next) {
        int rent = stoi(node->data.monthly_rent);
        if (rent >= minRent && rent <= maxRent) {
            result.append(node->data);
        }
    }
    return result;
}

DoublyLinkedList<Property> filterBySize(DoublyNode<Property> *low, int minSize, int maxSize) {
    DoublyLinkedList<Property> result;
    for (DoublyNode<Property>* node = low; node != nullptr; node = node->next) {
        int size = stoi(node->data.size);
        if (size >= minSize && size <= maxSize) {
            result.append(node->data);
        }
    }
    return result;
}


#endif