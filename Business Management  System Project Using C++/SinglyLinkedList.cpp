// Created by Zafar Ali on 23/11/2021
#include "SinglyLinkedList.h"
#include <iostream>
using namespace std;
template<typename T>

SinglyLinkedList<T>::SinglyLinkedList()//default constructor
{   
    head= nullptr;
    tail= nullptr;
    count=0;
    item_serial=1;
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T> &obj)//This finction deep copies the pointers after traseversal
//It goes to each node and copies its value this node
{
    head= nullptr;
    tail= nullptr;
        Node<T> *temp = obj.head;
        while (temp != nullptr)
        {
            Node<T> *newCopy = new Node<T>(temp->getNodeValue());
            newCopy->setNextNode(nullptr);
            if (head == nullptr) 
            {
                head = newCopy;
                tail = newCopy;
            } 
            else
            {
                tail->setNextNode(newCopy);
                tail = newCopy;
            }
            temp = temp->getNextNode();
        }
        count=obj.getCount();
        item_serial=obj.getItemSerial();
}


template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList(){   //destructor
//It goes node by node and deletes each node
    while (head != nullptr) {
        Node<T> *temp;
        temp = head->getNextNode();
        delete head;
        head = temp;
    }


}

template<typename T>
Node<T>*SinglyLinkedList<T>::getHead()const
{
    return head;
}

template <typename T>
Node<T> * SinglyLinkedList<T>::getTail()
{
    return tail;
}

template<typename T>
int SinglyLinkedList<T>::getCount()const
{
    return count;
}

template<typename T>
int SinglyLinkedList<T>::getItemSerial()const
{
    return item_serial;
}

template<typename T>
void SinglyLinkedList<T>::appendNode(T val)//Insert a new Node at End of List
{   
    Node<T>*temp=new Node<T>(val);
    temp->setNextNode(nullptr);
    if(head== nullptr)
    {
        head=temp;
        tail=temp;
    }
    else
    {
        tail->setNextNode(temp);
        tail=temp;
    }
    count++;
    item_serial++;
}

template<typename T>
void SinglyLinkedList<T>::deleteAtEnd() //This Function delete element at end if list contains elements
{
    Node<T> *temp = head;
    if (isListEmpty())
    {
        cout << endl << "List iS empty" << endl;

    } 
    else if (count == 2) 
    {
        temp = head->getNextNode();
        delete head;
        head = temp;
        count--;
    } 
    else if (count > 2)
    {
        Node<T> *temp = head;
        for (int i = 0; i < count - 2; ++i) 
        {
            temp = temp->getNextNode();
        }
        delete tail;
        tail = temp;
        tail->setNextNode(nullptr);
        count--;
    } 
    else 
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        count--;
    }
}

template<typename T>
void SinglyLinkedList<T>::deleteAtBeginning()//This function deletes Node from beginning
{
    Node<T> *temp = head;
    if (isListEmpty())
    {
        cout << endl << "List iS empty" << endl;
    } 
    else if (count > 1) 
    {
        temp = head->getNextNode();
        delete head;
        head = temp;
        count--;
    } 
    else
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        count--;
    }
}

template<typename T>
void SinglyLinkedList<T>::deleteAtIndex(int index)
//This Function calls delete at end if index value is equal to count and calls delele at begining if there is
//one node in list between those indexes it makes two temporaries one is previous of index Node and second is node
//itself then is sets the next of previous to get next of second temporay node and then it deletes the second temp node
{
    Node<T>* temp = head;
    Node<T>* temp2;
    if (count == 0)
    {
        cout << "Link list is already empty." << endl;
        return;
    }
    if (index > count)
    {
        cout << "Error! Out of range." << endl;
        return;
    }
    else if (count == 1)
    {
        if (index == 1)
        {
            deleteAtEnd();
            cout << "Data deleted from the Linked List." << endl;
            return;
        }
        else
        {
            cout << "Error! Out of range." << endl;
            return;
        }
    }
    if (index == 1)
    {
        deleteAtBeginning();
        cout << "Data deleted from the Linked List." << endl;
        return;
    }
    else
    {
        for (int i = 1; i < count; i++)
        {

            if (index - i == 1)
            {
                temp2 = temp->getNextNode();
                temp->setNextNode(temp->getNextNode()->getNextNode());
                delete temp2;
                cout << "Data deleted from the Linked List." << endl;
                count--;
                break;
            }
            temp = temp->getNextNode();
        }
    }
}

template<typename T>
void SinglyLinkedList<T>::set_head(Node<T>* head) 
{
    this->head = head;
}

template<typename T>
void SinglyLinkedList<T>::set_tail(Node<T>* tail)
{
    this->tail = tail;
}

template<typename T>
void SinglyLinkedList<T>::display()
//This function starts from beginning of list if list is not empty and couts each node value the ofstream operator overloading
//is also used the cout objects
{
    if (isListEmpty()) 
    {
        cout << endl << "List is Empty!!!!!!!!!!!!!" << endl;
    } 
    else 
    {
        Node<T> *temp = head;
        cout << endl << "Linked List: ";
        while (temp != NULL) 
        {
            cout << temp->getNodeValue() << "->";
            temp = temp->getNextNode();
        }
        cout << "NULL" << endl;
    }
}

template<typename T>
Node<T>*& SinglyLinkedList<T>::getHeadByReference()
{
    return head;
}

template<typename T>
Node<T>*& SinglyLinkedList<T>::getTailByReference()
{
    return tail;
}

template<typename T>
bool SinglyLinkedList<T>::isListEmpty()const
{
    return (count==0);
}

template<typename T>
void SinglyLinkedList<T>::setSerialNum(int sr)
{
    item_serial=sr;
}