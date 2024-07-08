// Created by Zafar Ali on 23/11/2021
#ifndef ARRAYLIST_H_NODE_H
#define ARRAYLIST_H_NODE_H
#include <iostream>
#include"Customer.h"

template<typename T>
class Node 
{
    T node_value;
    Node<T>*next_node;
  public:
    Node(T val); //Default Constructor
    ~Node(); //The Destructor
    void setNodeValue(T val); //Setter Function to set the value of the Node
    T getNodeValue()const; //Getter Function to get the value of the Node
    T& getValueByReference(); //Getter Function to get the value of the Node by reference
    void setNextNode(Node<T>*next); //Setter Function to set the next value of the Node
    Node<T>*getNextNode()const; //Getter Function to get the next value of the Node
};
#include "Node.cpp"
#endif //ARRAYLIST_H_NODE_H