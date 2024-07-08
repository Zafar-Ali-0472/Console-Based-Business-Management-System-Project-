// Created by Zafar on 20/11/2021
#ifndef ARRAYLIST_H_BILL_H
#define ARRAYLIST_H_BILL_H
#include "SinglyLinkedList.h"
#include "ItemBill.h"
#include <cstring>
using namespace std;

class Bill 
{
    string name;
    int bill_num;
    float total;
    float discount;
    float balance;
    SinglyLinkedList <ItemBill> billitems;
    int customer_id;
  public:
    Bill();//Default Constructor 
    Bill(const Bill &obj);//Pparametrized Constructor 
    ~Bill();//The Destructor
    void setCustomerIDBill(int val);
    int getCustomerIDBill()const;
    void setName(string nam);
    void setBillNo(int billno);
    void setTotal(float val);
    void setDiscount(float val);
    void setItems(ItemBill temp);
    void setBalance(float val);
    float getBalance()const;
    string getName()const;
    int getBillNum()const;
    float getTotal()const;
    float getDiscount()const;
    Node<ItemBill>*&getBillItemsHead();
    void displayBillItems();
    friend ostream& operator<<(ostream& out, const Bill& temp);
};

#endif //ARRAYLIST_H_BILL_H