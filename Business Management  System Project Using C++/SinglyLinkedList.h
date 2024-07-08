// Created by Zafar Ali on 26/11/2021.

#ifndef ARRAYLIST_H_SINGLYLINKEDLIST_H
#define ARRAYLIST_H_SINGLYLINKEDLIST_H
#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;
template<typename T>

class SinglyLinkedList 
{
    Node<T>*head;
    Node<T>*tail;
    int count;
    int item_serial;
  public:
    SinglyLinkedList();//Default Constructor
    SinglyLinkedList(const SinglyLinkedList&obj);//Parametrized Constructor
    ~SinglyLinkedList();//The Destructor
    Node<T>*& getHeadByReference();
    Node<T>*& getTailByReference();
    Node<T>*getHead()const;
    Node<T>*getTail();
    int getCount()const;
    int getItemSerial()const;
    void appendNode(T val);
    void display();
    bool isListEmpty()const;
    void deleteAtIndex(int index);
    void setSerialNum(int sr);
    void deleteAtBeginning();
    void deleteAtEnd();
    void set_head(Node<T>* head);
    void set_tail(Node<T>* tail);
};
#include "SinglyLinkedList.cpp"
#endif //ARRAYLIST_H_SINGLYLINKEDLIST_H
