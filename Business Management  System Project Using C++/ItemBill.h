// Created by Zafar Ali on 22/11/2021
#ifndef ARRAYLIST_H_ITEMBILL_H
#define ARRAYLIST_H_ITEMBILL_H

#include <iostream>
#include <cstring>
using namespace std;

class ItemBill
{
    string it_name;
    int item_serial;
    int quantity;
    float price;
  public:
    ItemBill();
    ~ItemBill();
    void setItemName(string name);
    void setItemSerial(int srno_);
    void setPrice(float pr);
    void setQuantity(int qty);
    string getName()const;
    int getSerial()const;
    float getPrice()const;
    int getQuantity()const;
    friend ostream& operator<<(ostream& out, const ItemBill& temp);
};
#endif //ARRAYLIST_H_ITEMBILL_H