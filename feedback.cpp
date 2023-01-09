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

    cout << "\n\t\t\t\t What do you want to feedback to us?: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        feed_choice = "Food";
        break;
    case 2:
        feed_choice = "Drink";
        break;
    case 3:
        feed_choice = "Services";
        break;
    case 4:
        feed_choice = "Self Order Machine";
        break;
    default:
        cout << "Invalid input, try again!";
    }

    feedback.push(feed_choice);

    system("CLS");

rate:
    SetConsoleTextAttribute(f, 7);
    cout << "\n Please give us a rating (0 to 100): \n\n"
         << feedback.top();
    cin >> rating;
    if (rating < 0 || rating > 100)
    {
        SetConsoleTextAttribute(f, 4);
        cout << "\n Please rate from 0 to 100.\n"
             << endl;
        goto rate;
    }
    else
    {
        rate.push(rating);

    menu:
        cout << "1. Confirm submit feedback" << endl;
        cout << "2. Submit another feedback" << endl;
        cout << "3. Undo previous feedback" << endl;
        cout << "4. Cancel feedback" << endl;
        cin >> choice3;

        switch (choice3)
        {
        case 1:
            choice2 = 'y';
            break;
        case 2:
            goto fill_in;
            break;
        case 3:
            feedback.pop();
            rate.pop();
            if (feedback.empty() && rate.empty())
            {
                cout << "Oops, feedback can't be empty!" << endl;
                cout << "Make a new feedback?(y/n): " << endl;
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

                cout << "Undo successfully!" << endl;
                goto menu;
            }
            break;
        case 4:
            choice2 = 'n';
        default:
            cout << "Wrong input, try again!";
        }

        tolower(choice3);

        cout << "Confirm submit feedback(s)?: ";
        cin >> choice2;

        tolower(choice2);

        if (choice2 == 'n')
        {
            cout << "Your feedback form will be cancel" << endl;
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

            cout << "Feedback received !" << endl;
        }

        countdown();
    }
}

void feedback::countdown()
{
    int counter = 9; // amount of seconds
    Sleep(10);

    while (counter >= 1)
    {
        cout << "\r You will return back to main menu in " << counter << " seconds....." << flush;
        Sleep(1000);
        counter--;
    }

    mainPage();
}