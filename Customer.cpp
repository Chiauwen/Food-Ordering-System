#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <Windows.h>
#include <vector>

using namespace std;
fstream file, file1;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); /* FOR TEXT COLOUR */

class Menu
{ /* MENU CLASS */
protected:
    int pno;
    string name;
    float price;

public:
    void menu();
    void loading();
};

class Customer : public Menu
{ /* CUSTOMER CLASS, INHERITANCE FROM MENU CLASS */
private:
    int order_arr[15], quan[15], c = 0; /* MAX 15 ORDERS */
    float amt = 0, total = 0, addtotal = 0;
    char addp, cp;
    string cust_name, cust_phone;
    int cust_type, changeorder, cpno, cq;

public:
    int table_no;
    string table;
    void order();
    void show_order();
    void show_order2();
    void add_order();
    void change_option();
    int change_order();  /* HAVENT DONE */
    void cancel_order(); /* HAVENT DONE */
};

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

void Customer::order() /* FUNCTION TO PLACE ORDER FROM CUSTOMER */
{
displaymenu:

    file.open("menu.txt", ios::in); /* DISPLAY MENU TO CUSTOMER */
    if (file)
    {
        file.close();
        menu();

        ofstream dineFile; /* STORE ORDER FROM CUSTOMER INTO dineIn.txt*/
        dineFile.open(table, ios::app);

        ofstream awayFile; /* STORE ORDER FROM CUSTOMER INTO takeAway.txt*/
        awayFile.open("takeAway.txt", ios::app);

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
                switch (table_no)
                {
                case 1:
                    table = "1.txt";
                    break;
                case 2:
                    table = "2.txt";
                    break;
                }
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
                    ofstream dineFile; /* STORE ORDER FROM CUSTOMER INTO dineIn.csv*/
                    dineFile.open(table, ios::app);
                    if (cust_type == 1)
                    {
                        dineFile << table_no << " " << order_arr[c] << " " << quan[c] << endl; /* IF QUANTITY IS IN THE RANGE, THEN STORE DINE IN ORDER INTO dineIn.csv*/
                    }
                    else if (cust_type == 2)
                    {
                        awayFile << cust_name << "," << cust_phone << "," << order_arr[c] << "," << quan[c] << endl; /* IF QUANTITY IS IN THE RANGE, THEN STORE DINE IN ORDER INTO takeAway.csv*/
                    }
                    c++; /* ORDER +1 */
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
        system("cls");

        show_order(); /* CALL SHOW ORDER FUNCTION WHEN CUSTOMER KEY IN 'N' */
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

        ofstream dineFile; /* STORE ORDER FROM CUSTOMER INTO dineIn.csv*/
        dineFile.open(table, ios::app);

        ofstream awayFile; /* STORE ORDER FROM CUSTOMER INTO takeAway.csv*/
        awayFile.open("takeAway.txt", ios::app);

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
                    ofstream dineFile; /* STORE ORDER FROM CUSTOMER INTO dineIn.csv*/
                    dineFile.open(table, ios::app);
                    if (cust_type == 1)
                    {
                        dineFile << table_no << " " << order_arr[c] << " " << quan[c]; /* IF QUANTITY IS IN THE RANGE, THEN STORE DINE IN ORDER INTO dineIn.csv*/
                    }
                    else if (cust_type == 2)
                    {
                        awayFile << cust_name << " " << cust_phone << " " << order_arr[c] << " " << quan[c]; /* IF QUANTITY IS IN THE RANGE, THEN STORE DINE IN ORDER INTO takeAway.csv*/
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

/////////////////////////////////////////////////////////////////////////////////

int Customer::change_order() /* FUCNTION FOR CUSTOMER TO CHANGE ORDER'S QUANTITY */
{
    string search, line;
    int cancel;

    system("cls");

    cout << "TABLE NO. : " << table_no << endl;
    cout << "1. Cancel certain order" << endl;
    cout << "2. Cancel all order" << endl;
    cout << "Please select 1 or 2: ";

    cin >> cancel;

    // cancel certain order
    if (cancel == 1)
    {
        if (cust_type == 1)
        {
            cout << "Food: ";
            cin >> cancel;

            fstream read_file;

            read_file.open(table);

            if (read_file.fail())
            {
                cout << "Error opening file." << endl;
                return 1;
            }

            vector<string> lines;
            string line;

            while (getline(read_file, line))
                lines.push_back(line);

            read_file.close();

            if (cancel > lines.size())
            {
                cout << "Line " << cancel;
                cout << " not in file." << endl;

                cout << "File has " << lines.size();
                cout << " lines." << endl;

                return 1;
            }

            ofstream write_file;

            write_file.open(table);

            if (write_file.fail())
            {
                cout << "Error opening file." << endl;
                return 1;
            }

            cancel--;

            for (int i = 0; i < lines.size(); i++)
                if (i != cancel)
                    write_file << lines[i] << endl;

            write_file.close();
        }
        else
        {
            cout << "Food: ";
            cin >> cancel;

            fstream read_file;

            read_file.open("takeAway.txt");

            if (read_file.fail())
            {
                cout << "Error opening file." << endl;
                return 1;
            }

            vector<string> lines;
            string line;

            while (getline(read_file, line))
                lines.push_back(line);

            read_file.close();

            if (cancel > lines.size())
            {
                cout << "Line " << cancel;
                cout << " not in file." << endl;

                cout << "File has " << lines.size();
                cout << " lines." << endl;

                return 1;
            }

            ofstream write_file;

            write_file.open(table);

            if (write_file.fail())
            {
                cout << "Error opening file." << endl;
                return 1;
            }

            cancel--;

            for (int i = 0; i < lines.size(); i++)
                if (i != cancel)
                    write_file << lines[i] << endl;

            write_file.close();
        }
    }
    // cancel all order
    else if (cancel == 2)
    {
        if (cust_type == 1)
        {
            ofstream dine;
            dine.open(table);

            cout << "Are you sure want to cancel all order? (y/n)" << endl;
            cin >> cancel;

            if(cancel=='y'){
                dine << "";
            }
            
            dine.close();
        }
        else
        { //havent finish cancel all order for take away
            // ifstream take, newtake;
            // take.open("takeAway.txt", ios::app);
            // newtake.open("newtake.txt", ios::app);

            // cin.ignore();

            // cout << "Are you sure want to cancel all order?" << endl;
            // cin >> cancel;

            // while (getline(name, line))
            // {
            //     if (line != name)
            //     {
            //         newtake << line << endl;
            //     }
            // }
        }
    }

    show_order2();
}

////////////////////////////////////////////////////////////////////////////////

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

void Customer::show_order2() /* FUCNTION TO SHOW CUSTOMER'S ORDER */
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

    change_option();
}

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
        cout << "\t 2. Change order quantity\n";
        cout << "\t 3. Remove an order\n\n";
        cout << "\t Please select an option: ";
        cin >> changeorder;

        switch (changeorder)
        {
        case 1:
            system("cls");
            add_order();
            break;
        case 2:
            system("cls");
            change_order();
            break;
        case 3:
            // cancel_order();
            break;
        default:
            SetConsoleTextAttribute(h, 4);
            cout << "\n\t\t\t\t\t   Invalid! Please select again.";
            goto change;
        }
    }
    else if (cp == 'n' || cp == 'N')
    {
        SetConsoleTextAttribute(h, 6);
        cout << "\n\t\t\t\t      *******************************************";
        cout << "\n\t\t\t\t      |         Thank you for your order!       |";
        cout << "\n\t\t\t\t      |     We will prepare your order soon...  |";
        cout << "\n\t\t\t\t      *******************************************\n";
        SetConsoleTextAttribute(h, 7);
    }
    else
    {
        SetConsoleTextAttribute(h, 4);
        cout << "\t\t\t\t\t\t Invalid input!";
        goto change;
    }
}

void user_optional(string opt) /* FUNCTION FOR USER AND ADMIN ON MAIN PAGE */
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); /* FOR TEXT COLOUR */
    Customer c;                                 /* CLASS OBJECT */
    // Admin a;

    if (opt == "1")
    {
        system("CLS");
        c.order();
    }

    /*//////////ADMIN LOGIN FUCTION HERE!!!//////////
    else if(opt == "2")
    {
        system("CLS");
        a.login();     <<<CHANGE THE FUNCTION NAME///
    }
    */
    ///////////////////////////////////////////////

    else
    {
        SetConsoleTextAttribute(h, 4);
        cout << "\n\t\t\t\t\t\tInvalid input. Please try again!\n";
        SetConsoleTextAttribute(h, 7);
        system("pause");
    }
}

int main()
{ /* MAIN PAGE */
    string user_opt;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    do
    {

        system("cls");

        // MAIN PAGE INTERFACE
        SetConsoleTextAttribute(h, 6);
        cout << "\n\t\t\t\t   ......................................................";
        cout << "\n\t\t\t\t   |\t\t\t\t\t\t\t|";
        cout << "\n\t\t\t\t   |\t\t\t   Foodie\t\t\t|";
        cout << "\n\t\t\t\t   |\t\t\t\t\t\t\t|";
        cout << "\n\t\t\t\t   ......................................................\n";
        SetConsoleTextAttribute(h, 14);
        cout << "\n\t\t\t\t\t  Welcome! It is our pleasure to serve you.";

        SetConsoleTextAttribute(h, 6);
        cout << "\n\n\t\t\t\t   ------------------------------------------------------\n";
        SetConsoleTextAttribute(h, 7);
        cout << "\n\t\t\t\t\t\t\t  Customer \t\t\t\n"
             << endl;
        SetConsoleTextAttribute(h, 10);
        cout << "\t\t\t\t\t\t       <1> Take Order \t\t\t" << endl;
        SetConsoleTextAttribute(h, 6);
        cout << "\n\t\t\t\t   ------------------------------------------------------";

        SetConsoleTextAttribute(h, 7);
        cout << "\n\n\t\t\t\t\t\t\t   Admin\n"
             << endl;
        SetConsoleTextAttribute(h, 9);
        cout << "\t\t\t\t\t\t\t <2> Login" << endl;

        SetConsoleTextAttribute(h, 6);
        cout << "\n\t\t\t\t   ------------------------------------------------------\n";

        SetConsoleTextAttribute(h, 7);
        cout << "\n\n\t\t\t\t    >> Please select an option (1/2) : ";

        // GO TO THE NEXT PAGE
        cin >> user_opt;
        user_optional(user_opt);
    } while (user_opt != "1" && user_opt != "2");

    return 0;
}
