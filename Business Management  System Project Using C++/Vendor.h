// Created by Zafar Ali on 26/11/2021.

#ifndef ARRAYLIST_H_VENDOR_H
#define ARRAYLIST_H_VENDOR_H
#include <iostream>
#include <cstring>
using namespace std;

class Vendor
{
   string vendor_name;
   long ven_phone_number;
   int vendor_id;
  public:
    Vendor(); //Default Constructor
    ~Vendor(); //The Destructor
    void setVendorName(string name); 
    string getVendorName()const; 
    void setVenPhoneNumber(long num); 
    long getVenPhoneNumber()const; 
    void setVendorID(int id); 
    int getVendorID()const;  
    friend ostream& operator<<(ostream & out, const Vendor & temp);
};
#endif //ARRAYLIST_H_VENDORNODE_H