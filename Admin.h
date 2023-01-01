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
};

class Food_Detail
{
public:
	string food_name;
	string food_desc;
	string food_price;
	Food_Detail *food_next;

	Food_Detail()
	{
		food_name;
		food_desc;
		food_price;
		food_next = NULL;
	}

	Food_Detail(string food_name, string food_desc, string food_price)
	{
		this->food_name = food_name;
		this->food_desc = food_desc;
		this->food_price = food_price;
		this->food_next = NULL;
	}
};

class Function
{
public:
	Food_Detail *food_Head;
	Function()
	{
		food_Head = NULL;
	};
	void print_food();
	void insert_food(Food_Detail food);
	void delete_food(string food_name);
	void update();
	void modify_food(Function function);
};

#endif