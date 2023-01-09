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

    int choice, rating;
    string feed_choice;
    char choice2;

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

    cout << "Review your feedback: ";
    cout << "Feedback topic: " << feedback.top() << endl;
    cout << "Rating: " << rate.top() << endl;

    cout << "Confirm your feedback?(y/n): ";
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
            file << feedback.top() << " " << rate.top() << endl;
        }

        file.close();

        cout << "Feedback received !" << endl;

        feedback.pop();
        rate.pop();
    }
    
}
