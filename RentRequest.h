#ifndef RENTREQUEST_H
#define RENTREQUEST_H

#include <string>
#include <chrono>
#include <ctime>

using namespace std;

class RentRequest
{
public:
    string id;
    string pID;
    string tID;
    string timeStamp;
    string status;

    // Default Constructor
    RentRequest() : id(""), tID(""), pID(""), status(""), timeStamp("") {}
    
    RentRequest(string id, string tID, string pID) : id(id), tID(tID), pID(pID), status("Pending") {
        // Set timeStamp to the current time
        auto now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);
        timeStamp = ctime(&currentTime); // Convert time_t to string
        timeStamp.pop_back(); // Remove newline character added by ctime
    }

    ~RentRequest() {}

    bool operator==(const RentRequest& other) const {
      return this->id == other.id;
    }
    
    bool operator!=(const RentRequest& other) const {
      return !(*this == other);
    }

    void updateTimestamp() {
      auto now = std::chrono::system_clock::now();
      std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
      this->timeStamp = std::ctime(&currentTime);
      this->timeStamp.pop_back();  // To remove the newline added by ctime
    }

    void setApproved(){
      status = "Approved, Pending for Payment";
    }

    void setPaid(){
      status = "Paid, Property Rented";
    }

};

#endif