// Created by Zafar Ali on 23/11/2021
#include "Node.h"

template<typename T>
Node<T>::Node(T val)
{
    node_value=val;
    next_node= nullptr;
}

template<typename T>
Node<T>::~Node()
{

}

template<typename T>
void Node<T>::setNodeValue(T val)
{
    node_value=val;
}

template<typename T>
T Node<T>::getNodeValue()const
{
    return node_value;
}

template<typename T>
Node<T> *Node<T>::getNextNode()const
{
    return next_node;
}

template<typename T>
void Node<T>::setNextNode(Node<T>*next)
{
    next_node=next;
}

template<typename T>
T & Node<T>::getValueByReference()
{
    return node_value;
}
