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
			a_menu();
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

void Node ::add_menu() {

    Node *temp = new Node();

    cout << "Enter number: ";
    cin >> temp->pno;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, temp->name);

    cout << "Enter price: ";
    cin >> temp->price;

    temp->food_next = NULL;

    if (food_head == NULL) {
        food_head = temp;
        return;
    }

    Node *last = food_head;
    while (last->food_next != NULL) {
        last = last->food_next;
    }

    last->food_next = temp;

    cout << endl;
}


void Node :: display_menu() {
    Node *temp = food_head;
    file.open("menu.txt", ofstream::out);

    cout << left << setw(20) << "PNo" 
         << left << setw(25) << "Food Name" 
         << left << setw(20) << "Price"  << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    while (temp != NULL) {
        // Display node data
        cout << left << setw(20) << temp->pno 
             << left << setw(25) << temp->name 
             << left << setw(20) << temp->price <<endl;

        file << temp->pno <<  " " << temp->name << " " << temp->price << endl;
        file << endl;

        temp = temp->food_next;
    }
    file.close();
}


void Node :: modify_menu() {
    int number, ch;
    Node *temp = food_head;

    cout << "Enter Number: ";
    cin >> number;

    cout << endl;
    while (temp != NULL) {
        if ((temp->pno) == number) {
            cout << "What do you want to modify?\n";
            cout << "1. Food Name\n";
            cout << "2. Food Price\n";
            cout << "Enter an option (1 or 2): ";
            cin >> ch;

            cin.ignore();

            switch(ch) {
                case 1:
                    cout << "Enter New Name: ";
                    getline(cin, temp->name);
                    break;

                case 2:
                    cout << "Enter New Price: ";
                    cin >> temp->price;
                    break;

                default: 
					cout << "\nWrong Option!!!\n"; 
					break;
            }
            
            return;
        }
        temp = temp->food_next;
    }
    cout << " Not Found !!!";
}

void Node ::delete_menu() {
    int number;
    Node *temp = food_head;

    cout << "Enter Number want to delete: ";
    cin >> number;

    int position = 0;
    int found = 0;

    // Get position of node to delete
    while (temp != NULL) {
        position++;
        if ((temp->pno) == number) {
            found = 1;
            break;
        }
        temp = temp->food_next;
    }

    if(found == 0) {
        cout << "No existing number";
    } else {
        
        Node *temp1 = food_head;

        if (position == 1) {
            food_head = temp1->food_next;
            free(temp1);
            return;
        }

        for (int i = 2; temp1 != NULL && i < position - 1; i++) {
            temp1 = temp1->food_next;
        }

        if (temp1 == NULL || temp1->food_next == NULL) {
            return;
        }

        Node *next = temp1->food_next->food_next;
        free(temp1->food_next);
        temp1->food_next = next;

        cout << "\nFood Deleted" << endl << endl;
    }
}

void Admin::a_menu()
{
	int choice;
	Node n;
    do {
        // Display menu
        cout << "\n==============================================\n";
        cout << right << setw(35) << " Food Menu\n";
        cout << "==============================================\n";
        cout << "\n\t<1> ADD FOOD";
        cout << "\n\t<2> DISPLAY MENU";
        cout << "\n\t<3> MODIFY MENU";
        cout << "\n\t<4> DELETE MENU";
        cout << "\n\t<5> to Exit";
        cout << "\n\tEnter your choice: ";
        cin >> choice;
        cout << "\n";
        switch (choice) {
            case 1:
                n.add_menu();
                break;
            case 2:
                n.display_menu();
                break;
            case 3:
                n.modify_menu();
                break;
            case 4:
                n.delete_menu();
                break;
            case 5:
                break;
        }
    } while (choice != 5);
}