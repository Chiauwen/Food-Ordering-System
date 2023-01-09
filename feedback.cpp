#include <iostream>
#include <stack>
#include <string>
#include <fstream>
using namespace std;

#include "feedback.h"
#include "main.h"

void feedback::fill_feedback()
{

    stack<string> feedback;
    stack<int> rate;

    int choice, rating, choice3;
    string feed_choice;
    char choice2, choice4;

    system("CLS");

fill_in:
    cout << "FEEDBACK" << endl
         << endl;
    cout << "1. Food" << endl;
    cout << "2. Drink" << endl;
    cout << "3. Services" << endl;
    cout << "4. Self Order Machine" << endl;

    cout << "What do you want to feedback to us?: ";
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

    cout << "Give us a rating on " << feedback.top();
    cin >> rating;
    rate.push(rating);

    cout << "Review your feedback before submit" << endl;
    cout << "Feedback topic: " << feedback.top() << endl;
    cout << "Rating: " << rate.top() << endl;

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

            if(choice4!='n'){
                goto fill_in;
            }
            else{
                countdown();
            }
        }
        else{
            
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