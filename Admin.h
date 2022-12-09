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

#ifndef ADMIN_H
#define ADMIN_H
using namespace std;

class Admin
{
public:
	void adminAuthentication();
	void adminMenu();
	void adminCheck();
	void adminConfirm();
};

#endif