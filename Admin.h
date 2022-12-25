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
#include "main.h"

#ifndef ADMIN_H
#define ADMIN_H
using namespace std;

class Admin
{
public:
	void adminAuthentication();
	int adminMenu();
	void adminCheck();
	void adminConfirm();
	int attempt(int times);
};

#endif