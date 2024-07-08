// Created by Zafar Ali on 23/11/2021

#include "Customer.h"
#include <cstring>

Customer::Customer()
{
    phone_number=0;
    customer_id=0;
}

Customer::~Customer()
{

}

void Customer::setCustomerName(string name)
{
    customer_name=name;
}

string Customer::getCustomerName()const
{
   return customer_name;
}

void Customer::setPhoneNumber(long num)
{
    phone_number=num;
}

long Customer::getPhoneNumber()const
{
    return phone_number;
}

void Customer::setCustomerID(int id)
{
    customer_id=id;
}

int Customer::getCustomerID()const
{
    return customer_id;
}

ostream& operator <<(ostream& out, const Customer& temp)
{
    out << endl << "Customer ID: " << temp.customer_id << endl << "Customer Name: " << temp.customer_name << endl
        << "Customer Phone: " << temp.phone_number << endl;
    return out;
}