#ifndef IMPORTMETHOD_H
#define IMPORTMETHOD_H

#include "DoublyLinkedList.h"
#include "Property.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

bool importFromCsv(const string &filename, DoublyLinkedList<Property>& propertyList){
    ifstream file(filename);

    if(!file.is_open()){
        return false;
    }

    string line;
    getline(file, line);  // skip the header line

    // Utility functions to clean rent and size data
    auto cleanRentData = [](const string& rent) -> int {
        string cleanedRent = rent;

        cleanedRent.erase(remove_if(cleanedRent.begin(), cleanedRent.end(), [](char c) {
            return !isdigit(c);
        }), cleanedRent.end());

        return cleanedRent.empty() ? -1 : stoi(cleanedRent);
    };

    auto cleanSizeData = [](const string& size) -> int {
        string cleanedSize = size;

        cleanedSize.erase(remove_if(cleanedSize.begin(), cleanedSize.end(), [](char c) {
            return !isdigit(c);
        }), cleanedSize.end());

        return cleanedSize.empty() ? -1 : stoi(cleanedSize);
    };

    while (getline(file, line)) {
        istringstream ss(line);
        string data[14];
        int dataIndex = 0;
        bool insideQuotes = false;
        string currentValue = "";
        for (char c : line) {
            if (c == '"') {
                insideQuotes = !insideQuotes;
            } else if (c == ',' && !insideQuotes) {
                data[dataIndex++] = currentValue;
                currentValue = "";
            } else {
                currentValue += c;
            }
        }
        data[dataIndex] = currentValue;  // last field

        // Provide default values for missing data
        if (data[1] == "") data[1] = "None"; // Property Type
        if (data[7] == "") data[7] = "0"; // parking
        if (data[12] == "") data[12] = "None"; // additional_facilities

        // Clean and handle rent and size data
        int rentValue = cleanRentData(data[3]);
        int sizeValue = cleanSizeData(data[9]);

        // Provide unique value for inconsistent data
        int year = 0;
        try{
            year = stoi(data[2]);
        }catch(const invalid_argument& ia){
            year = -1;
        }

        int rooms = 0;
        if(data[6] == "More than 10"){
            rooms = 99; // rooms
        }else{
            try{
                rooms = stoi(data[6]);
            }catch(const invalid_argument& ia){
                rooms = 88;
            }
        }

        int parking = 0;
        try{
            parking = stoi(data[7]);
        }catch(const invalid_argument& ia){
            parking = 99;
        }

        int bathroom = 0;
        try{
            bathroom = stoi(data[8]);
        }catch(const invalid_argument& ia){
            bathroom = 99;
        }

        Property *prop = new Property(stoul(data[0]), data[1], year, to_string(rentValue), data[4], data[5], 
        rooms, parking, bathroom, to_string(sizeValue), data[10], data[11], data[12], data[13]);

        DoublyNode<Property> *newNode = new DoublyNode<Property>(*prop);

        propertyList.append(*prop);
    }

    file.close();
    return true;
};

#endif