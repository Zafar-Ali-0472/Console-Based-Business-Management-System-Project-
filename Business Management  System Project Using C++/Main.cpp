#include <iostream>
#include "Company.h"

int main()
{
    int option;
    Company C1;
    cout <<"~:((===============================================================)):~" << endl << endl;
    cout <<"WELCOME TO BUSINESS MANAGEMENT SYSTEM " <<endl << endl;
    cout <<"\tEnter 1 to Login the System Administration " <<endl;
    cout <<"\tEnter 0 to Exit the System " <<endl << endl;
    cout <<"~:((===============================================================)):~" << endl;
    cin >>option;

    if(option==1)
    {
        C1.menu();

    }
    else if(option==0)
    {
        cout <<"Exiting the System .......... " << endl;
        return 0;
    }
    else
    {
        cout<<"Invalid Input, TRy Again ...... " << endl;
    }
}