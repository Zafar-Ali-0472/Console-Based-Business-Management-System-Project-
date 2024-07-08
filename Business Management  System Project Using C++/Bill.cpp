//Created by Zafar on 20/11/2021
#include <iostream>
#include "Bill.h"
#include <cstring>

Bill::Bill()
{
}

Bill::Bill(const Bill &obj) 
{
   name =obj.name;
   bill_num=obj.bill_num;
   total=obj.total;
   discount=obj.discount;
   balance=obj.balance;
   customer_id=obj.customer_id;
   Node<ItemBill> *temp = obj.billitems.getHead();
   while (temp != nullptr)
   {
       billitems.appendNode(temp->getNodeValue());
       temp = temp->getNextNode();
   }
   billitems.setSerialNum(obj.billitems.getItemSerial());
}

Bill::~Bill()
{

}

void Bill::setName(string nam)
{
    name=nam;
}

void Bill::setBillNo(int billno)
{
    bill_num=billno;
}

void Bill::setTotal(float val)
{
    total=val;
}

void Bill::setDiscount(float val){
    discount=val;
}

void Bill::setItems(ItemBill temp)
{
    billitems.appendNode(temp);
    cout<<"Billed Items Are"<<endl;
    billitems.display();
}

string Bill::getName()const
{
    return name;
}

int Bill::getBillNum()const
{
    return bill_num;
}

float Bill::getTotal()const
{
    return total;
}

float Bill::getDiscount()const
{
    return discount;
}

void Bill::setBalance(float val) 
{
    balance=val;
}

float Bill::getBalance() const 
{
    return balance;
}

void Bill::setCustomerIDBill(int val) 
{
    customer_id=val;
}

int Bill::getCustomerIDBill() const 
{
    return customer_id;
}

Node<ItemBill> *& Bill::getBillItemsHead()
{
    return billitems.getHeadByReference();
}

void Bill::displayBillItems()
{
    billitems.display();
}

 ostream&operator<<(ostream& out, const Bill & temp)
 {
    out<<"Bill No: "<<temp.getBillNum()<<endl<<"Bill To: "<<temp.getName()<<"********************************ID customer/Vendor: "
    <<temp.getCustomerIDBill()<<endl<<
    "Total: "<<temp.getTotal()<<"**********************************Discount :"<<temp.getDiscount()<<endl<<
    "Balance Amount: "<<temp.getBalance()<<endl;
     return out;
}