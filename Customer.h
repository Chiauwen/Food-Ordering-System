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

#ifndef CUSTOMER_H
#define CUSTOMER_H

using namespace std;

fstream file, filedorder, filetorder;
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
    int order_arr[15], quan[15], c = 0; /* MAX 15 ORDERS IN 1 ORDER */
    float amt = 0, total = 0, addtotal = 0, changetotal = 0;
    char addp, cp;
    string cust_name, cust_phone;
    int cust_type, table_no, changeorder, deleteorder;

public:
    void order();
    void show_order();
    void show_order2();
    void show_order3();
    void add_order();
    void change_option();
    void cancel_order(); 
    void full_queue();
    void countdown();
};

#endif
