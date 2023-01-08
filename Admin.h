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

	// sort
	int sort(string sortArr[], int j);
	void printSortDine(string sortArr[], int j);
	void printSortTake(string sortArr[], int j);
	
};


#endif