// Created by Zafar Ali on 23/11/2021
#include <string>
#include "Item.h"

Item::Item() //Default Constructor
{  
    item_SR_number=0;
    pur_price=0;
    sell_price=0;
    quantity=0;
}

Item::~Item()//The Destructor
{

}

void Item::setItemName(string name)
{  
    item_name=name;
}

void Item::setItemSRNumber(int srnum)
{  
    item_SR_number=srnum;
}

void Item::setPurchasePrice(float purprice)
{ 
    pur_price=purprice;
}

void Item::setSellPrice(float sellprice)
{  
    sell_price=sellprice;
}
void Item::setQuantity(int qty)
{  
    quantity=qty;
}

string Item::getItemName()const
{  
    return item_name;
}

int Item::getItemSRNumber()const
{  
    return item_SR_number;
}

float Item::getItemPurPrice()const
{  
    return pur_price;
}

float Item::getItemSellPrice()const
{  
    return sell_price;
}

int Item::getItemQuantity()const
{
    return quantity;
}

ostream & operator<<(ostream& out, const Item& temp)
{
    out<<endl<<"Item Serial: "<<temp.getItemSRNumber()<<endl<<
    "Item Name: "<<temp.getItemName()<<endl<<
    "Item Purchase Price: "<<temp.getItemPurPrice()<<endl<<
    "Item Selling Price: "<<temp.getItemSellPrice()<<endl<<
    "Item Quantity Available: "<<temp.getItemQuantity()<<endl;
    return out;
}