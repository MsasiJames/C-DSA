#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include "Queue.h"
#include "RentRequest.h"

using namespace std;

class Property {
public:
    long ads_id;
    string prop_name;
    int completion_year;
    string monthly_rent;
    string location;
    string property_type;
    int rooms;
    int parking;
    int bathroom;
    string size;
    string furnished;
    string facilities;
    string additional_facilities;
    string region;
    int favCount;
    int reqCount;
    Queue<RentRequest>* requestQ;

    // Constructor
    Property(long ads_id = 0, string prop_name = "", int completion_year = 0, string monthly_rent = "",
             string location = "", string property_type = "", int rooms = 0, int parking = 0,
             int bathroom = 0, string size = "", string furnished = "", string facilities = "",
             string additional_facilities = "", string region = "")
        : ads_id(move(ads_id)), prop_name(move(prop_name)), completion_year(move(completion_year)),
          monthly_rent(move(monthly_rent)), location(move(location)), property_type(move(property_type)),
          rooms(move(rooms)), parking(move(parking)), bathroom(move(bathroom)), size(move(size)),
          furnished(move(furnished)), facilities(move(facilities)), additional_facilities(move(additional_facilities)),
          region(move(region)) {
            requestQ = new Queue<RentRequest>();
            favCount = 0;
            reqCount = 0;
          }

    ~Property() {}

    bool operator==(const Property& other) const {
      return this->ads_id == other.ads_id;
    }
    
    bool operator!=(const Property& other) const {
      return !(*this == other);
    }
    
    void incrementFavCount(){
      favCount++;
    }

    void decrementFavCount(){
      favCount--;
    }

    void incrementReqCount(){
      reqCount++;
    }

    void decrementReqCount(){
      reqCount--;
    }

    string generateNewReqID(){
      string id = "REQ" + to_string(reqCount+1);
      return id;
    }

};

#endif