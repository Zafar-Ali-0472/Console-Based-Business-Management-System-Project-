// Created by Zafar Ali on 22/11/2021

#include "ItemBill.h"
#include <cstring>

ItemBill::ItemBill()
{

}

ItemBill::~ItemBill()
{

}

void ItemBill::setItemName(string name)
{
    it_name = name;
}

void ItemBill::setItemSerial(int srno_)
{
    item_serial = srno_;
}

void ItemBill::setPrice(float pr)
{
    price=pr;
}

void ItemBill::setQuantity(int qty)
{
    quantity=qty;
}

string ItemBill::getName()const
{
    return it_name;
}

int ItemBill::getSerial()const
{
    return item_serial;
}

float ItemBill::getPrice()const
{
    return price;
}

int ItemBill::getQuantity()const
{
    return quantity;
}

ostream&operator<<(ostream & out, const ItemBill & temp)
{
    out << endl << "Item Serial: " << temp.getSerial() << endl << "Qunatity: " <<
        temp.getQuantity() << endl << "Price: " << temp.getPrice() << endl << endl;
    return out;
}