#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

#include "feedback.h"
#include "main.h"

HANDLE f = GetStdHandle(STD_OUTPUT_HANDLE); /* FOR TEXT COLOUR */

void feedback::fill_feedback()
{

    stack<string> feedback;
    stack<int> rate;

    int choice, rating, choice3;
    string feed_choice;
    char choice2, choice4;

    system("CLS");

fill_in:
    SetConsoleTextAttribute(f, 6);
    cout << "\n\t\t\t\t --------------------------------------------- \n\n";
    SetConsoleTextAttribute(f, 7);
    cout << "\t\t\t\t\t\t    FEEDBACK" << endl;
    SetConsoleTextAttribute(f, 6);
    cout << "\n\t\t\t\t --------------------------------------------- \n";

    SetConsoleTextAttribute(f, 7);
    cout << "\n\t\t\t\t 1. Food" << endl;
    cout << "\t\t\t\t 2. Drink" << endl;
    cout << "\t\t\t\t 3. Services" << endl;
    cout << "\t\t\t\t 4. Self Order Machine" << endl;

    feedback:
    SetConsoleTextAttribute(f, 7);
    cout << "\n\t\t\t\t What do you want to feedback to us?: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        feed_choice = " Food: ";
        break;
    case 2:
        feed_choice = " Drink: ";
        break;
    case 3:
        feed_choice = " Services: ";
        break;
    case 4:
        feed_choice = " Self Order Machine: ";
        break;
    default:
        SetConsoleTextAttribute(f, 4);
        cout << "\n\t\t\t\t Invalid input, try again!\n";
        goto feedback;
    }

    feedback.push(feed_choice);

    system("CLS");

    rate:
    SetConsoleTextAttribute(f, 7);
    cout << "\n\n\n \t\t\t\t\t Please give us a rating (0 to 100): \n\n"
         << "\t\t\t\t\t" << feedback.top();
    cin >> rating;
    if (rating < 0 || rating > 100)
    {
        SetConsoleTextAttribute(f, 4);
        cout << "\n \t\t\t\t\t Please rate from 0 to 100.\n"
             << endl;
        goto rate;
    }
    else
    {
        system("CLS");
        rate.push(rating);

        SetConsoleTextAttribute(f, 7);
        cout << "\n\n \t\t\t\t\t 1. Submit feedback" << endl;
        cout << "\n\t\t\t\t\t 2. Make another feedback" << endl;
        cout << "\n\t\t\t\t\t 3. Undo previous feedback" << endl;
        cout << "\n\t\t\t\t\t 4. Cancel feedback" << endl;
    option:
        SetConsoleTextAttribute(f, 7);
        cout << "\n \t\t\tPlease select an option: ";
        cin >> choice3;

        switch (choice3)
        {
        case 1:
            choice2 = 'y';
            break;
        case 2:
            system("cls");
            goto fill_in;
            break;
        case 3:
            feedback.pop();
            rate.pop();
            if (feedback.empty() && rate.empty())
            {
                SetConsoleTextAttribute(f, 4);
                cout << " \n\t\t\t Oops, you don't have a previous feedback!" << endl;

                SetConsoleTextAttribute(f, 15);
                cout << " \n\n \t\t\tMake a new feedback?(y/n): " << endl;
                cin >> choice4;

                tolower(choice4);

                if (choice4 != 'n')
                {
                    goto fill_in;
                }
                else
                {
                    countdown();
                }
            }
            else
            {

                SetConsoleTextAttribute(f, 10);
                cout << "\n\n\n \t\t\t\tUndo successfully!" << endl;
                goto option;
            }
            break;
        case 4:
            choice2 = 'n';
            break;
        default:
            SetConsoleTextAttribute(f, 4);
            cout << "\n Invalid input, try again!\n";
            goto option;
        }

        tolower(choice2);

        if (choice2 == 'n')
        {
            SetConsoleTextAttribute(f, 4);
            cout << "\n\n \t\t\t\tYour feedback form will be cancel\n" << endl;
            SetConsoleTextAttribute(f, 15);
            feedback.pop();
            rate.pop();
        }
        else
        {
            ofstream file;
            file.open("feedback.txt", ios::app);

            if (file.is_open())
            {
                while (!feedback.empty() && !rate.empty())
                {
                    file << feedback.top() << " " << rate.top() << endl;
                    feedback.pop();
                    rate.pop();
                }
            }

            file.close();

            SetConsoleTextAttribute(f, 10);
            cout << "\n\t\t\t Feedback received!" << endl;
            SetConsoleTextAttribute(f, 7);
            cout << "\n\t Thank you for your feedback, we will try our best to improve our services to you\n\n\n\n\n" << endl;
        }

        countdown();
    }
}

void feedback::countdown()
{

    int counter = 9; // amount of seconds
    Sleep(10);

    cout << "\n\n";

    while (counter >= 1)
    {
        cout << "\r You will return back to main menu in " << counter << " seconds....." << flush;
        Sleep(1000);
        counter--;
    }

    mainPage();
}
