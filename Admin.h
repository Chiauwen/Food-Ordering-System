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
#include <bits/stdc++.h>
#include "main.h"

#ifndef ADMIN_H
#define ADMIN_H
using namespace std;
HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);

class Admin
{

public:
	// functions
	void adminAuthentication();
	int adminMenu();

	// check order
	void adminCheck();
	void checkDine();

	// confirm order
	void adminConfirm();
	void checkConfirmed();

	// login authentication
	int attempt(int times);

	void a_menu();
	
};

class Node {
Node *food_head = NULL;
ofstream file;
    public:
        int pno;
        string name;
        float price;
        Node *food_next;

	void add_menu();
	void display_menu();
	void modify_menu();
	void delete_menu();
};



#endif