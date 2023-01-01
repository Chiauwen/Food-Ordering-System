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
#include "main.h"

using namespace std;

// RECURSION
int Admin::attempt(int times)
{
	string adminUsername, adminPassword;

	if (times < 2)
	{
		system("CLS");

		SetConsoleTextAttribute(a, 3);
		cout << "\n\t\t\t\t --------------------------------------------- \n";
		SetConsoleTextAttribute(a, 15);
		cout << "\t\t\t\t\t\t ADMIN LOGIN";
		SetConsoleTextAttribute(a, 3);
		cout << "\n\t\t\t\t --------------------------------------------- \n\n\n";

		SetConsoleTextAttribute(a, 12);
		cout << "\t\t\t Login Unsuccessful, try again! \n\n"
			 << endl;

		SetConsoleTextAttribute(a, 15);
		cout << "\t\t\t Enter the Username: ";
		getline(cin, adminUsername);

		cout << "\t\t\t Enter the Password: ";
		getline(cin, adminPassword);

		if (adminUsername == "Admin" && adminPassword == "Admin")
		{
			system("CLS");
			adminMenu();
		}

		return times + attempt(times + 1);
	}

	else
	{
		system("CLS");

		SetConsoleTextAttribute(a, 12);
		cout << "\n\n\t\t\t Attempted 3 times still failure, force to exit the system!\n\n"
			 << endl
			 << endl;

		SetConsoleTextAttribute(a, 15);
		return 0;
	}
}

void Admin::adminAuthentication()
{
	cin.ignore();
	string adminUsername, adminPassword;

	SetConsoleTextAttribute(a, 3);
	cout << "\n\t\t\t\t --------------------------------------------- \n";
	SetConsoleTextAttribute(a, 15);
	cout << "\t\t\t\t\t\t ADMIN LOGIN";
	SetConsoleTextAttribute(a, 3);
	cout << "\n\t\t\t\t --------------------------------------------- \n\n\n";

	SetConsoleTextAttribute(a, 15);
	cout << "\t\t\t Enter the Username: ";
	getline(cin, adminUsername);

	cout << "\t\t\t Enter the Password: ";
	getline(cin, adminPassword);

	if (adminUsername == "Admin" && adminPassword == "Admin")
	{
		system("CLS");
		adminMenu(); // if the username and password correct then go menu
	}
	else
	{
		attempt(0); // if false go to attempt()
	}
}

int Admin::adminMenu()
{
	int optionChoice;
	bool optionLoop = false;

	do
	{
		system("CLS");
		cout << "\n\n\t\t\t\t\t\t ADMIN MENU" << endl;
		SetConsoleTextAttribute(a, 3);
		cout << "\n\t\t\t\t ------------------------------------------- \n\n\n";
		SetConsoleTextAttribute(a, 15);

		cout << "\t\t\t\t 1. Check All Order" << endl;
		cout << "\n\t\t\t\t 2. Confirm Order" << endl;
		cout << "\n\t\t\t\t 3. Check All Confirmed Order" << endl;
		cout << "\n\t\t\t\t 4. Modify Menu" << endl;
		cout << "\n\t\t\t\t 5. Return to Main Menu" << endl;
		cout << "\n\n \t\t Enter the Option: ";
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
		case 3:
			cout << endl;
			checkConfirmed();
			break;
		case 4:
			cout << endl;
			modify_food();
			break;
		case 5:
			cout << endl;
			return mainPage();
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
	system("CLS");

	// Variables
	int i = 0, j = 0, z = 0;
	int commaIndex1;
	int commaIndex2;
	int commaIndex3;
	int commaIndex4;
	int optionChoice;
	char ans;
	string line;

	// Order Status
	string status[15];

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

	/*    Customer   */
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

			commaIndex4 = line.substr(commaIndex1 + commaIndex2 + commaIndex3 + 3).find(",");
			foodQty[i - 1] = line.substr(commaIndex1 + commaIndex2 + commaIndex3 + 3, commaIndex4);
			status[i - 1] = line.substr(commaIndex1 + commaIndex2 + commaIndex3 + commaIndex4 + 4);
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

			commaIndex3 = line.substr(commaIndex1 + commaIndex2 + 2).find(",");
			orderQty[j - 1] = line.substr(commaIndex1 + commaIndex2 + 2, commaIndex3);
			status[j - 1] = line.substr(commaIndex1 + commaIndex2 + commaIndex3 + 3);
		}
		j++;
	}
	readDineIn.close();

	cout << "\n\n\t\t\t\t\t\t CHECK ORDER OPTION LIST" << endl;
	SetConsoleTextAttribute(a, 3);
	cout << "\n\t\t\t\t ---------------------------------------------------- \n\n\n";
	SetConsoleTextAttribute(a, 15);

	cout << "\t\t\t\t 1. Dine In" << endl;
	cout << "\n\t\t\t\t 2. Take Away" << endl;

	SetConsoleTextAttribute(a, 14);
	cout << "\n\n\t\t\tEnter the Option: ";
	SetConsoleTextAttribute(a, 15);
	cin >> optionChoice;

	system("CLS");

	switch (optionChoice)
	{
	case 1:
		do
		{
			// Find data
			bool findDine = false;

			system("CLS");
			cin.ignore();
			cout << endl;

			cout << "\n\n\t\t\t\t\t\t TABLE NO" << endl;
			SetConsoleTextAttribute(a, 3);
			cout << "\n\t\t\t\t\t -------------------------- \n\n\n";
			SetConsoleTextAttribute(a, 15);

			for (int b = 0; b < j - 1; b++)
			{
				int c;
				for (c = 0; c < b; c++)
					if (tableNo[b] == tableNo[c])
						break;
				if (b == c)
				{
					if (tableNo[b] != "")
					{
						SetConsoleTextAttribute(a, 14);
						cout << "\t\t\t\t\t Table Number: ";
						SetConsoleTextAttribute(a, 15);
						cout << tableNo[b] << endl
							 << endl;
					}
				}
			}

			cout << "\n\n\t\t\t\tEnter table number: ";
			getline(cin, tempTableNo);
			cout << endl;

			system("CLS");

			cout << "\n\n\t\t\t\t\t\t CHECKING ORDER" << endl;
			SetConsoleTextAttribute(a, 3);
			cout << "\n\t\t\t\t ---------------------------------------------------- \n\n\n";
			SetConsoleTextAttribute(a, 15);

			for (int b = 0; b < j; b++)
			{
				if (tableNo[b] == tempTableNo)
				{
					findDine = true;
					for (int p = 0; p < z; p++)
					{
						if (stoi(orderID[b]) == productID[p])
						{
							cout << "\t\t\t\t Food: " << productName[p] << endl;
						}
					}
					cout << "\t\t\t\t Quantity: " << orderQty[b] << endl;
					cout << "\t\t\t\t Order Status: " << status[b] << endl;
					cout << endl;
				}
			}

			if (!findDine)
			{
				SetConsoleTextAttribute(a, 12);
				cout << "\n\n\t\t\t\t\t DATA NOT FOUND, TRY AGAIN! \n\n";
				SetConsoleTextAttribute(a, 15);
			}

			cout << "\n\n\t\t\t\t Return to Admin Menu(y/n): ";
			cin >> ans;

			tolower(ans);

		} while (ans != 'y');

		break;
	case 2:
		do
		{
			bool findTake = false;
			cin.ignore();
			cout << endl;

			cout << "\n\n\t\t\t\t\t\t CUSTOMER NAME" << endl;
			SetConsoleTextAttribute(a, 3);
			cout << "\n\t\t\t\t\t ----------------------------------- \n\n\n";
			SetConsoleTextAttribute(a, 15);

			for (int b = 0; b < i - 2; b++)
			{
				int c;
				for (c = 0; c < b; c++)
					if (userName[b] == userName[c])
						break;
				if (b == c)
				{
					if (userName[b] != "")
					{
						SetConsoleTextAttribute(a, 14);
						cout << "\t\t\t\t\t Customer: ";
						SetConsoleTextAttribute(a, 15);
						cout << userName[b] << endl
							 << endl;
					}
				}
			}

			cout << "\t\t\tEnter Customer Name: ";
			getline(cin, tempUserName);
			cout << endl;

			system("CLS");

			cout << "\n\n\t\t\t\t\t\t CHECKING ORDER" << endl;
			SetConsoleTextAttribute(a, 3);
			cout << "\n\t\t\t\t ---------------------------------------------------- \n\n\n";
			SetConsoleTextAttribute(a, 15);

			for (int b = 0; b < i - 1; b++)
			{
				if (userName[b] == tempUserName)
				{
					findTake = true;
					cout << "\t\t\t\t Phone Number: " << userPhone[b] << endl;
					for (int p = 0; p < z; p++)
					{
						if (stoi(foodID[b]) == productID[p])
						{
							cout << "\t\t\t\t Food: " << productName[p] << endl;
						}
					}
					cout << "\t\t\t\t Quantity: " << foodQty[b] << endl;
					cout << "\t\t\t\t Order Status: " << status[b] << endl;
					cout << endl;
				}
			}

			if (!findTake)
			{
				SetConsoleTextAttribute(a, 12);
				cout << "\n\n\t\t\t\t\t DATA NOT FOUND, TRY AGAIN! \n\n";
				SetConsoleTextAttribute(a, 15);
			}

			cout << "\n\n\t\t\t\t Return to Admin Menu: ";
			cin >> ans;

			tolower(ans);
		} while (ans != 'y');

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
	int commaIndex4;
	int optionChoice;
	bool confirmDineIn = false, confirmTakeAway = false;
	string line;

	// return main menu
	char ans;

	// Order Status
	string status[15];

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
			// foodQty[i - 1] = line.substr(commaIndex1 + commaIndex2 + commaIndex3 + 3);

			commaIndex4 = line.substr(commaIndex1 + commaIndex2 + commaIndex3 + 3).find(",");
			foodQty[i - 1] = line.substr(commaIndex1 + commaIndex2 + commaIndex3 + 3, commaIndex4);
			status[i - 1] = line.substr(commaIndex1 + commaIndex2 + commaIndex3 + commaIndex4 + 4);
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

			commaIndex3 = line.substr(commaIndex1 + commaIndex2 + 2).find(",");
			orderQty[j - 1] = line.substr(commaIndex1 + commaIndex2 + 2, commaIndex3);
			status[i - 1] = line.substr(commaIndex1 + commaIndex2 + commaIndex3 + 3);
		}
		j++;
	}
	readDineIn.close();

	outDineIn.open("confirmDine.csv", ios::app);
	outTakeAway.open("confirmtakeAway.csv", ios::app);

	system("CLS");

	cout << "\n\n\t\t\t\t\t CONFIRM ORDER OPTION LIST" << endl;
	SetConsoleTextAttribute(a, 3);
	cout << "\n\t\t\t\t ---------------------------------------------------- \n\n\n";
	SetConsoleTextAttribute(a, 15);

	cout << "\t\t\t\t 1. Dine In" << endl;
	cout << "\n\t\t\t\t 2. Take Away" << endl;

	SetConsoleTextAttribute(a, 14);
	cout << "\n\n\t\t\tEnter the Option: ";
	SetConsoleTextAttribute(a, 15);
	cin >> optionChoice;

	switch (optionChoice)
	{
	case 1:
		do
		{
			// find data
			bool findConfirmDine = false;

			system("CLS");

			cin.ignore();
			cout << endl;

			cout << "\n\n\t\t\t\t\t\t TABLE NO" << endl;
			SetConsoleTextAttribute(a, 3);
			cout << "\n\t\t\t\t\t -------------------------- \n\n\n";
			SetConsoleTextAttribute(a, 15);

			for (int b = 0; b < j - 1; b++)
			{
				int c;
				for (c = 0; c < b; c++)
					if (tableNo[b] == tableNo[c])
						break;
				if (b == c)
				{
					if (tableNo[b] != "")
					{
						SetConsoleTextAttribute(a, 14);
						cout << "\t\t\t\t\t Table Number: ";
						SetConsoleTextAttribute(a, 15);
						cout << tableNo[b] << endl
							 << endl;
					}
				}
			}

			cout << "\n\n\t\t\t\tEnter table number: ";
			getline(cin, tempTableNo);
			cout << endl;

			for (int b = 0; b < j - 1; b++)
			{
				if (tableNo[b] == tempTableNo)
				{
					findConfirmDine = true;
					confirmDineIn = true;

					outDineIn << tableNo[b];

					for (int p = 0; p < z; p++)
					{
						if (stoi(orderID[b]) == productID[p])
						{
							outDineIn << "," << orderID[b];
						}

						status[b] = "";
					}

					outDineIn << "," << orderQty[b] << endl;

					SetConsoleTextAttribute(a, 6);
					cout << "\n \t\t\t\t -------------------------------------------------";
					cout << "\n\n \t\t\t\t\t ORDER CONFIRMED SUCCESSFULLY!" << endl
						 << endl;
					SetConsoleTextAttribute(a, 15);

					// queue
					fstream queueFile;
					queueFile.open("queue.txt", ios::in);
					int queueNum;
					string newQueue;
					queueFile >> queueNum;
					if (queueFile)
					{
						while (!queueFile.eof()) /* IF NOT AT END OF FILE, THEN CONTINUE TO READ DATA FROM FILE */
						{
							queueFile >> queueNum;
							newQueue.append(" ");
							newQueue.append(to_string(queueNum));
						}
						queueFile.close();
					}

					fstream queueFile2;
					queueFile2.open("queue.txt", ios::out);
					if (queueFile2)
					{
						queueFile2 << newQueue;
						queueFile2.close();
					}
				}
			}

			if (findConfirmDine = true)
			{
				if (confirmDineIn)
				{
					resetDineIn.open("Dine.csv", ios::out);
					for (int b = 0; b < j; b++)
					{
						if (tableNo[b] != tempTableNo)
						{
							if (b == 0)
							{
								resetDineIn << "tableno"
											<< ","
											<< "order"
											<< ","
											<< "quantity"
											<< ","
											<< "status"
											<< endl;
							}
							resetDineIn << tableNo[b] << "," << orderID[b] << "," << orderQty[b] << "," << status[b] << endl;
						}
					}
					for (int b = 0; b < j - 1; b++)
					{
						if (tableNo[b] == tempTableNo)
						{
							status[b] = "CONFIRMED";
							resetDineIn << tableNo[b] << "," << orderID[b] << "," << orderQty[b] << "," << status[b] << endl;
						}
					}
					resetDineIn.close();
				}
				else
				{
					SetConsoleTextAttribute(a, 12);
					cout << "\n\n\t\t\t\t\t DATA NOT FOUND, TRY AGAIN! \n\n";
					SetConsoleTextAttribute(a, 15);
				}

				cout << "\n\n\t\t\t\t Return to Admin Menu: ";
				cin >> ans;

				tolower(ans);
			}
		} while (ans != 'y');
		break;

	case 2:
		do
		{
			// find data
			bool findConfirmTake = false;
			system("CLS");

			cin.ignore();
			cout << endl;

			cout << "\n\n\t\t\t\t\t\t CUSTOMER NAME" << endl;
			SetConsoleTextAttribute(a, 3);
			cout << "\n\t\t\t\t\t ----------------------------------- \n\n\n";
			SetConsoleTextAttribute(a, 15);

			for (int b = 0; b < i - 2; b++)
			{
				int c;
				for (c = 0; c < b; c++)
					if (userName[b] == userName[c])
						break;
				if (b == c)
				{
					if (userName[b] != "")
					{
						SetConsoleTextAttribute(a, 14);
						cout << "\t\t\t\t\t Customer: ";
						SetConsoleTextAttribute(a, 15);
						cout << userName[b] << endl
							 << endl;
					}
				}
			}

			cout << "\t\t\tEnter Customer Name: ";
			getline(cin, tempUserName);
			cout << endl;

			system("CLS");

			for (int b = 0; b < i - 1; b++)
			{
				if (userName[b] == tempUserName)
				{
					confirmTakeAway = true;
					outTakeAway << userName[b] << "," << userPhone[b];
					for (int p = 0; p < z; p++)
					{
						if (stoi(foodID[b]) == productID[p])
						{
							outTakeAway << "," << foodID[b];
						}

						status[b] = "";
					}

					outTakeAway << "," << foodQty[b] << endl;

					SetConsoleTextAttribute(a, 6);
					cout << "\n \t\t\t\t -------------------------------------------------";
					cout << "\n\n \t\t\t\t ORDER CONFIRMED SUCCESSFULLY!" << endl
						 << endl;
					SetConsoleTextAttribute(a, 15);

					cout << endl;

					// queue
					fstream queueFile3;

					queueFile3.open("queue.txt", ios::in);

					int queueNum;
					string newQueue;

					queueFile3 >> queueNum;
					if (queueFile3)
					{
						while (!queueFile3.eof()) /* IF NOT AT END OF FILE, THEN CONTINUE TO READ DATA FROM FILE */
						{
							queueFile3 >> queueNum;
							newQueue.append(" ");
							newQueue.append(to_string(queueNum));
						}
						queueFile3.close();
					}

					fstream queueFile4;
					queueFile4.open("queue.txt", ios::out);
					if (queueFile4)
					{
						queueFile4 << newQueue;
						queueFile4.close();
					}
				}
			}

			if (findConfirmTake = true)
			{
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
											  << "quantity"
											  << ","
											  << "status"
											  << endl;
							}
							status[b] = "PENDING";
							resetTakeAway << userName[b] << "," << userPhone[b] << "," << foodID[b] << "," << foodQty[b] << "," << status[b] << endl;
						}
						if (userName[b] == tempUserName)
						{
							if (b == 0)
							{
								resetTakeAway << "name"
											  << ","
											  << "phone"
											  << ","
											  << "food"
											  << ","
											  << "quantity"
											  << ","
											  << "status"
											  << endl;
							}
							status[b] = "CONFRIMED";
							resetTakeAway << userName[b] << "," << userPhone[b] << "," << foodID[b] << "," << foodQty[b] << "," << status[b] << endl;
						}
					}
					resetTakeAway.close();
				}
				else
				{
					SetConsoleTextAttribute(a, 12);
					cout << "\n\n\t\t\t\t\t DATA NOT FOUND, TRY AGAIN! \n\n";
					SetConsoleTextAttribute(a, 15);
				}
				cout << "\n\n\t\t\t\t Return to Admin Menu: ";
				cin >> ans;

				tolower(ans);
			}

		} while (ans != 'y');

		break;
	default:
		system("CLS");
		cout << "Invalid Input! Only 1 or 2 is allowed!" << endl
			 << endl;
		break;
	}

	outDineIn.close();
	outTakeAway.close();
}

void Admin::checkConfirmed()
{
	system("CLS");

	// Variables
	int i = 0, j = 0, z = 0;
	int commaIndex1;
	int commaIndex2;
	int commaIndex3;
	int commaIndex4;
	int optionChoice;
	char ans;
	string line;

	// Order Status
	string status[15];

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

	// Find data
	bool found = false;

	// File Structure
	ifstream readMenu;
	ifstream readDineIn;
	ifstream readTakeAway;

	readMenu.open("menu.txt", ios::in);
	readDineIn.open("confirmDine.csv", ios::in);
	readTakeAway.open("confirmtakeAway.csv", ios::in);

	while (!readMenu.eof())
	{
		readMenu >> productID[z] >> productName[z] >> productPrice[z];
		z++;
	}
	readMenu.close();

	/*    Customer   */
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

			commaIndex4 = line.substr(commaIndex1 + commaIndex2 + commaIndex3 + 3).find(",");
			foodQty[i - 1] = line.substr(commaIndex1 + commaIndex2 + commaIndex3 + 3, commaIndex4);
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

			commaIndex3 = line.substr(commaIndex1 + commaIndex2 + 2).find(",");
			orderQty[j - 1] = line.substr(commaIndex1 + commaIndex2 + 2, commaIndex3);
		}
		j++;
	}
	readDineIn.close();

	cout << "\n\n\t\t\t\t\t\t CHECK CONFIRMED ORDER" << endl;
	SetConsoleTextAttribute(a, 3);
	cout << "\n\t\t\t\t ---------------------------------------------------- \n\n\n";
	SetConsoleTextAttribute(a, 15);

	cout << "\t\t\t\t 1. Dine In" << endl;
	cout << "\n\t\t\t\t 2. Take Away" << endl;

	SetConsoleTextAttribute(a, 14);
	cout << "\n\n\t\t\tEnter the Option: ";
	SetConsoleTextAttribute(a, 15);
	cin >> optionChoice;

	system("CLS");

	switch (optionChoice)
	{
	case 1:
		do
		{
			system("CLS");
			cin.ignore();
			cout << endl;

			cout << "\n\n\t\t\t\t\t\t TABLE NO" << endl;
			SetConsoleTextAttribute(a, 3);
			cout << "\n\t\t\t\t\t -------------------------- \n\n\n";
			SetConsoleTextAttribute(a, 15);

			for (int b = 0; b < j - 1; b++)
			{
				int c;
				for (c = 0; c < b; c++)
					if (tableNo[b] == tableNo[c])
						break;
				if (b == c)
				{
					if (tableNo[b] != "")
					{
						SetConsoleTextAttribute(a, 14);
						cout << "\t\t\t\t\t Table Number: ";
						SetConsoleTextAttribute(a, 15);
						cout << tableNo[b] << endl
							 << endl;
					}
				}
			}

			cout << "\n\n\t\t\t\tEnter table number: ";
			getline(cin, tempTableNo);
			cout << endl;

			system("CLS");

			cout << "\n\n\t\t\t\t\t\t CHECKING CONFIRMED ORDER" << endl;
			SetConsoleTextAttribute(a, 3);
			cout << "\n\t\t\t\t ---------------------------------------------------- \n\n\n";
			SetConsoleTextAttribute(a, 15);

			for (int b = 0; b < j; b++)
			{
				if (tableNo[b] == tempTableNo)
				{
					found = true;
					for (int p = 0; p < z; p++)
					{
						if (stoi(orderID[b]) == productID[p])
						{
							cout << "\t\t\t\t Food: " << productName[p] << endl;
						}
					}
					cout << "\t\t\t\t Quantity: " << orderQty[b] << endl;
					cout << endl;
				}
			}

			if (!found)
			{
				SetConsoleTextAttribute(a, 12);
				cout << "\n\n\t\t\t\t\t DATA NOT FOUND, TRY AGAIN! \n\n";
				SetConsoleTextAttribute(a, 15);
			}

			cout << "\n\n\t\t\t\t Return to Admin Menu(y/n): ";
			cin >> ans;

			tolower(ans);

		} while (ans != 'y');

		break;
	case 2:
		do
		{
			cin.ignore();
			cout << endl;

			cout << "\n\n\t\t\t\t\t\t CUSTOMER NAME" << endl;
			SetConsoleTextAttribute(a, 3);
			cout << "\n\t\t\t\t\t ----------------------------------- \n\n\n";
			SetConsoleTextAttribute(a, 15);

			for (int b = 0; b < i - 2; b++)
			{
				int c;
				for (c = 0; c < b; c++)
					if (userName[b] == userName[c])
						break;
				if (b == c)
				{
					if (userName[b] != "")
					{
						SetConsoleTextAttribute(a, 14);
						cout << "\t\t\t\t\t Customer: ";
						SetConsoleTextAttribute(a, 15);
						cout << userName[b] << endl
							 << endl;
					}
				}
			}

			cout << "\t\t\tEnter Customer Name: ";
			getline(cin, tempUserName);
			cout << endl;

			system("CLS");

			cout << "\n\n\t\t\t\t\t\t CHECKING ORDER" << endl;
			SetConsoleTextAttribute(a, 3);
			cout << "\n\t\t\t\t ---------------------------------------------------- \n\n\n";
			SetConsoleTextAttribute(a, 15);

			for (int b = 0; b < i - 1; b++)
			{
				if (userName[b] == tempUserName)
				{
					found = true;
					cout << "\t\t\t\t Phone Number: " << userPhone[b] << endl;
					for (int p = 0; p < z; p++)
					{
						if (stoi(foodID[b]) == productID[p])
						{
							cout << "\t\t\t\t Food: " << productName[p] << endl;
						}
					}
					cout << "\t\t\t\t Quantity: " << foodQty[b] << endl;
					cout << endl;
				}
			}

			if (!found)
			{
				SetConsoleTextAttribute(a, 12);
				cout << "\n\n\t\t\t\t\t DATA NOT FOUND, TRY AGAIN! \n\n";
				SetConsoleTextAttribute(a, 15);
			}

			cout << "\n\n\t\t\t\t Return to Admin Menu: ";
			cin >> ans;

			tolower(ans);
		} while (ans != 'y');

		break;
	default:
		cout << "Invalid Input! Only 1 and 2 is allowed!" << endl;
		break;
	}
}
void Function::print_food()
{

	Food_Detail *food_temp = food_Head;
	cout << "|-------------Menu List------------------|\n\n";
	if (food_Head == NULL)
	{
		cout << "\n\nEmpty List\n\n";
		return;
	}

	while (food_temp != NULL)
	{
		cout << "Food Name           : " << food_temp->food_name << "\n";
		cout << "Food Description    : " << food_temp->food_desc << "\n";
		cout << "Food Price         : " << food_temp->food_price << "\n";
		food_temp = food_temp->food_next;
	}
	cout << "\n\n";
}

void Function::insert_food(Food_Detail food)
{
	if (!(food.food_name.empty()))
	{
		Food_Detail *new_food = new Food_Detail(food.food_name, food.food_desc, food.food_price);

		if (food_Head == NULL)
		{
			food_Head = new_food;
			return;
		}

		Food_Detail *temp = food_Head;

		while (temp->food_next != NULL)
		{
			temp = temp->food_next;
		}
		temp->food_next = new_food;
	}
};

void Function::delete_food(string food_name)
{

	Food_Detail *temp = food_Head;
	Food_Detail *prev = NULL;

	if (temp != NULL && temp->food_name == food_name)
	{
		food_Head = temp->food_next;
		delete temp;
		return;
	}
	else
	{
		while (temp != NULL && temp->food_name != food_name)
		{
			prev = temp;
			temp = temp->food_next;
		}
		if (temp == NULL)
		{
			return;
		}
		else
		{
			prev->food_next = temp->food_next;
			delete temp;
		}
	}
};

void Function::update()
{

	Food_Detail *food_temp = food_Head;

	ofstream Food_temp("Food_temp.txt");

	while (food_temp != NULL)
	{
		Food_temp << food_temp->food_name << endl;
		Food_temp << food_temp->food_desc << endl;
		Food_temp << food_temp->food_price << endl;
		food_temp = food_temp->food_next;
	}
	Food_temp.close();
	remove("menu.txt");
	rename("Food_temp.txt", "foods.txt");
}

void Function::modify_food(Function function)
{

	Food_Detail food;
	int user_input = 0;
	bool found = false;

	cout << "1. Add New Food\n\n";
	cout << "2. Delete Food\n\n";
	cout << "3. Save Food\n\n";
	cout << "4. View Food\n\n";

	do
	{
		cout << "Enter your choice : ==> ";
		cin >> user_input;

		if (cin.fail() || user_input < 1 || user_input > 4)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Error Input....Please Try Again...\n";
			found = true;
		}
		else
		{
			found = false;
		}
	} while (found);

	switch (user_input)
	{
	case 1:
		cin.ignore();

		do
		{
			cout << "\n\nEnter Food Name : ";
			getline(cin, food.food_name);

			if (food.food_name.find_first_not_of(' '))
			{
				cout << "No empty food allow....\n";
				cin.ignore();
			}
		} while (food.food_name.find_first_not_of(' '));

		cout << "\n\n--------------------------\n\n";

		do
		{
			cout << "Enter Food Description : ";
			getline(cin, food.food_desc);

			if (food.food_desc.find_first_not_of(' '))
			{
				cout << "No empty Description allow....\n";
				cin.ignore();
			}
		} while (food.food_desc.find_first_not_of(' '));

		cout << "\n\n--------------------------\n\n";

		do
		{
			cout << "Enter Food Price : ";
			getline(cin, food.food_price);

			if (food.food_price.find_first_not_of(' '))
			{
				cout << "No empty price allow....\n";
				cin.ignore();
			}
		} while (food.food_price.find_first_not_of(' '));

		function.insert_food(food);
		break;

	case 2:
		cin.ignore();

		do
		{
			cout << "\n\nEnter food Name : ";
			getline(cin, food.food_name);

			if (food.food_name.find_first_not_of(' '))
			{
				cout << "No empty food allow....\n";
			}
		} while (food.food_name.find_first_not_of(' '));

		// found = function.search_Book(food.food_name);

		if (found)
		{
			function.delete_food(food.food_name);
			cout << "\n\nDelete Success...\n";
		}
		else
		{
			cout << "\n\n Food Not found...\n\n";
		}

		break;

	case 3:
		cout << "\n\n Save \n\n";
		function.update();
		break;

	case 4:
		function.print_food();
		break;

	default:
		cout << "\n\nError Input...\n\n";
		break;
	}
}