// Created by Zafar Ali on 24/11/2021

#ifndef ARRAYLIST_H_COMPANY_H
#define ARRAYLIST_H_COMPANY_H
#include <iostream>
#include "SinglyLinkedList.h"
#include "Customer.h"
#include "Vendor.h"
#include "Item.h"
#include "Bill.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

class Company
{
    SinglyLinkedList <Customer> customer;
    SinglyLinkedList<Vendor> vendors;
    SinglyLinkedList<Item> items;
    SinglyLinkedList<Bill> bills;
  public:
    Company();//Default Contructor 
    ~Company();//The Destructor
    // Customer Functionalities
    void addCustomer(); 
    void displayCustomerList(); 
    void searchCustomer(int id);
    Customer getCustomer(int id); 
    void searchCustomer(string name);
    void deleteCustomer(int id);
    void deleteCustomer (string name);
    void createCustomerBill(Customer temp);
    void mergeSort(Node<Customer> * & head, Node<Customer> *& tail, int cnt);
    void merge(Node<Customer> * partA, Node<Customer> *partB, Node <Customer> * & mergedHead , Node <Customer> * & mergedTail);
    void writeCustomersToFile();
    void readCustomersFromFile();
    void mergeSortCustomer(Node<Customer> * & head, Node<Customer> *& tail, int cnt);
    void mergeCustomer(Node<Customer> * partA, Node<Customer> *partB, Node <Customer> * & mergedHead , Node <Customer> * & mergedTail);
    int find_max_Customer();
    void count_sort_customer(Node<Customer>**& count_array, int exp, int length);
    void radix_sort_customer();

    //Vendor Functionalities
    void addVendor();
    void displayVendorList();
    void deleteVendor(int id);
    void deleteVendor(string name);
    void searchVendor(int id);
    void searchVendor(string name);
    Vendor getVendor(int id);
    void readVendors();
    void writeVendors();
    void createVendorBill();

    //Item Functionalities
    void addItem();
    void deleteItem(int srno);
    void deleteItem(string name);
    void searchItem(int srno);
    Item searchItemByRef(int srno);
    void decreaseItemQuantity(int srno, int qty); 
    void increaseItemQuantity(int srno, int qty);
    void setItemSellPrice(int srno, float sel_price);
    void setItemPurPrice(int srno, float pur_price);
    void searchItem(string name);
    void displayItemList();
    void writeItemsToFile();
    void readItemsFromFile();
    void mergeSortItems(Node<Item> * & head, Node<Item> *& tail, int cnt);
    void mergeItems(Node<Item> * partA, Node<Item> *partB, Node <Item> * & mergedHead , Node <Item> * & mergedTail);
    int find_max_Item();
    void count_sort_items(Node<Item>**& count_array, int exp, int length);
    void radix_sort_items();
    void menu();
    void customerMenu();
    void itemsMenu();
    void vendorsMenu();
    //Bill functionalities
    void displayBill();
    void writeBillsToFile();
    void readBillsFromFile();
    void writeBilledItemsToFile(Node<Bill>*temp);
    void displayBillsFunction();
};
#endif //ARRAYLIST_H_COMPANY_H
