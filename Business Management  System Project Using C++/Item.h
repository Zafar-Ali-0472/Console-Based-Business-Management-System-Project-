// Created by Zafar Ali on 23/11/2021

#ifndef ARRAYLIST_H_ITEM_H
#define ARRAYLIST_H_ITEM_H
#include <iostream>
#include <cstring>
using namespace std;
//All functionalities done by zafar Ali

class Item 
{
    string item_name;
    int item_SR_number;
    float pur_price;
    float sell_price;
    int quantity;
  public:
    Item();
    ~Item();
    void setItemName(string name);
    void setItemSRNumber(int srnum);
    void setPurchasePrice(float purprice);
    void setSellPrice(float sellprice);
    void setQuantity(int qty);
    string getItemName()const;
    int getItemSRNumber()const;
    float getItemPurPrice()const;
    float getItemSellPrice()const;
    int getItemQuantity()const;
    friend ostream& operator<<(ostream& out, const Item& temp);
};

#endif //ARRAYLIST_H_ITEMNODE_H
