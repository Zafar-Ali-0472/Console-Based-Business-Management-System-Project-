// Created by Zafar on 20/11/2021
#include <iostream>
#include "Company.h"
#include <cstring>
using namespace std;

Company::~Company()
{
    writeCustomersToFile();
    writeItemsToFile();
    writeBillsToFile();
    writeVendors();
}

Company::Company() 
{
    readCustomersFromFile();
    readItemsFromFile();
    readVendors();
    readBillsFromFile();
}

void Company::addCustomer()//This functions add new customer to end after taking input from user and calls append funation for linked list
{  
    int cus_id;
    cus_id=customer.getItemSerial();
    long num;
    string name;
    cout << endl << "Please enter Customer Name: ";
    cin>>name;
    cout << endl << "Please enter Customer Phone Number: ";
    cin>>num;
    Customer temp;
    temp.setCustomerID(cus_id);
    temp.setPhoneNumber(num);
    temp.setCustomerName(name);
    customer.appendNode(temp);
}

void Company::displayCustomerList()
{
    customer.display();
}

void Company::searchCustomer(int id)
//this function traverses from each customer linked list and displays the customer if found with given id
{
    Node<Customer>* temp = customer.getHead();
    int check = 0;
    while (temp != NULL)
    {
        if ((temp->getNodeValue()).getCustomerID() == id)
        {
            cout << temp->getNodeValue() << endl;
            check++;
            break;
        }
        temp = temp->getNextNode();
    }
    if (check==0)
    {
        cout << endl << "Customer of id: '" << id << "' doesn't found." << endl;
    }
}
void Company::searchCustomer(string name)
{
    //this function traverses from each customer linked list and displays the customer if found with given name
    Node<Customer>* temp = customer.getHead();
    int check = 0;
    while (temp != NULL)
    {
        if ((temp->getNodeValue()).getCustomerName() == name) 
        {
            cout << temp->getNodeValue() << endl;
            check++;
            break;
        }
        temp = temp->getNextNode();
    }
    if (check == 0)
    {
        cout << endl << "Customer of name: '" << name << "' doesn't found." << endl;
    }
}
Customer Company::getCustomer(int id)
{
//this function traverses from the linked list of customer and returns the customer object if finds with specific ID
    Node<Customer>* temp = customer.getHead();
    while (temp != NULL) 
    {
        if ((temp->getNodeValue()).getCustomerID() == id)
        {
            return temp->getNodeValue();
        }
        temp = temp->getNextNode();
    }
}
void Company::deleteCustomer(int id)
//This function takes ID as input and traverses the linked list of customers and maintains a count as index
//if finds the customer with ID then call the Delete at index function whose Index is Count
{
    Node<Customer>* temp = customer.getHead();
    int count = 1;
    int check = 0;
    while (temp != NULL) 
    {
        if (temp->getNodeValue().getCustomerID()==id)
        {
            customer.deleteAtIndex(count);
            cout << "Customer of " << id << " deleted" << endl;
            check++;
            break;
        }
        count++;
        temp = temp->getNextNode();
    }
    if (check==0) 
    {
        cout << "Customer of " << id << " couldn't be found." << endl;
    }
}
void Company::deleteCustomer(string name) 
{
    //This function takes Name as input and traverses the linked list of customers and maintains a count as index
    //if finds the customer with Name then call the Delete at index function whose Index is Count
    Node<Customer>* temp = customer.getHead();
    int count = 1;
    int check = 0;
    while (temp != NULL)
    {
        if (temp->getNodeValue().getCustomerName() == name)
        {
            customer.deleteAtIndex(count);
            check++;
            cout << "Customer of " << name << " deleted" << endl;
            break;
        }
        count++;
        temp = temp->getNextNode();
    }
    if (check == 0)
    {
        cout << "Customer of " << name << " couldn't be found." << endl;
    }
}

void Company::createCustomerBill(Customer temp) 
//This function creates an Customer Bill it gets the customer from linked list of customers
//and uses the Items from items linked list It makes a bill object inserts the values in it This Bill also stores the ID of Customer
//which makes it easier to get the bills for a specific Customer
//The bill obeject Conatains Billled Item Linked List Bill Number Customer Name And Id total And Balance Amount
{
    int billno ,item_sr,qty;
    float disc=0;
    float total=0,balance,amount;
    Bill temp_bill;
    billno=bills.getItemSerial();
    temp_bill.setBillNo(billno);
    temp_bill.setName(temp.getCustomerName());
    temp_bill.setCustomerIDBill(temp.getCustomerID());
    while (true)
    {
        Item item_temp;
        ItemBill bill_item_temp;
        int opt;
        cout <<"~:((===============================================================)):~" << endl;
        cout << endl << "Enter 1 to Add Items to Bill" << endl <<
            "Enter 2 to Enter Discount Percentage" << endl <<
            "Enter 0 to Finalize and Confirm Bill" << endl;
        cout <<"~:((===============================================================)):~" << endl;
        cin>>opt;
        if(opt==1)
        {
            items.display();
            cout << endl << "Enter Serial number Of Item to Add in Bill from Above Available Items: ";
            cin >> item_sr;
            cout << endl << "Enter Quantity: ";
            cin >> qty;
            if(item_sr>0&&item_sr<=((items.getTail())->getNodeValue()).getItemSRNumber())
            {
                item_temp = searchItemByRef(item_sr);
            }
            if (qty > 0 && qty <= item_temp.getItemQuantity())
            {
                bill_item_temp.setQuantity(qty);
                bill_item_temp.setItemName(item_temp.getItemName());
                bill_item_temp.setItemSerial(item_temp.getItemSRNumber());
                bill_item_temp.setPrice(item_temp.getItemSellPrice());
                temp_bill.setItems(bill_item_temp);
                total = total + (qty * item_temp.getItemSellPrice());
                decreaseItemQuantity(item_sr, qty);
            }
        }
        else if(opt==2)
        {
            cout << endl << "Please Enter Discount Percentage: ";
            cin >> disc;
            temp_bill.setDiscount(disc);
        }
        else if(opt==0)
        {
            temp_bill.setDiscount(disc);
            total=total-(total*(disc/100));
            cout<<endl<<"Total is: "<<total<<endl;
            cout<<endl<<"Please Enter the Received Amount: ";
            cin>>amount;
            balance=total-amount;
            cout<<endl<<"Balance: "<<balance<<endl;
            temp_bill.setTotal(total);
            temp_bill.setBalance(balance);
            cout<<temp_bill;
            bills.appendNode(temp_bill);
            cout<<endl<<"Bill SuccessFully Added!!!!!!!"<<endl;
            break;
        }
    }
}

void Company::writeCustomersToFile() 
{
    //This Function Traverses the customers list and writes the customer Object Attributes
    //To A CSV File in each Line
    //Before Writing Objects Attributes It Writes count of customers in First line which is used later for reading Purpose
    ofstream fout;
    Node<Customer>* temp = customer.getHead();
    fout.open("customers.csv", ios::out);
    fout << customer.getCount() << "\n";
    while (temp!= nullptr)
    {
        fout << (temp->getNodeValue()).getCustomerName() << "\n"
            << (temp->getNodeValue()).getCustomerID() << "\n"
            << (temp->getNodeValue()).getPhoneNumber() << "\n";
        temp = temp->getNextNode();
    }
    fout.close();
}

void Company::readCustomersFromFile()
{
    //This function reads data from a CSV File that files contains count of customers ane each customer object sttributes
    //in each line Firstly it Reads count and runs the file lines till that count
    //in while loop there is a for loop used which always starts from zero and goes till the maximum
    //number of attributes an object contains it reads the attributes in order as they are written and stores them in their specific
    //data types after that they are stored in temp object of that class type and that object is added to linked list using append function
    int sr_no,i=0,count;
    string cus_name;
    long phn;
    Customer temp;
    ifstream fin;
    fin.open("customers.csv",ios::in);
    fin>>count;
    while (i<count)
    {
        for (int j = 0; j < 3 ; ++j) 
        {
            if(j==0)
                fin>>cus_name;
            else if(j==1)
                fin>>sr_no;
            else if(j==2)
                fin>>phn;
        }
        temp.setPhoneNumber(phn);
        temp.setCustomerID(sr_no);
        temp.setCustomerName(cus_name);
        customer.appendNode(temp);
        i++;
    }
    fin.close();
}

void Company::addItem()
{
    //this function takes item information from user and stores it in temp object of item
    //and appends the linked list of items
    int srno;
    string name;
    float pur_price, sale_price;
    int qty;
    srno=items.getItemSerial();
    Item temp;
    cout <<"~:((===============================================================)):~" << endl;
    cout<<endl<<"Please enter Item Name: ";
    cin>>name;
    cout<<endl<<"Please enter Item Quantity: ";
    cin>>qty;
    cout<<endl<<"Please Enter Purchase Price: ";
    cin>>pur_price;
    cout<<endl<<"Please Enter selling Price: ";
    cout <<"~:((===============================================================)):~" << endl;
    cin>>sale_price;
    temp.setItemName(name);
    temp.setItemSRNumber(srno);
    temp.setPurchasePrice(pur_price);
    temp.setQuantity(qty);
    temp.setSellPrice(sale_price);
    items.appendNode(temp);
}

void Company::displayItemList() 
{
    items.display();
}

Item Company::searchItemByRef(int srno)
{
    //This function get ID of Items and searches it in linked list if finds it then return the
    //Item object
    Node<Item>* temp = items.getHead();

    while (temp != NULL) 
    {
        if ((temp->getNodeValue()).getItemSRNumber() == srno)
        {
            return temp->getNodeValue();
        }
        temp = temp->getNextNode();
    }
}

void Company::decreaseItemQuantity(int srno, int qty) 
{
    //This function uses Sr number of item and qauntity to be decreases as parameter and
    //gets the Node value of that specific serial number item by refernces and sets it quantity by decrementing it
    Node<Item>* temp = items.getHead();

    while (temp != NULL)
    {
        if ((temp->getNodeValue()).getItemSRNumber() == srno) 
        {
            (temp->getValueByReference()).setQuantity((temp->getNodeValue()).getItemQuantity()-qty);
            break;
        }
        temp = temp->getNextNode();
    }
}

void Company::increaseItemQuantity(int srno, int qty)
{
    //This function uses Sr number of item and qauntity to be increased as parameter and
    //gets the Node value of that specific serial number item by refernces and sets it quantity by Incrementing it
    Node<Item>* temp = items.getHead();
    while (temp != NULL)
    {
        if ((temp->getValueByReference()).getItemSRNumber() == srno) 
        {
            (temp->getValueByReference()).setQuantity((temp->getValueByReference()).getItemQuantity() + qty);
            cout<<endl<<"Quantity Updated"<<endl;
            cout<<temp->getNodeValue();
            break;
        }
        temp = temp->getNextNode();
    }
}

void Company::setItemSellPrice(int srno, float sel_price)
{
    //This function gets Item Serial Number in Parameter and traverses in list
    //if finds the Item the set the new selling price to it
    Node<Item>* temp = items.getHead();
    while (temp != NULL)
    {
        if ((temp->getNodeValue()).getItemSRNumber() == srno)
        {
            (temp->getValueByReference()).setSellPrice(sel_price);
            cout<<endl<<"Price Updated"<<endl;
            cout<<temp->getNodeValue();
            break;
        }
        temp = temp->getNextNode();
    }
}

void Company::setItemPurPrice(int srno, float pur_price)
{
    //This function gets Item Serial Number in Parameter and traverses in list
    //if finds the Item the set the new Purchase price to it
    Node<Item>* temp = items.getHead();
    while (temp != NULL)
    {
        if ((temp->getNodeValue()).getItemSRNumber() == srno) {
            (temp->getValueByReference()).setSellPrice(pur_price);
            cout<<endl<<"Price Updated"<<endl;
            cout<<temp->getNodeValue();
            break;
        }
        temp = temp->getNextNode();
    }
}

void Company::deleteItem(int srno) 
{
    //This function takes ID as input and traverses the linked list of Items and maintains a count as index
    //if finds the Item with ID then call the Delete at index function whose Index is Count
    Node<Item>* t1 = items.getHead();
    int count = 1;
    int check = 0;
    while (t1 != NULL) 
    {
        if (t1->getNodeValue().getItemSRNumber()==srno)
        {
            items.deleteAtIndex(count);
            cout << "Item of SR No.'" << srno << "'deleted" << endl;
            check++;
            break;
        }
        count++;
        t1 = t1->getNextNode();
    }
    if (check == 0)
    {
        cout << "Item of SR No.'" << srno << "'can't be found." << endl;
    }
}
void Company::deleteItem(string name) 
{
    //This function takes Name as input and traverses the linked list of customers and maintains a count as index
    //if finds the customer with Name then call the Delete at index function whose Index is Count
    Node<Item>* temp = items.getHead();
    int count = 1;
    int check = 0;
    while (temp != NULL)
    {
        if (temp->getNodeValue().getItemName() == name)
        {
            items.deleteAtIndex(count);
            check++;
            cout << "Item: " << name << " deleted" << endl;
            break;
        }
        count++;
        temp = temp->getNextNode();
    }
    if (check == 0) 
    {
        cout << "Item: " << name << " couldn't be found." << endl;
    }
}
void Company::searchItem(int srno) {
    //this function traverses from each Item linked list and displays the customer if found with given id
    Node<Item>* temp = items.getHead();
    int check = 0;
    while (temp != NULL) {
        if ((temp->getNodeValue()).getItemSRNumber() == srno) {
            cout << temp->getNodeValue() << endl;
            check++;
            break;
        }
        temp = temp->getNextNode();
    }
    if (check == 0) {
        cout << endl << "Item of '" << srno << "' can't be found." << endl;
    }
}
void Company::searchItem(string name) {
    //this function traverses from each Item linked list and displays the customer if found with given Name
    Node<Item>* temp = items.getHead();
    int check = 0;
    while (temp != NULL) {
        if ((temp->getNodeValue()).getItemName() == name) {
            cout << temp->getNodeValue() << endl;
            check++;
            break;
        }
        temp = temp->getNextNode();
    }
    if (check == 0) {
        cout << endl << "Item '" << name << "' can't be found." << endl;
    }
}

void Company::writeItemsToFile() {
    //This Function Traverses the customers list and writes the Item Object Attributes
    //To A CSV File in each Line
    //Before Writing Objects Attributes It Writes count of Items in First line which is used later for reading Purpose
    ofstream fout;
    Node<Item>*temp=items.getHead();
    fout.open("items.csv",ios::out);
    fout<<items.getCount()<<"\n";
    while (temp!= nullptr){
        fout<<(temp->getNodeValue()).getItemName()<<"\n"
            <<(temp->getNodeValue()).getItemSRNumber()<<"\n"
            <<(temp->getNodeValue()).getItemPurPrice()<<"\n"
            <<(temp->getNodeValue()).getItemSellPrice()<<"\n"
            <<(temp->getNodeValue()).getItemQuantity()<<"\n";
        temp=temp->getNextNode();
    }
    fout.close();
}
void Company::readItemsFromFile() {
    //This function reads data from a CSV File that files contains count of customers ane each customer object sttributes
    //in each line Firstly it Reads count and runs the file lines till that count
    //in while loop there is a for loop used which always starts from zero and goes till the maximum
    //number of attributes an object contains it reads the attributes in order as they are written and stores them in their specific
    //data types after that they are stored in temp object of that class type and that object is added to linked list using append function
    int sr_no,i=0,count,qty;
    string _name;
    float pur_price,sell_price;
    Item temp;
    ifstream fin;
    fin.open("items.csv",ios::in);
    fin>>count;
    while (i<count){
        for (int j = 0; j < 5 ; ++j) {
            if(j==0)
                fin>>_name;
            else if(j==1)
                fin>>sr_no;
            else if(j==2)
                fin>>pur_price;
            else if(j==3)
                fin>>sell_price;
            else if(j==4)
                fin>>qty;
        }
        temp.setItemName(_name);
        temp.setQuantity(qty);
        temp.setSellPrice(sell_price);
        temp.setPurchasePrice(pur_price);
        temp.setItemSRNumber(sr_no);
        items.appendNode(temp);
        i++;
    }
    fin.close();
}
//Vendor
void Company::readVendors() {
    //This function reads data from a CSV File that files contains count of customers ane each customer object sttributes
    //in each line Firstly it Reads count and runs the file lines till that count
    //in while loop there is a for loop used which always starts from zero and goes till the maximum
    //number of attributes an object contains it reads the attributes in order as they are written and stores them in their specific
    //data types after that they are stored in temp object of that class type and that object is added to linked list using append function
    int sr_no,i=0,count;
    string cus_name;
    long phn;
    Vendor temp;
    ifstream fin;
    fin.open("vendors.csv",ios::in);
    fin>>count;
    while (i<count){
        for (int j = 0; j < 3 ; ++j) {
            if(j==0)
                fin>>cus_name;
            else if(j==1)
                fin>>sr_no;
            else if(j==2)
                fin>>phn;
        }
        temp.setVenPhoneNumber(phn);
        temp.setVendorID(sr_no);
        temp.setVendorName(cus_name);
        vendors.appendNode(temp);
        i++;
    }
    fin.close();
}
void Company::writeVendors() {
    //This Function Traverses the vendors list and writes the vendor Object Attributes
    //To A CSV File in each Line
    //Before Writing Objects Attributes It Writes count of VEndors in First line which is used later for reading Purpose
    ofstream fout;
    Node<Vendor>*temp=vendors.getHead();
    fout.open("vendors.csv",ios::out);
    fout<<vendors.getCount()<<"\n";
    while (temp!= nullptr){
        fout<<(temp->getNodeValue()).getVendorName()<<"\n"
            <<(temp->getNodeValue()).getVendorID()<<"\n"
            <<(temp->getNodeValue()).getVenPhoneNumber()<<"\n";
        temp=temp->getNextNode();
    }
    fout.close();
}
void Company::addVendor() {
    //this functions add new vendor to end after taking input from user and calls append funation for linked list
    int vendor_id;
    long num;
    string name;
    vendor_id=vendors.getItemSerial();
    cout << endl << "Please enter Vendor's Name: ";
    cin >> name;
    cout << endl << "Please enter Vendor's Phone Number: ";
    cin >> num;
    Vendor temp;
    temp.setVendorID(vendor_id);
    temp.setVendorName(name);
    temp.setVenPhoneNumber(num);
    vendors.appendNode(temp);
}
void Company::displayVendorList() {
    vendors.display();
}
void Company::deleteVendor(int id) {
    //This function takes ID as input and traverses the linked list of VENDORS and maintains a count as index
    //if finds the vendor with ID then call the Delete at index function whose Index is Count
    Node<Vendor>* t1 = vendors.getHead();
    int count = 1;
    int check = 0;
    while (t1 != NULL) {
        if (t1->getNodeValue().getVendorID() == id) {
            vendors.deleteAtIndex(count);
            cout << "Vendor of '" << id << "'deleted" << endl;
            check++;
            break;
        }
        count++;
        t1 = t1->getNextNode();
    }
    if (check == 0) {
        cout << "Vendor of ID'" << id << "'can't be found." << endl;
    }
}
void Company::deleteVendor(string name) {
    //This function takes NAmE as input and traverses the linked list of VENDORS and maintains a count as index
    //if finds the vendor with NAME then call the Delete at index function whose Index is Count
    Node<Vendor>* t1 = vendors.getHead();
    int count = 1;
    int check = 0;
    while (t1 != NULL) {
        if (t1->getNodeValue().getVendorName() == name) {
            vendors.deleteAtIndex(count);
            cout << "Vendor '" << name << "'deleted" << endl;
            check++;
            break;
        }
        count++;
        t1 = t1->getNextNode();
    }
    if (check == 0) {
        cout << "Vendor '" << name << "'can't be found." << endl;
    }
}
void Company::searchVendor(int id) {
    //this function traverses from each vendor linked list and displays the vendor if found with given ID
    Node<Vendor>* temp = vendors.getHead();
    int check = 0;
    while (temp != NULL) {
        if ((temp->getNodeValue()).getVendorID() == id) {
            cout << temp->getNodeValue() << endl;
            check++;
            break;
        }
        temp = temp->getNextNode();
    }
    if (check == 0) {
        cout << endl << "Vendor of name: '" << id << "' can't be found." << endl;
    }
}
void Company::searchVendor(string name) {
    //this function traverses from each vendor linked list and displays the vendor if found with given Name
    Node<Vendor>* temp = vendors.getHead();
    int check = 0;
    while (temp != NULL) {
        if ((temp->getNodeValue()).getVendorName() == name) {
            cout << temp->getNodeValue() << endl;
            check++;
            break;
        }
        temp = temp->getNextNode();
    }
    if (check == 0) {
        cout << endl << "Vendor of name: '" << name << "' can't be found." << endl;
    }
}

void Company::menu(){

    int option;
    do {
        //system("clear");
        cout<< "~:((*********************************************************)):~" << endl;
        cout << "\tEnter 1 to go to Customer's Menu" << endl;
        cout << "\tEnter 2 to go to Vendor's Menu" << endl;
        cout << "\tEnter 3 to go to Item's Menu" << endl;
        cout << "\tEnter 0 to Exit " << endl;
        cout <<"~:((********************************************************)):~" << endl;
        cin >> option;
        switch (option) {
            case 1:
            {
                customerMenu();
                break;
            }
            case 2:
            {
                vendorsMenu();
                break;
            }
            case 3:
            {
                itemsMenu();
                break;
            }
        }
    } while (option != 0);

}


//Bill Functions
void Company::displayBill() {
    bills.display();
}

void Company::writeBillsToFile() {
    //This Function Traverses the bills list and writes the bill Object Attributes
    //To A CSV File in each Line
    //Before Writing Objects Attributes It Writes count of bills in First line which is used later for reading Purpose
    ofstream fout;
    Node<Bill>*temp=bills.getHead();
    fout.open("bills.csv",ios::out);
    fout<<bills.getCount()<<"\n";
    while (temp!= nullptr){
        fout<<(temp->getNodeValue()).getCustomerIDBill()<<"\n"
            <<(temp->getNodeValue()).getBalance()<<"\n"
            <<(temp->getNodeValue()).getName()<<"\n"
            <<(temp->getNodeValue()).getBillNum()<<"\n"
            <<(temp->getNodeValue()).getTotal()<<"\n"
            <<(temp->getNodeValue()).getDiscount()<<"\n";
       // (temp->getNodeValue()).displayBillItems();
        temp=temp->getNextNode();
    }
    fout.close();
}

void Company::readBillsFromFile() {
//This function reads data from a CSV File that files contains count of customers ane each customer object sttributes
//in each line Firstly it Reads count and runs the file lines till that count
//in while loop there is a for loop used which always starts from zero and goes till the maximum
//number of attributes an object contains it reads the attributes in order as they are written and stores them in their specific
//data types after that they are stored in temp object of that class type and that object is added to linked list using append function
    int cus_id,bill_no,i=0,count;
    string cus_name;
    float total,discount,bal;
    Bill temp;
    ifstream fin;
    fin.open("bills.csv",ios::in);
    fin>>count;
    while (i<count){
        for (int j = 0; j < 6 ; ++j) {
            if(j==0)
                fin>>cus_id;
            else if(j==1)
                fin>>bal;
            else if(j==2)
                fin>>cus_name;
            else if(j==3)
                fin>>bill_no;
            else if(j==4)
                fin>>total;
            else if(j==5)
                fin>>discount;
        }
        temp.setBalance(bal);
        temp.setTotal(total);
        temp.setCustomerIDBill(cus_id);
        temp.setName(cus_name);
        temp.setBillNo(bill_no);
        temp.setDiscount(discount);
        bills.appendNode(temp);
        i++;
    }
    fin.close();

}

void Company::createVendorBill() {
    items.display();
    float newpprice,newsprice,payed;
    cout<<endl<<"Enter 1 to create Bill for Existing Items"<<endl<<
    "Enter 2 to create Bill for New Items"<<endl;
    int opt;
    cin>>opt;
    if (opt==1){
        vendors.display();

            int item_srno,bill_num,vendor_id,qty;
            items.display();
            Bill btemp;
            bill_num=bills.getItemSerial();
            cout<<endl<<"Please Enter Item Serial Number"<<endl;
            cin>>item_srno;
            cout<<endl<<"Please Enter Quantity"<<endl;
            cin>>qty;
            if(item_srno>0&&item_srno<items.getItemSerial()) {
                Item tempitem = searchItemByRef(item_srno);

                vendors.display();
                cout << endl << "Please Enter the Vendor ID" << endl;
                cin >> vendor_id;
                if(vendor_id>0&&vendor_id<vendors.getItemSerial()){
                    Vendor vtemp= getVendor(vendor_id);
                    ItemBill tempitembill;
                    tempitembill.setItemSerial(item_srno);
                    tempitembill.setQuantity(qty);
                    cout<<endl<<"Enter 1 Create Bill With NewPrices Prices"<<endl<<
                    "Enter 0 to Create Bill With Old Prices"<<endl;
                    int opt3;
                    cin>>opt3;
                    if(opt3==1){
                        cout<<endl<<"Please Enter new Purchase Price"<<endl;
                        cin>>newpprice;
                        cout<<endl<<"Please Enter new Selling Price"<<endl;
                        cin>>newsprice;
                        tempitem.setPurchasePrice(newpprice);
                        tempitem.setSellPrice(newsprice);


                    }else if(opt3==0){
                        cout<<endl<<"Generating Bill With Old Prices"<<endl;
                    }
                    tempitembill.setPrice(tempitem.getItemPurPrice());
                    tempitembill.setItemName(tempitem.getItemName());
                    btemp.setBillNo(bill_num);
                    btemp.setCustomerIDBill(vendor_id);
                    btemp.setItems(tempitembill);
                    btemp.setName(vtemp.getVendorName());
                    btemp.setTotal(tempitem.getItemPurPrice()*qty);
                    cout<<endl<<"Total: "<<tempitem.getItemPurPrice()*qty;
                    cout<<"Please Enter The Amount Payed: ";
                    cin>>payed;
                    cout<<endl<<"Balance is: "<<(tempitem.getItemPurPrice()*qty)-payed;
                    btemp.setBalance((tempitem.getItemPurPrice()*qty)-payed);
                    bills.appendNode(btemp);
                    cout<<endl<<"Bill Generated"<<endl;

                }else{
                    cout<<endl<<"Wrong Vendor ID"<<endl;
                }
            }else{
                cout<<endl<<"Wrong Serial Input"<<endl;
            }

    }else if(opt==2){

    }

}

Vendor Company::getVendor(int id) {
    //thsi function takes ID of Vendor In parameter and searches the specific ID Vendor in Linked List Through Traversion
    //If finds then return the Vendor Object
    Node<Vendor>* temp = vendors.getHead();
    while (temp != NULL) {
        if ((temp->getNodeValue()).getVendorID() == id) {
            return temp->getNodeValue();
        }
        temp = temp->getNextNode();
    }
}


void Company::customerMenu() {
    int option1;
    do {
        cout <<"~:((===============================================================)):~" << endl;
        cout << endl << "Enter 1 to Add new Customer" << endl <<
             "Enter 2 to display Customers List" << endl <<
             "Enter 3 to Create Customer Bill" << endl <<
             "Enter 4 to Display Bill" << endl <<
             "Enter 5 to Delete Customer By Name" << endl <<
             "Enter 6 to Delete Customer By ID" << endl <<
             "Enter 7 to Search Customer By ID" << endl <<
             "Enter 8 to Search Customer By Name" << endl <<
             "Enter 9 to Sort the Customer's ID from Radix Sort" << endl <<
             "Enter 10 to Sort the Customer's from Merge Sort Using Names" << endl <<
             "Enter 11 to go to main menu" << endl;
        cout <<"~:((===============================================================)):~" << endl;
        cin >> option1;
        if (option1 == 1) {
            system("clear");
            addCustomer();
            cout << endl << "Customer Added!!!!!!" << endl;
            system("clear");
        }
        else if (option1 == 2) {

            customer.display();

        }
        else if (option1 == 3) {

            system("clear");
            if(items.isListEmpty()==false) {
                int opt, id;
                cout << endl << "Enter '1' to Create Bill from Existing Customers" << endl <<
                     "Enter '2' To Add New Customer and Create Bill" << endl;
                cin >> opt;
                if (opt == 1) {
                    customer.display();
                    cout << endl << "Please Enter The ID of Customer To create Bill ";
                    cin >> id;
                    if (id > 0 && id <= ((customer.getTail())->getNodeValue()).getCustomerID()) {
                        Customer temp = getCustomer(id);
                        createCustomerBill(temp);
                    } else {
                        cout << endl << "ID Not Found!!!!!!" << endl;
                    }
                } else if (opt == 2) {
                    addCustomer();
                    customer.display();
                    cout << endl << "Please Enter The ID of Customer To create Bill ";
                    cin >> id;
                    if (id > 0 && id <= ((customer.getTail())->getNodeValue()).getCustomerID()) {
                        Customer temp = getCustomer(id);
                        createCustomerBill(temp);
                    } else {
                        cout << endl << "ID Not Found!!!!!!" << endl;
                    }
                }
            } else{
                cout<<endl<<"Item List Is Empty Cannot Create Bill Please Add Item From MAin Menu"<<endl;
            }

        }
        else if (option1 == 4) {

            bills.display();

        }
        else if (option1 == 5) {

            system("clear");
            string name;
            cout << "Enter the name of the customer to delete: " << endl;
            cin.ignore();
            getline(cin, name);
            deleteCustomer(name);

        }
        else if (option1 == 6) {

            system("clear");
            int num;
            cout << "Enter the id of the customer to delete: " << endl;
            cin >> num;
            deleteCustomer(num);
        }
        else if (option1 == 7) {

            system("clear");
            int num;
            cout << "Enter customer id to search " << endl;
            cin >> num;
            searchCustomer(num);
        }
        else if (option1 == 8) {

            system("clear");
            string name;
            cout << "Enter customer name to search " << endl;
            cin >> name;
            searchCustomer(name);
        }
        else if (option1 == 9) {
            system("clear");
            if(customer.isListEmpty()==false) {
            radix_sort_customer();
            cout << "SORTED CUSTOMER ARE" << endl;
            customer.display();
            }else{
                cout<<endl<<"Customers List is Empty cannot Sort"<<endl;
            }
        }
        else if (option1 == 10) {
            system("clear");
            if(customer.isListEmpty()==false) {
                mergeSortCustomer(customer.getHeadByReference(), customer.getTailByReference(), customer.getCount());
                cout<<endl<<"Sorted Customers Are: "<<endl;
                customer.display();
            }else{
                cout<<endl<<"Customers List is Empty cannot Sort"<<endl;
            }



        }
        else if (option1 == 11) {
            system("clear");
            return;
        }
    } while (option1 != 0);
}

void Company::vendorsMenu() {
    int option2;
    do {
        cout <<"~:((===============================================================)):~" << endl;
        cout << endl << "Enter 1 to Add new Vendor" << endl <<
             "Enter 2 to display Vendors List" << endl <<
             "Enter 3 to Delete Vendor By Name" << endl <<
             "Enter 4 to Delete Vendor By ID" << endl <<
             "Enter 5 to Search Vendor By ID" << endl <<
             "Enter 6 to Search Vendor By Name" << endl <<
             "Enter 7 to go to main menu" << endl;
        cout <<"~:((===============================================================)):~" << endl;
        cin >> option2;
        if (option2 == 1) {
            system("clear");
            addVendor();
            cout << endl << "Vendor Added!!!!!!" << endl;
            system("clear");
        }
        else if (option2 == 2) {
            vendors.display();

        }
        else if (option2 == 3) {
            system("clear");
            string name;
            cout << "Enter the name of the vendor to delete: " << endl;
            cin.ignore();
            getline(cin, name);
            deleteVendor(name);

        }
        else if (option2 == 4) {
            system("clear");
            int num;
            cout << "Enter the id of the vendor to delete: " << endl;
            cin >> num;
            deleteVendor(num);


        }
        else if (option2 == 5) {
            system("clear");
            int num;
            cout << "Enter the ID of the Vendor to search " << endl;
            cin >> num;
            searchVendor(num);


        }
        else if (option2 == 6) {
            system("clear");
            string name;
            cout << "Enter Vendor's name to search " << endl;
            cin >> name;
            searchVendor(name);


        }
        else if (option2 == 7) {
            system("clear");
            return;


        }

    } while (option2 != 0);
}

void Company::itemsMenu() {
    int option3;
    do {
        cout <<"~:((===============================================================)):~" << endl;
        cout << endl << "Enter 1 to Add new Item" << endl <<
             "Enter 2 to display Items List" << endl <<
             "Enter 3 to Delete Item By Name" << endl <<
             "Enter 4 to Delete Item By SR No." << endl <<
             "Enter 5 to Search Item By SR No." << endl <<
             "Enter 6 to Search Item By Name" << endl <<
             "Enter 7 to sort Item's SR No. from Radix Sort" << endl <<
             "Enter 8 to sort Item's Name from Merge Sort" << endl <<
             "Enter 9 to Add New Quantity to Items" << endl <<
             "Enter 10 to set New Purchase Price" << endl <<
             "Enter 11 to set New Selling Price" << endl<<
             "Enter 12 to get to MAIN MENU" << endl;
        cout <<"~:((===============================================================)):~" << endl;
        cin >> option3;
        if (option3 == 1) {
            system("clear");
            addItem();
            cout << endl << "Item Added!!!!!!" << endl;
            system("clear");
        }
        else if (option3 == 2) {

            items.display();
        }

        else if (option3 == 3) {

            system("clear");
            string n;
            cout << "Enter the name of the item to delete: " << endl;
            cin.ignore();
            getline(cin, n);
            deleteItem(n);
        }
        else if (option3 == 4) {

            system("clear");
            int num;
            cout << "Enter the id of the item to delete: " << endl;
            cin >> num;
            deleteItem(num);
        }
        else if (option3 == 5) {

            system("clear");
            int num;
            cout << "Enter the ID of the Item to search " << endl;
            cin >> num;
            searchItem(num);
        }
        else if (option3 == 6) {

            system("clear");
            string name;
            cout << "Enter Item's name to search " << endl;
            cin >> name;
            searchItem(name);
        }
        else if (option3 == 7) {
            system("clear");
            if(items.isListEmpty()== false) {
            radix_sort_items();
            cout << "SORTED" << endl;
            items.display();
            }else{
                cout<<endl<<"Items List Is Empty"<<endl;
            }
        }
        else if (option3 == 8) {
            system("clear");
            if(items.isListEmpty()== false) {
                mergeSortItems(items.getHeadByReference(), items.getTailByReference(), items.getCount());
                cout << endl << "Sorted Items Are: " << endl;
                items.display();
            }else{
                cout<<endl<<"Items List Is Empty"<<endl;
            }

        }
        else if (option3 == 12) {
            system("clear");
            return;
        }
        else if (option3 == 9) {
            system("clear");
            if(items.isListEmpty()==false){
                items.display();
                int srno,qty;
                cout<<endl<<"Please Enter Item Sr Number:" ;
                cin>>srno;
                cout<<endl<<"Please Enter Quantity To Add";
                cin>>qty;
                if(srno>0&&srno<=items.getItemSerial()){
                    increaseItemQuantity(srno,qty);
                }else{
                    cout<<endl<<"Serial Number Beyond Limit"<<endl;
                }
            }
        }
        else if (option3 == 10) {
            system("clear");
            if(items.isListEmpty()==false){
                items.display();
                int srno;
                float price;
                cout<<endl<<"Please Enter Item Sr Number:" ;
                cin>>srno;
                cout<<endl<<"Please Enter New Purchase Price To Add";
                cin>>price;
                if(srno>0&&srno<=items.getItemSerial()){
                    setItemPurPrice(srno,price);
                }else{
                    cout<<endl<<"Serial Number Beyond Limit"<<endl;
                }
            }
        }
        else if (option3 == 11) {
            system("clear");
            if(items.isListEmpty()==false){
                items.display();
                int srno;
                float price;
                cout<<endl<<"Please Enter Item Sr Number:" ;
                cin>>srno;
                cout<<endl<<"Please Enter New Selling Price To Add";
                cin>>price;
                if(srno>0&&srno<=items.getItemSerial()){
                    setItemSellPrice(srno,price);
                }else{
                    cout<<endl<<"Serial Number Beyond Limit"<<endl;
                }
            }
        }



    } while (option3 != 0);
}

void Company::mergeSortCustomer(Node<Customer> * & head, Node<Customer> *& tail, int cnt) {
    //This function takes in Parameters the Head And Tail Node of Customer Linked List by refernece and its count
    //after the it divides the count into two and calls the merge funtion for first and then second part
    //merge function is called till the linked list of single value is obtained then the merge function for that
    //part is called which compares the both parts names and nad places them in alphabetic order in new linked list
    //this merge and merge sort function is called in recursion
    Node<Customer> *partA;
    Node<Customer> *partB;
    Node<Customer> *temp = head;


    if (cnt == 1 || temp->getNextNode() == nullptr) {

        return;
    } else {

        int mid = cnt / 2.00;
        int remaining_count = cnt - mid;
        partA = head;

        for (int i = 0; i < mid - 1 && temp != nullptr; ++i) {
            temp = temp->getNextNode();
        }
        partB = temp->getNextNode();
        temp->setNextNode(nullptr);
        mergeSortCustomer(partA, temp, mid);
        mergeSortCustomer(partB, tail, remaining_count);

        mergeCustomer(partA, partB, head, tail);


    }
}

void Company::mergeCustomer(Node<Customer> * partA, Node<Customer> *partB, Node <Customer> * & mergedHead , Node <Customer> * & mergedTail) {
    //This function takes two parts pointers value and compare those part value with each other whose part specific
    //index value is less that is placed first in new list and so on

    Node<Customer> *partChead = nullptr;
    Node<Customer> *partCtail = nullptr;

    while (partA != nullptr && partB != nullptr) {
        if ((partA->getNodeValue()).getCustomerName() < (partB->getNodeValue()).getCustomerName()) {
            if (partChead == nullptr) {
                partChead = partA;
                partCtail = partA;
                partA = partA->getNextNode();
                partCtail->setNextNode(nullptr);
            } else {

                partCtail->setNextNode(partA);
                partCtail = partCtail->getNextNode();
                partA = partA->getNextNode();
                partCtail->setNextNode(nullptr);
            }
        } else {
            if (partChead == nullptr) {
                partChead = partB;
                partCtail = partB;
                partB = partB->getNextNode();
                partCtail->setNextNode(nullptr);
            } else {

                partCtail->setNextNode(partB);
                partCtail = partCtail->getNextNode();
                partB = partB->getNextNode();
                partCtail->setNextNode(nullptr);
            }

        }
    }
    while (partA != nullptr) {
        if (partChead == nullptr) {
            partChead = partA;
            partCtail = partA;
            partA = partA->getNextNode();
            partCtail->setNextNode(nullptr);
        } else {

            partCtail->setNextNode(partA);
            partCtail = partA;
            partA = partA->getNextNode();
            partCtail->setNextNode(nullptr);
        }

    }
    while (partB != nullptr) {
        if (partChead == nullptr) {
            partChead = partB;
            partCtail = partB;
            partB = partB->getNextNode();
            partCtail->setNextNode(nullptr);
        } else {

            partCtail->setNextNode(partB);
            partCtail = partB;
            partB = partB->getNextNode();
            partCtail->setNextNode(nullptr);
        }

    }
    mergedHead = partChead;
    mergedTail = partCtail;


}

void Company::mergeSortItems(Node<Item> * & head, Node<Item> *& tail, int cnt) {
    //This function takes in Parameters the Head And Tail Node of Items Linked List by refernece and its count
    //after the it divides the count into two and calls the merge funtion for first and then second part
    //merge function is called till the linked list of single value is obtained then the merge function for that
    //part is called which compares the both parts names and nad places them in alphabetic order in new linked list
    //this merge and merge sort function is called in recursion
    Node<Item> *partA;
    Node<Item> *partB;
    Node<Item> *temp = head;


    if (cnt == 1 || temp->getNextNode() == nullptr) {

        return;
    } else {

        int mid = cnt / 2.00;
        int remaining_count = cnt - mid;
        partA = head;

        for (int i = 0; i < mid - 1 && temp != nullptr; ++i) {
            temp = temp->getNextNode();
        }
        partB = temp->getNextNode();
        temp->setNextNode(nullptr);
        mergeSortItems(partA, temp, mid);
        mergeSortItems(partB, tail, remaining_count);

        mergeItems(partA, partB, head, tail);


    }
}

void Company::mergeItems(Node<Item> * partA, Node<Item> *partB, Node <Item> * & mergedHead , Node <Item> * & mergedTail) {
    //This function takes two parts pointers value and compare those part value with each other whose part specific
    //index value is less that is placed first in new list and so on
    Node<Item> *partChead = nullptr;
    Node<Item> *partCtail = nullptr;

    while (partA != nullptr && partB != nullptr) {
        if ((partA->getNodeValue()).getItemName() < (partB->getNodeValue()).getItemName()) {
            if (partChead == nullptr) {
                partChead = partA;
                partCtail = partA;
                partA = partA->getNextNode();
                partCtail->setNextNode(nullptr);
            } else {

                partCtail->setNextNode(partA);
                partCtail = partCtail->getNextNode();
                partA = partA->getNextNode();
                partCtail->setNextNode(nullptr);
            }
        } else {
            if (partChead == nullptr) {
                partChead = partB;
                partCtail = partB;
                partB = partB->getNextNode();
                partCtail->setNextNode(nullptr);
            } else {

                partCtail->setNextNode(partB);
                partCtail = partCtail->getNextNode();
                partB = partB->getNextNode();
                partCtail->setNextNode(nullptr);
            }

        }
    }
    while (partA != nullptr) {
        if (partChead == nullptr) {
            partChead = partA;
            partCtail = partA;
            partA = partA->getNextNode();
            partCtail->setNextNode(nullptr);
        } else {

            partCtail->setNextNode(partA);
            partCtail = partA;
            partA = partA->getNextNode();
            partCtail->setNextNode(nullptr);
        }

    }
    while (partB != nullptr) {
        if (partChead == nullptr) {
            partChead = partB;
            partCtail = partB;
            partB = partB->getNextNode();
            partCtail->setNextNode(nullptr);
        } else {

            partCtail->setNextNode(partB);
            partCtail = partB;
            partB = partB->getNextNode();
            partCtail->setNextNode(nullptr);
        }

    }
    mergedHead = partChead;
    mergedTail = partCtail;


}

int Company::find_max_Item() //find the max sr numbr
{
    //This function Finds the Item in Linked list with maximum Serial number after traversion Starting
    //linked list head till null pointer
    Node<Item>* temp = items.getHead();
    int max = 0;
    while (temp != NULL) {

        if (max < temp->getNodeValue().getItemSRNumber())
        {
            max = temp->getNodeValue().getItemSRNumber();
        }
        temp = temp->getNextNode();
    }
    return max;
}

void Company::count_sort_items(Node<Item>**& count_array, int exp, int length) {
    int cumm_sum[11] = { 0 };//initialized to zero

    for (int j = 0; j < length; j++)
    {
        int digit = int(count_array[j]->getNodeValue().getItemSRNumber() / pow(10, exp - 1)) % 10;//to get the least significant digit we take the mode and the increment the whole array to get to the significant digit and so on.
        cumm_sum[digit + 1]++;//increment
    }

    for (int j = 1; j < 11; j++)
    {
        cumm_sum[j] += cumm_sum[j - 1];
    }

    Node<Item>** temp = new Node<Item>*[length];
    for (int j = 0; j < length; j++)
    {

        int digit = int(count_array[j]->getNodeValue().getItemSRNumber() / pow(10, exp - 1)) % 10;//Firstly we will apply the previous logc to get the least to most significant digits
        temp[cumm_sum[digit]] = count_array[j];
        cumm_sum[digit]++;

    }
    count_array = temp;
}
void Company::radix_sort_items() {
    //this function firstly finds the maximum serial or Id number through find max function
    //then applies count sort starting from right till least most significant digit on ID's or Serial number of objects
    //present in Linked List
    int length = items.getCount();
    int max = find_max_Item();
    int num = 0;
    while (int(max / pow(10, num)) != 0)
    {
        num++;
    }
    Node<Item>** count_array = new Node<Item>*[length];

    Node<Item>* current = items.getHead();

    for (int i = 0; i < length; i++)
    {
        count_array[i] = current;
        current = current->getNextNode();
    }
    for (int i = 1; i <= num; i++)
    {
        count_sort_items(count_array, i, length);
    }
    items.set_head(count_array[0]);
    items.set_tail(count_array[length - 1]);
    count_array[length - 1]->setNextNode(NULL);
    for (int i = 0; i < length - 1; i++)
    {
        count_array[i]->setNextNode(count_array[i + 1]);
    }
}


int Company::find_max_Customer() //This function finds the max id of the customer
{

    //This function Finds the Customer in Linked list with maximum ID  number after traversion Starting
    //linked list head till null pointer
    Node<Customer>* temp = customer.getHead();
    int max=0;
    while (temp != NULL) {

        if (max < temp->getNodeValue().getCustomerID())
        {
            max = temp->getNodeValue().getCustomerID();
        }
        temp = temp->getNextNode();
    }
    return max;
}
void Company::count_sort_customer(Node<Customer>**& count_array, int exp, int length)
{
    int cumm_sum[11] = { 0 }; //Initialized to zero

    for (int j = 0; j < length; j++)
    {
        int digit = int(count_array[j]->getNodeValue().getCustomerID() / pow(10, exp - 1)) % 10;//to get the least significant digit we take the mode and the increment the whole array to get to the significant digit and so on.
        cumm_sum[digit + 1]++;
    }

    for (int j = 1; j < 11; j++)
    {
        cumm_sum[j] += cumm_sum[j - 1];//Add the previous value
    }

    Node<Customer>** temp = new Node<Customer>*[length];
    for (int j = 0; j < length; j++)
    {

        int digit = int(count_array[j]->getNodeValue().getCustomerID() / pow(10, exp - 1)) % 10;//Firstly we will apply the previous logc to get the least to most significant digits
        temp[cumm_sum[digit]] = count_array[j];//copying
        cumm_sum[digit]++;

    }
    count_array = temp;
}

void Company::radix_sort_customer() {
    //this function firstly finds the maximum serial or Id number through find max function
    //then applies count sort starting from right till least most significant digit on ID's or Serial number of objects
    //present in Linked List
    int length=customer.getCount();
    int max = find_max_Customer();
    int num = 0;
    while (int(max / pow(10, num)) != 0)
    {
        num++;
    }
    Node<Customer>** count_array = new Node<Customer>*[length];

    Node<Customer>* current = customer.getHead();

    for (int i = 0; i < length; i++)
    {
        count_array[i] = current;
        current = current->getNextNode();
    }
    for (int i = 1; i <= num; i++)
    {
        count_sort_customer(count_array,i,length);
    }
    customer.set_head(count_array[0]);
    customer.set_tail(count_array[length - 1]);
    count_array[length - 1]->setNextNode(NULL);
    for (int i = 0; i < length-1; i++)
    {
        count_array[i]->setNextNode(count_array[i + 1]);
    }
}
