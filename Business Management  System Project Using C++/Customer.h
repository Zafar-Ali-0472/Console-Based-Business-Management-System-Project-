/// Created by Zafar Ali on 23/11/2021

#ifndef ARRAYLIST_H_CUSTOMER_H
#define ARRAYLIST_H_CUSTOMER_H
#include <iostream>
#include <cstring>
using namespace std;
//All functionalities Done by Zafar Ali

class Customer
{
   string customer_name;
   long phone_number;
   int customer_id;
  public: 
    Customer();//Default Constructor
   ~Customer();//The Destructor
    void setCustomerName(string name);
    string getCustomerName()const;
    void setPhoneNumber(long num);
    long getPhoneNumber()const;
    void setCustomerID(int id);
    int getCustomerID()const;
    friend ostream& operator <<(ostream& out, const Customer& temp);
    //check all the functionalities by making an helping display function whether they are working or Not
};
#endif //ARRAYLIST_H_CUSTOMERNODE_H
