#include<iostream>
#include"Customer.h"
#include"Customer.cpp"
#include"Admin.h"
#include"Admin.cpp"
using namespace std;


void user_optional(string opt)               /* FUNCTION FOR USER AND ADMIN ON MAIN PAGE */
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);     /* FOR TEXT COLOUR */
    Customer c;                                     /* CLASS OBJECT */
    Admin a;                                        /* CLASS OBJECT */

    if(opt == "1")
    {
        system("CLS");
        c.order();
    }

    else if (opt == "2")
	{
		system("CLS");
		a.adminAuthentication();
	}

    else
    {
        SetConsoleTextAttribute(h,4);
        cout << "\n\t\t\t\t\t\tInvalid input. Please try again!\n";
        SetConsoleTextAttribute(h,7);
        system("pause");
    }
}


int main() {                                 /* MAIN PAGE */
    string user_opt;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    do{

    system("cls");

    // MAIN PAGE INTERFACE
    SetConsoleTextAttribute(h,6);
    cout << "\n\t\t\t\t   ......................................................";
    cout << "\n\t\t\t\t   |\t\t\t\t\t\t\t|";
    cout << "\n\t\t\t\t   |\t\t\t   Foodie\t\t\t|";
    cout << "\n\t\t\t\t   |\t\t\t\t\t\t\t|";
    cout << "\n\t\t\t\t   ......................................................\n";
    SetConsoleTextAttribute(h,14);
    cout << "\n\t\t\t\t\t  Welcome! It is our pleasure to serve you.";

    SetConsoleTextAttribute(h,6);
    cout << "\n\n\t\t\t\t   ------------------------------------------------------\n";
    SetConsoleTextAttribute(h,7);
    cout << "\n\t\t\t\t\t\t\t  Customer \t\t\t\n" << endl;
    SetConsoleTextAttribute(h,10);
    cout << "\t\t\t\t\t\t       <1> Take Order \t\t\t" << endl;
    SetConsoleTextAttribute(h,6);
    cout << "\n\t\t\t\t   ------------------------------------------------------";

    SetConsoleTextAttribute(h,7);
    cout << "\n\n\t\t\t\t\t\t\t   Admin\n" << endl;
    SetConsoleTextAttribute(h,9);
    cout << "\t\t\t\t\t\t\t <2> Login" << endl;

    SetConsoleTextAttribute(h,6);
    cout << "\n\t\t\t\t   ------------------------------------------------------\n";

    SetConsoleTextAttribute(h,7);
    cout << "\n\n\t\t\t\t    >> Please select an option (1/2) : ";

    // GO TO THE NEXT PAGE
        cin >> user_opt;
        user_optional(user_opt);
    } while (user_opt!= "1" && user_opt!= "2");

    return 0;
}
