// Created by Zafar Ali on 26/11/2021.

#include "Vendor.h"
#include <iostream>

Vendor::Vendor()
{
    vendor_id=0;
    ven_phone_number=0;
}

Vendor::~Vendor()
{

}
void Vendor::setVendorName(string name)
{
    vendor_name=name;
}

string Vendor::getVendorName()const
{
    return vendor_name;
}

void Vendor::setVenPhoneNumber(long num)
{
    ven_phone_number=num;
}

long Vendor::getVenPhoneNumber()const
{
    return ven_phone_number;
}

void Vendor::setVendorID(int id)
{
    vendor_id=id;
}

int Vendor::getVendorID()const
{
    return vendor_id;
}

ostream&operator<<(ostream & out, const Vendor&temp)
{
    out << endl << "Vendor ID: " << temp.getVendorID() << endl << "Vendor Name: " << temp.getVendorName() << endl << "Vendor ID: " << temp.getVenPhoneNumber() << endl;
    return out;
}