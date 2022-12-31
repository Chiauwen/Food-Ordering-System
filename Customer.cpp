#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <Windows.h>

#include "main.h"
#include "Customer.h"

using namespace std;


void Menu::menu() /* FUNCTION TO DISPLAY MENU FROM MENU.TXT */
{
    system("cls");
    file.open("menu.txt", ios::in);
    SetConsoleTextAttribute(h, 6);
    cout << "\t\t\t\t\t\t....................";
    cout << "\n \t\t\t\t\t\t|\tMENU\t   |\n";
    cout << "\t\t\t\t\t\t....................\n";
    cout << endl;
    SetConsoleTextAttribute(h, 15);
    cout << "\t\t ================================================================================" << endl;
    cout << setw(5) << "\t\t |  P.NO  |"
         << "\t\t\t NAME  \t\t\t"
         << " |\t   PRICE   \t|" << endl;
    cout << "\t\t ================================================================================" << endl;

    file >> pno >> name >> price;

    while (!file.eof()) /* IF NOT AT END OF FILE, THEN CONTINUE TO READ DATA FROM FILE */
    {
        cout << "\t\t |" << setw(5) << pno << "   | " << setw(10) << name << "\t\t\t\t"
             << " |\t " << setw(5) << price << "     \t|" << endl;
        file >> pno >> name >> price;
    }
    cout << "\t\t ================================================================================" << endl;
    file.close();
    SetConsoleTextAttribute(h, 7);
    cout << "\n\t\t Press Enter to Place Order ->" << endl;
    getch();
}

void Menu::loading() /* FUNCTION FOR LOADING BAR */
{
    char a = 177, b = 219;
    cout << "\t\t\t\t\t    ";
    for (int i = 0; i <= 25; i++)
        cout << a;
    Sleep(30);
    cout << "\r";
    cout << "\t\t\t\t\t    ";
    for (int i = 0; i <= 25; i++)
    {
        SetConsoleTextAttribute(h, 10);
        cout << b;
        Sleep(80); /* TRANSITION SPEED */
    }
}

void Customer::countdown()
{
    int counter = 9; // amount of seconds
    Sleep(10);

    while (counter >= 1)
    {
        cout << "\r You will return back to main menu in " << counter << " seconds....."<< flush;
        Sleep(1000);
        counter--;
    }

    mainPage();
}

void Customer::order() /* FUNCTION TO PLACE ORDER FROM CUSTOMER */
{
displaymenu:

    bool full = false;
    int queueNum;
    int counter = 0;
    bool emptyQueue = file.peek() == std::ifstream::traits_type::eof();
    string newQueue;

    // QUEUE
    file.open("queue.txt", ios::in);

    if (file)
    {
        if (!emptyQueue)
        {
            while (!file.eof()) /* IF NOT AT END OF FILE, THEN CONTINUE TO READ DATA FROM FILE */
            {
                file >> queueNum;
                if (counter != 0)
                {
                    newQueue.append(" ");
                }
                newQueue.append(to_string(queueNum));
                counter++;
            }

            if (counter >= 30)
            { /*MAX CUSTOMER 30*/
                full_queue();
                full = true;
            }
            else
            {
                if (queueNum >= 30)
                {
                    queueNum = 0;
                }
            }
        }
        else
        {
            queueNum = 0;
        }
        file.close();
    }

    // if the queue is not full
    if (!full)
    {

        file.open("menu.txt", ios::in); /* DISPLAY MENU TO CUSTOMER */
        if (file)
        {
            file.close();
            menu();

            ofstream filedorder; /* STORE ORDER FROM CUSTOMER INTO Dine.csv*/
            filedorder.open("Dine.csv", ios::app);

            ofstream filetorder; /* STORE ORDER FROM CUSTOMER INTO takeAway.csv*/
            filetorder.open("takeAway.csv", ios::app);

            cout << endl;
            SetConsoleTextAttribute(h, 7); /* DINE IN / TAKE AWAY */
            cout << "\t\t --------------------------------------------------------------------------------\n";
            cout << "\t\t <1> Dine in\n";
            cout << "\t\t <2> Take away\n";
            cout << "\n\t\t >> Dine in / Take away (1/2): ";
            cin >> cust_type;
            if (cust_type == 1)
            { /* DINE IN, THEN KEY IN TABLE NO. */
                SetConsoleTextAttribute(h, 15);
                cout << "\n\t\t================================================================================" << endl;
                cout << "\t\t\t\t\t\tPLACE YOUR ORDER" << endl;
                cout << "\t\t================================================================================" << endl;

            again:
                SetConsoleTextAttribute(h, 7);
                cout << "\n\t\t >> Please enter your table no.: ";
                cin >> table_no;

                if (table_no >= 1 && table_no <= 30)
                {
                    // do nothing
                }
                else
                {
                    SetConsoleTextAttribute(h, 4);
                    cout << "\n\t\t\t\t   Please enter a valid table no. (1 - 30)\n";
                    cout << "\t\t\t\t\t Please enter number input.\n";
                    goto again;
                }
            }
            else if (cust_type == 2)
            { /* TAKE AWAY, THEN KEY IN NAME AND PHONE NO. */
                SetConsoleTextAttribute(h, 15);
                cout << "\n\t\t================================================================================" << endl;
                cout << "\t\t\t\t\t\tPLACE YOUR ORDER" << endl;
                cout << "\t\t================================================================================" << endl;
                SetConsoleTextAttribute(h, 7);
                cout << "\n\t\t >> Please enter your name : ";
                cin >> cust_name;
                cout << "\t\t >> Please enter your phone number : ";
                cin >> cust_phone;
            }
            else
            {
                goto displaymenu; /* IF INPUT IS NOT 1/2, THEN GO BACK AGAIN */
            }

            do /* GET PRODUCT NO AND QUANTITY FROM CUSTOMER */
            {
            restart:
                SetConsoleTextAttribute(h, 7);
                cout << "\n\t\t >> Enter the product no.: ";
                cin >> order_arr[c];

                if (order_arr[c] >= 1 && order_arr[c] <= 15)
                { /* IF PRODUCT NO. IS VALID, THEN ASK FOR QUANTITY */
                quantity:
                    SetConsoleTextAttribute(h, 7);
                    cout << "\n\t\t >> Quantity in number : ";
                    cin >> quan[c];

                    if (quan[c] >= 1 && quan[c] <= 10)
                    {
                        c++;
                    }
                    else
                    { /* QUANTITY BELOW/EXCEED RANGE */
                        SetConsoleTextAttribute(h, 4);
                        cout << "\n\t\t\t\t   Sorry. Minimum order is 1. Maximum order is 10.\n";
                        goto quantity;
                    }
                }
                else
                { /* PRODUCT NO. NOT VALID */
                    SetConsoleTextAttribute(h, 4);
                    cout << "\n\t\t\t\t   Please enter a valid product no. (1 - 15)\n";
                    goto restart;
                }

                cout << "\n\t\t--------------------------------------------------------------------------------";
                cout << "\n\t\t >> Do you want to order another product [y/n] : ";
                cin >> addp;
                cout << "\t\t--------------------------------------------------------------------------------" << endl;

            } while ((addp == 'y' || addp == 'Y') && (c < 15));

            // queue
            fstream queueFile;
            queueFile.open("queue.txt", ios::out);
            bool full = false;
            if (queueFile)
            {
                queueNum++;
                if (counter != 0)
                {
                    newQueue.append(" ");
                }
                newQueue.append(to_string(queueNum));
                queueFile << newQueue; // inserting text

                queueFile.close();
            }

            system("cls");

            show_order(); /* CALL SHOW ORDER FUNCTION WHEN CUSTOMER KEY IN 'N' */
        }
    }
}

void Customer::add_order() /* FUNCTION FOR CUSTOMER TO ADD ORDER */
{
displaymenu:
    ofstream file;
    file.open("menu.txt", ios::in); /* DISPLAY MENU TO CUSTOMER */
    if (file)
    {
        file.close();
        menu();

        ofstream filedorder; /* STORE ORDER FROM CUSTOMER INTO Dine.csv*/
        filedorder.open("Dine.csv", ios::app);

        ofstream filetorder; /* STORE ORDER FROM CUSTOMER INTO takeAway.csv*/
        filetorder.open("takeAway.csv", ios::app);

        for (int x = 0; x < c; x++) /* STORE FIRST ORDER */
        {
            if (cust_type == 1)
            {
                filedorder << table_no << "," << order_arr[x] << "," << quan[x] << "," << status << endl; /* IF QUANTITY IS IN THE RANGE, THEN STORE DINE IN ORDER INTO Dine.csv*/
            }
            else if (cust_type == 2)
            {
                filetorder << cust_name << "," << cust_phone << "," << order_arr[x] << "," << quan[x] << "," << status << endl; /* IF QUANTITY IS IN THE RANGE, THEN STORE DINE IN ORDER INTO takeAway.csv*/
            }
        }

        cout << endl;

        do /* GET PRODUCT NO AND QUANTITY FROM CUSTOMER */
        {
        restart:
            SetConsoleTextAttribute(h, 7);
            cout << "\n\t\t >> Enter the product no.: ";
            cin >> order_arr[c];

            if (order_arr[c] >= 1 && order_arr[c] <= 15)
            {
            quantity:
                SetConsoleTextAttribute(h, 7);
                cout << "\n\t\t >> Quantity in number : ";
                cin >> quan[c];

                if (quan[c] >= 1 && quan[c] <= 10)
                {
                    if (cust_type == 1)
                    {
                        filedorder << table_no << "," << order_arr[c] << "," << quan[c] << "," << status << endl; /* IF QUANTITY IS IN THE RANGE, THEN STORE DINE IN ORDER INTO Dine.csv*/
                    }
                    else if (cust_type == 2)
                    {
                        filetorder << cust_name << "," << cust_phone << "," << order_arr[c] << "," << quan[c] << "," << status << endl; /* IF QUANTITY IS IN THE RANGE, THEN STORE DINE IN ORDER INTO takeAway.csv*/
                    }
                    c++; /* ORDER +1 */
                }
                else
                {
                    SetConsoleTextAttribute(h, 4);
                    cout << "\n\t\t\t\t   Sorry. Minimum order is 1. Maximum order is 10.\n";
                    goto quantity;
                }
            }
            else
            {
                SetConsoleTextAttribute(h, 4);
                cout << "\n\t\t\t\t   Please enter a valid product no. (1 - 15)\n";
                goto restart;
            }

            cout << "\n\t\t--------------------------------------------------------------------------------";
            cout << "\n\t\t >> Do you want to order another product [y/n] : ";
            cin >> addp;
            cout << "\t\t--------------------------------------------------------------------------------" << endl;

        } while ((addp == 'y' || addp == 'Y') && (c < 15));
        system("cls");

        show_order2();
    }
}

void Customer::cancel_order()
{
cancel:
    SetConsoleTextAttribute(h, 7);
    cout << "\n\t---------------------------------------------------------------------------------------------------\n";
    cout << "\t >> Which order do you want to remove? Please enter NO : ";
    cin >> deleteorder;

    int i, j, index = -1;
    for (i = 0; i < c; i++)
    {
        if (order_arr[i] == deleteorder)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        for (i = index; i < (c - 1); i++)
            // SHIFT THE ORDERS THAT ARE AFTER 'deleteorder' TO THE LEFT
            // SHIFT FROM INDEX +1 BY 1 POSITION TO THE LEFT
            order_arr[i] = order_arr[i + 1];
        c--;

        for (j = index; j < c; j++)
            quan[j] = quan[j + 1];

        for (i = 0; i < c; i++)
        {
            ofstream filedorder; /* STORE ORDER FROM CUSTOMER INTO Dine.csv*/
            filedorder.open("Dine.csv", ios::app);

            ofstream filetorder; /* STORE ORDER FROM CUSTOMER INTO takeAway.csv*/
            filetorder.open("takeAway.csv", ios::app);

            if (cust_type == 1)
            {
                filedorder << table_no << "," << order_arr[i] << "," << quan[i] << "," << status << "\n"; /* STORE DINE IN ORDER INTO Dine.csv*/
            }
            else if (cust_type == 2)
            {
                filetorder << cust_name << "," << cust_phone << "," << order_arr[i] << "," << quan[i] << "," << status << "\n"; /* STORE TAKE AWAY ORDER INTO takeAway.csv*/
            }
        }

        system("cls");
        SetConsoleTextAttribute(h, 8);
        cout << "\n\t\t\t\t\t Selected Order Has Been Removed\n";
        show_order3();
    }
    else
    {
        SetConsoleTextAttribute(h, 4);
        cout << "\n\t\t\t\t\t\t Order not found.";
        goto cancel;
    }
}

void Customer::show_order() /* FUCNTION TO SHOW CUSTOMER'S ORDER */
{
    SetConsoleTextAttribute(h, 8);
    cout << "\n\n\t\t\t\t\t      ...Generating Order...\n\n";
    loading();

    SetConsoleTextAttribute(h, 15);
    cout << "\n\n\n\t\t\t\t\t\t  Order Confirmed!" << endl;
    cout << "\n\t\t\t\t\t    This is your order summary: \n"
         << endl;
    cout << "\t===================================================================================================";
    cout << "\n\t|   No  | \t\t\t Name \t\t\t|  Quantity  |    Price   |     Amount    |" << endl;
    cout << "\t===================================================================================================";

    for (int x = 0; x < c; x++) /* DISPLAY THE ORDER AND AMOUNT */
    {
        file.open("menu.txt", ios::in);
        file >> pno >> name >> price;

        while (!file.eof())
        {
            if (pno == order_arr[x]) /* FIND PRODUCT NO. THAT MATCH WITH CUSTOMER INPUT */
            {
                amt = price * quan[x];
                cout << "\n\t| " << setw(4) << order_arr[x] << "  | " << setw(10) << name << "\t\t\t\t|    " << setw(3) << quan[x]
                     << "     |   " << setw(5) << price << "    |     " << setw(5) << amt << "     | " << endl;
                total += amt;
            }
            file >> pno >> name >> price;
        }
        file.close();
    }
    cout << "\t===================================================================================================" << endl;
    cout << "\n\t|\t\t\t\t\t\t\t\t\t TOTAL AMOUNT : RM " << total << "\t  |" << endl;
    cout << "\t===================================================================================================" << endl;
    getch();

    change_option();
}

void Customer::show_order2() /* FUCNTION TO SHOW CUSTOMER'S ORDER WITH ADD ORDER*/
{
    SetConsoleTextAttribute(h, 8);
    cout << "\n\n\t\t\t\t\t      ...Generating Order...\n\n";
    loading();

    SetConsoleTextAttribute(h, 15);
    cout << "\n\n\n\t\t\t\t\t\t  Order Confirmed!" << endl;
    cout << "\n\t\t\t\t\t    This is your order summary: \n"
         << endl;
    cout << "\t===================================================================================================";
    cout << "\n\t|   No  | \t\t\t Name \t\t\t|  Quantity  |    Price   |     Amount    |" << endl;
    cout << "\t===================================================================================================";

    for (int x = 0; x < c; x++) /* DISPLAY THE ORDER AND AMOUNT */
    {
        file.open("menu.txt", ios::in);
        file >> pno >> name >> price;
        while (!file.eof())
        {
            if (pno == order_arr[x]) /* FIND PRODUCT NO. THAT MATCH WITH CUSTOMER INPUT */
            {
                amt = price * quan[x];
                cout << "\n\t| " << setw(4) << order_arr[x] << "  | " << setw(10) << name << "\t\t\t\t|    " << setw(3) << quan[x]
                     << "     |   " << setw(5) << price << "    |     " << setw(5) << amt << "     | " << endl;
                addtotal += amt;
            }
            file >> pno >> name >> price;
        }
        file.close();
    }
    cout << "\t===================================================================================================" << endl;
    cout << "\n\t|\t\t\t\t\t\t\t\t\t TOTAL AMOUNT : RM " << addtotal << "\t  |" << endl;
    cout << "\t===================================================================================================" << endl;
    getch();

    SetConsoleTextAttribute(h, 6);
    cout << "\n\t\t\t\t      *******************************************";
    cout << "\n\t\t\t\t      |         Thank you for your order!       |";
    cout << "\n\t\t\t\t      |     We will prepare your order soon...  |";
    cout << "\n\t\t\t\t      *******************************************\n";
    SetConsoleTextAttribute(h, 7);

    countdown();
}

void Customer::show_order3() /* FUCNTION TO SHOW CUSTOMER'S ORDER WITH CANCEL ORDER*/
{
    SetConsoleTextAttribute(h, 8);
    cout << "\n\n\t\t\t\t\t      ...Generating Order...\n\n";
    loading();

    SetConsoleTextAttribute(h, 15);
    cout << "\n\n\n\t\t\t\t\t\t  Order Confirmed!" << endl;
    cout << "\n\t\t\t\t\t    This is your order summary: \n"
         << endl;
    cout << "\t===================================================================================================";
    cout << "\n\t|   No  | \t\t\t Name \t\t\t|  Quantity  |    Price   |     Amount    |" << endl;
    cout << "\t===================================================================================================";

    for (int i = 0; i < c; i++) /* DISPLAY THE ORDER AND AMOUNT */
    {
        file.open("menu.txt", ios::in);
        file >> pno >> name >> price;
        while (!file.eof())
        {
            if (pno == order_arr[i]) /* FIND PRODUCT NO. THAT MATCH WITH CUSTOMER INPUT */
            {
                amt = price * quan[i];
                cout << "\n\t| " << setw(4) << order_arr[i] << "  | " << setw(10) << name << "\t\t\t\t|    " << setw(3) << quan[i]
                     << "     |   " << setw(5) << price << "    |     " << setw(5) << amt << "     | " << endl;
                changetotal += amt;
            }
            file >> pno >> name >> price;
        }
        file.close();
    }
    cout << "\t===================================================================================================" << endl;
    cout << "\n\t|\t\t\t\t\t\t\t\t\t TOTAL AMOUNT : RM " << changetotal << "\t  |" << endl;
    cout << "\t===================================================================================================" << endl;
    getch();

    SetConsoleTextAttribute(h, 6);
    cout << "\n\t\t\t\t      *******************************************";
    cout << "\n\t\t\t\t      |         Thank you for your order!       |";
    cout << "\n\t\t\t\t      |     We will prepare your order soon...  |";
    cout << "\n\t\t\t\t      *******************************************\n";
    SetConsoleTextAttribute(h, 7);

    countdown();
}

// no payment
void Customer::change_option()
{
change:
    SetConsoleTextAttribute(h, 7);
    cout << "\n\t---------------------------------------------------------------------------------------------------";
    cout << "\n\t >> Do you want to change your order? [y/n] : ";
    cin >> cp;
    cout << "\t---------------------------------------------------------------------------------------------------" << endl;

    if (cp == 'y' || cp == 'Y')
    {
        SetConsoleTextAttribute(h, 7);
        cout << "\t 1. Add order\n";
        cout << "\t 2. Remove order\n\n";
        cout << "\t >> Please select an option: ";
        cin >> changeorder;

        switch (changeorder)
        {
        case 1:
            system("cls");
            add_order();
            break;
        case 2:
            cancel_order();
            break;
        default:
            SetConsoleTextAttribute(h, 4);
            cout << "\n\t\t\t\t\t   Invalid! Please select again.";
            goto change;
        }
    }
    else if (cp == 'n' || cp == 'N')
    {

        ofstream filedorder; /* STORE ORDER FROM CUSTOMER INTO Dine.csv*/
        filedorder.open("Dine.csv", ios::app);

        ofstream filetorder; /* STORE ORDER FROM CUSTOMER INTO takeAway.csv*/
        filetorder.open("takeAway.csv", ios::app);

        for (int x = 0; x < c; x++) /* STORE ORDER WITHOUT ANY CHANGES */
        {
            if (cust_type == 1)
            {
                filedorder << table_no << "," << order_arr[x] << "," << quan[x] << "," << status << endl; /* IF QUANTITY IS IN THE RANGE, THEN STORE DINE IN ORDER INTO Dine.csv*/
            }
            else if (cust_type == 2)
            {
                filetorder << cust_name << "," << cust_phone << "," << order_arr[x] << "," << quan[x] << "," << status  << endl; /* IF QUANTITY IS IN THE RANGE, THEN STORE DINE IN ORDER INTO takeAway.csv*/
            }
        }

        SetConsoleTextAttribute(h, 6);
        cout << "\n\t\t\t\t      *******************************************";
        cout << "\n\t\t\t\t      |         Thank you for your order!       |";
        cout << "\n\t\t\t\t      |     We will prepare your order soon...  |";
        cout << "\n\t\t\t\t      *******************************************\n";
        SetConsoleTextAttribute(h, 7);

        countdown();
    }
    else
    {
        SetConsoleTextAttribute(h, 4);
        cout << "\t\t\t\t\t\t Invalid input!";
        goto change;
    }
}

void Customer::full_queue()
{
    SetConsoleTextAttribute(h, 6);
    cout << "\n\t\t\t\t      *****************************************";
    cout << "\n\t\t\t\t      |         Sorry our queue is full!       |";
    cout << "\n\t\t\t\t      |         Please try again later        |";
    cout << "\n\t\t\t\t      *****************************************\n\n";
}
