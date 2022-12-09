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

#include "Admin.h"
using namespace std;

void Admin::adminAuthentication()
{
	cin.ignore();
	int errorTime = 0;
	string adminUsername, adminPassword;

	do
	{
		cout << "Admin Authentication" << endl;
		cout << "Enter the Username: ";
		getline(cin, adminUsername);

		if (adminUsername == "Admin")
		{
			cout << "Enter the Password: ";
			getline(cin, adminPassword);

			if (adminPassword == "Admin")
			{
				cout << "Login Successful!" << endl;

				system("PAUSE");
				system("cls");
				adminMenu();
			}
			else
			{
				cout << "Password Incorrect!" << endl;
				errorTime++;
			}
		}
		else
		{
			cout << "Username does not exist!" << endl;
			errorTime++;
		}
	} while (errorTime < 3);

	if (errorTime < 3)
	{
		cout << "Attempted 3 times still failure, force to exit the system!" << endl
			 << endl;
	}
}

void Admin::adminMenu()
{
	int optionChoice;
	bool optionLoop = false;

	do
	{
		cout << "Admin Menu" << endl;
		cout << "1. Check Order" << endl;
		cout << "2. Confirm Order" << endl;
		cout << "Enter the Option: ";
		cin >> optionChoice;

		switch (optionChoice)
		{
		case 1:
			cout << endl;
			adminCheck();
			break;
		case 2:
			cout << endl;
			adminConfirm();
			break;
		default:
			cout << "Invalid Input! Only 1 or 2 is allowed!" << endl
				 << endl;
			break;
		}
	} while (!optionLoop);
}

void Admin::adminCheck()
{
	// Variables
	int i = 0, j = 0, z = 0;
	int commaIndex1;
	int commaIndex2;
	int commaIndex3;
	int optionChoice;
	string line;

	// Dine In
	string tempTableNo;
	string tableNo[15];
	string orderID[15];
	string orderQty[15];

	// Delivery
	string tempUserName;
	string foodID[15];
	string foodQty[15];
	string userName[15], userPhone[15];

	// Product
	int productID[15];
	float productPrice[15];
	string productName[15];

	// File Structure
	ifstream readMenu;
	ifstream readDineIn;
	ifstream readTakeAway;

	readMenu.open("menu.txt", ios::in);
	readDineIn.open("Dine.csv");
	readTakeAway.open("takeAway.csv");

	while (!readMenu.eof())
	{
		readMenu >> productID[z] >> productName[z] >> productPrice[z];
		z++;
	}
	readMenu.close();

	while (!readTakeAway.eof())
	{
		getline(readTakeAway, line);
		if (i > 1)
		{
			commaIndex1 = line.find(",");
			userName[i - 1] = line.substr(0, commaIndex1);

			commaIndex2 = line.substr(commaIndex1 + 1).find(",");
			userPhone[i - 1] = line.substr(commaIndex1 + 1, commaIndex2);

			commaIndex3 = line.substr(commaIndex1 + commaIndex2 + 2).find(",");
			foodID[i - 1] = line.substr(commaIndex1 + commaIndex2 + 2, commaIndex3);
			foodQty[i - 1] = line.substr(commaIndex1 + commaIndex2 + commaIndex3 + 3);
			// cout << "Username: " << userName[i - 1] << endl;
			// cout << "Phone Number: " << userPhone[i - 1] << endl;
			// cout << "Food ID: " << foodID[i - 1] << endl;
			// cout << "Food Qty: " << foodQty[i - 1] << endl;
			// cout << line << endl;
		}
		// readDineIn >> line;
		i++;
	}

	readTakeAway.close();
	while (!readDineIn.eof())
	{
		getline(readDineIn, line);
		if (j > 1)
		{
			commaIndex1 = line.find(",");
			tableNo[j - 1] = line.substr(0, commaIndex1);

			commaIndex2 = line.substr(commaIndex1 + 1).find(",");
			orderID[j - 1] = line.substr(commaIndex1 + 1, commaIndex2);

			orderQty[j - 1] = line.substr(commaIndex1 + commaIndex2 + 2);

			/*cout << "Table No: " << tableNo[j - 1] << endl;
			cout << "Order ID: " << orderID[j - 1] << endl;
			cout << "Order Quantity: " << orderQty[j - 1] << endl;
			cout << endl;*/
		}
		j++;
	}
	readDineIn.close();

	cout << "Check Order Option List" << endl;
	cout << "1. Dine In" << endl;
	cout << "2. Take Away" << endl;
	cout << "Enter the Option: ";
	cin >> optionChoice;

	switch (optionChoice)
	{
	case 1:
		cin.ignore();
		cout << endl;

		for (int a = 0; a < j - 1; a++)
		{
			if (tableNo[a] != "")
			{
				cout << "Table No: " << tableNo[a] << endl;
			}
		}
		cout << "Enter the Table No: ";
		getline(cin, tempTableNo);
		cout << endl;

		for (int a = 0; a < j - 1; a++)
		{
			if (tableNo[a] == tempTableNo)
			{
				cout << "Table No: " << tableNo[a] << endl;
				for (int p = 0; p < z; p++)
				{
					if (stoi(orderID[a]) == productID[p])
					{
						cout << "Food Name: " << productName[p] << endl;
					}
				}
				cout << "Quantity: " << orderQty[a] << endl;
				cout << endl;
			}
		}
		break;
	case 2:
		cin.ignore();
		cout << endl;

		for (int a = 0; a < i - 1; a++)
		{
			if (userName[a] != "")
			{
				cout << "User Name: " << userName[a] << endl;
			}
		}
		cout << "Enter the User Name: ";
		getline(cin, tempUserName);
		cout << endl;

		for (int a = 0; a < i - 1; a++)
		{
			if (userName[a] == tempUserName)
			{
				cout << "Username: " << userName[a] << endl;
				cout << "Phone Number: " << userPhone[a] << endl;
				for (int p = 0; p < z; p++)
				{
					if (stoi(foodID[a]) == productID[p])
					{
						cout << "Food Name: " << productName[p] << endl;
					}
				}
				cout << "Quantity: " << foodQty[a] << endl;
				cout << endl;
			}
		}
		break;
	default:
		cout << "Invalid Input! Only 1 and 2 is allowed!" << endl;
		break;
	}
}

void Admin::adminConfirm()
{
	// Variables
	int i = 0, j = 0, z = 0;
	int commaIndex1;
	int commaIndex2;
	int commaIndex3;
	int optionChoice;
	bool confirmDineIn = false, confirmTakeAway = false;
	string line;

	// Dine In
	string tempTableNo;
	string tableNo[15];
	string orderID[15];
	string orderQty[15];

	// Delivery
	string tempUserName;
	string foodID[15];
	string foodQty[15];
	string userName[15], userPhone[15];

	// Product
	int productID[15];
	float productPrice[15];
	string productName[15];

	// File Structure
	ifstream readMenu;
	ifstream readDineIn;
	ifstream readTakeAway;

	ofstream resetDineIn;
	ofstream outDineIn;
	ofstream resetTakeAway;
	ofstream outTakeAway;

	readMenu.open("menu.txt", ios::in);
	readDineIn.open("Dine.csv");
	readTakeAway.open("takeAway.csv");

	while (!readMenu.eof())
	{
		readMenu >> productID[z] >> productName[z] >> productPrice[z];
		z++;
	}
	readMenu.close();

	while (!readTakeAway.eof())
	{
		getline(readTakeAway, line);
		if (i > 1)
		{
			commaIndex1 = line.find(",");
			userName[i - 1] = line.substr(0, commaIndex1);

			commaIndex2 = line.substr(commaIndex1 + 1).find(",");
			userPhone[i - 1] = line.substr(commaIndex1 + 1, commaIndex2);

			commaIndex3 = line.substr(commaIndex1 + commaIndex2 + 2).find(",");
			foodID[i - 1] = line.substr(commaIndex1 + commaIndex2 + 2, commaIndex3);
			foodQty[i - 1] = line.substr(commaIndex1 + commaIndex2 + commaIndex3 + 3);
		}
		i++;
	}

	readTakeAway.close();
	while (!readDineIn.eof())
	{
		getline(readDineIn, line);
		if (j > 1)
		{
			commaIndex1 = line.find(",");
			tableNo[j - 1] = line.substr(0, commaIndex1);

			commaIndex2 = line.substr(commaIndex1 + 1).find(",");
			orderID[j - 1] = line.substr(commaIndex1 + 1, commaIndex2);

			orderQty[j - 1] = line.substr(commaIndex1 + commaIndex2 + 2);
		}
		j++;
	}
	readDineIn.close();

	outDineIn.open("confirmDine.csv", ios::out);
	outTakeAway.open("confirmtakeAway.csv", ios::out);
	cout << "Confirm Order Option List" << endl;
	cout << "1. Dine In" << endl;
	cout << "2. Take Away" << endl;
	cout << "Enter the Option: ";
	cin >> optionChoice;

	switch (optionChoice)
	{
	case 1:
		cin.ignore();
		cout << endl;

		for (int a = 0; a < j - 1; a++)
		{
			if (tableNo[a] != "")
			{
				cout << "Table No: " << tableNo[a] << endl;
			}
		}
		cout << "Enter the Table No: ";
		getline(cin, tempTableNo);
		cout << endl;

		for (int a = 0; a < j - 1; a++)
		{
			if (tableNo[a] == tempTableNo)
			{
				confirmDineIn = true;
				outDineIn << tableNo[a];
				for (int p = 0; p < z; p++)
				{
					if (stoi(orderID[a]) == productID[p])
					{
						outDineIn << "," << orderID[a];
					}
				}
				outDineIn << "," << orderQty[a] << endl;

				cout << "confirm order successfully!" << endl
					 << endl;
			}
		}

		if (confirmDineIn)
		{
			resetDineIn.open("Dine.csv", ios::out);
			for (int b = 0; b < j - 1; b++)
			{
				if (tableNo[b] != tempTableNo)
				{
					if (b == 0)
					{
						resetDineIn << "tableno"
									<< ","
									<< "order"
									<< ","
									<< "quantity" << endl;
					}
					resetDineIn << tableNo[b] << "," << orderID[b] << "," << orderQty[b] << endl;
				}
			}
			resetDineIn.close();
		}

		break;
	case 2:
		cin.ignore();
		cout << endl;

		for (int a = 0; a < i - 1; a++)
		{
			if (userName[a] != "")
			{
				cout << "User Name: " << userName[a] << endl;
			}
		}
		cout << "Enter the User Name: ";
		getline(cin, tempUserName);
		cout << endl;

		for (int a = 0; a < i - 1; a++)
		{
			if (userName[a] == tempUserName)
			{
				confirmTakeAway = true;
				outTakeAway << userName[a] << "," << userPhone[a];
				for (int p = 0; p < z; p++)
				{
					if (stoi(foodID[a]) == productID[p])
					{
						outTakeAway << "," << foodID[a];
					}
				}
				outTakeAway << "," << foodQty[a] << endl;
				cout << endl;
			}
		}

		if (confirmTakeAway)
		{
			resetTakeAway.open("takeAway.csv", ios::out);
			for (int b = 0; b < i - 1; b++)
			{
				if (userName[b] != tempUserName)
				{
					if (b == 0)
					{
						resetTakeAway << "name"
									  << ","
									  << "phone"
									  << ","
									  << "food"
									  << ","
									  << "quantity" << endl;
					}
					resetTakeAway << userName[b] << "," << userPhone[b] << "," << foodID[b] << "," << foodQty[b] << endl;
				}
			}
			resetTakeAway.close();
		}

		break;
	default:
		cout << "Invalid Input! Only 1 or 2 is allowed!" << endl
			 << endl;
		break;
	}

	outDineIn.close();
	outTakeAway.close();
}