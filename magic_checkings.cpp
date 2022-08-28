// magic_checkings.cpp
// by: Charles Mitchell

/* I completed this project summer 2022. It showcases csv file manipulation skills,
and class usuage. This program asks you to create an account via a username and password
and that data is saved into a csv file. The program will end, and once you run it again,
you will login. You will only be able to login if you have a username and password in this
csv file. You will then add money to a Magic Checkings account where the money will fluctuate
by a randomly multiplying a floating point number between 0 and 2 everytime you deposite
or withdraw money. This is a playful and not realistic stock simulator basically without
all the market knowledge */

//Compile in terminal: g++ -Wall -Wextra -o magic_checkings magic_checkings.cpp

#include <iostream>
#include <fstream>
#include <cctype>
#include "magic_checkings.h"
using namespace std;

string create_user();
string create_pass();
int account_num(string data);
void add_data(string data, string username, string password);
bool check_user(string data);
bool check_pass(string data);
void command_loop();
void checkings();

int main(int argc, char* argv[])
{
    // checks to see if argument count and argument was entered correctly
    if (argc != 2)
    {
        cerr << "Usage: ./magic_checkings registerdata.csv" << endl;
        return 1;
    }

    // stores the data file name into a string variable
    string data = argv[1];
    int choice;

    // a loop that continues to ask the user to create an account or login if they enter anything but 1 or 2
    while (choice < 1 or choice > 2)
    {
        cout << "Create a new account (1) or login (2)? ";
        cin >> choice;
    }

    // if the user enters 1, they will go through the process of creating an account
    if (choice == 1)
    {
        // stores entered username and password from create_user and create_pass functions into two strings
        string username = create_user();
        string password = create_pass();

        // calls the add_data void function and quits the program
        add_data(data, username, password);
        return 0;
    }

    // if the user enters 2, they will then go through the login process to enter the simulation
    else if (choice == 2)
    {
        // stores the return value from the check_user function into a new boolean variable
        bool user = check_user(data);

        // if the value from the check_user function is true, then continue with the login process
        if (user == true)
        {
            // stores the return balue from the check_pass function into a new boolean variable
            bool pass = check_pass(data);

            // if the value from the check_pass function is true, then continue into the simulation
            if (pass == true)
            {
                // a loop function that starts the entire simulation
                command_loop();
            }

            // if the value from the check_pass function is false, then quit the program
            else
            {
                cout << "Incorrect password" << endl;
                return 0;
            }
        }

        // if the value from the check_user function is false, then quit the program
        else
        {
            cout << "Username not found" << endl;
            return 0;
        }

    }

    return 0;
}


/*
create_user
Parameters: None
Purpose: asks user to create a username that is atleast 5
        characters long with no spaces
Returns: the username inputted by the user
*/
string create_user()
{
    string username;
    bool check = false;

    while (check == false)
    {
        cout << "Username must be atleast 5 characters with no spaces" << endl;
        cout << "Enter a username: ";
        cin >> username;

        for (unsigned int i = 0; i < username.length(); i++)
        {
            if (username.length() >= 5 and username[i]!= ' ')
            {
                check = true;
            }
        }
    }

    return username;
}


/*
create_pass
Parameters: None
Purpose: asks user to create a password that is atleast 7
        characters long with no spaces
Returns: the password inputted by the user
*/
string create_pass()
{
    string password;
    bool check = false;

    while (check == false)
    {
        cout << "Password must be atleast 7 characters with no spaces" << endl;
        cout << "Enter a password: ";
        cin >> password;

        for (unsigned int i = 0; i < password.length(); i++)
        {
            if (password.length() >= 7 and password[i] != ' ')
            {
                check = true;
            }
        }
    }

    return password;
}


/*
add_data
Parameters: the name of the csv file, the username, and the password
Purpose: adds the username and password inputted by the user
        into the csv file
Returns: Nothing
*/
void add_data(string data, string username, string password)
{
    ofstream file;
    file.open(data, ofstream::app);

    if (not file.is_open())
    {
        cerr << "Could not open file:" << data << endl;
    }

    file << username << ", " << password << endl;

    file.close();
}


/*
check_user
Parameters: the name of the csv file
Purpose: checks to see if the username the user inputted
        to login is in the csv file
Returns: true or false
*/
bool check_user(string data)
{
    string username;
    string line;
    ifstream file;
    file.open(data);

    if (not file.is_open())
    {
        cerr << "Could not open file: " << data << endl;
        return false;
    }

    cout << "Enter username: ";
    cin >> username;

    while (not file.eof())
    {
        getline(file, line);

        // if the username is found in the csv file
        if (line.find(username) != string::npos)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}


/*
check_pass
Parameters: the name of the csv file
Purpose: checks to see if the password the user inputted
        to login is in the csv file
Returns: true or false
*/
bool check_pass(string data)
{
    string password;
    string line;
    ifstream file;
    file.open(data);

    if (not file.is_open())
    {
        cerr << "Could not open file: " << data << endl;
        return false;
    }

    cout << "Enter password: ";
    cin >> password;

    while (not file.eof())
    {
        getline(file, line);

        // if the password is found in the csv file
        if (line.find(password) != string::npos)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

/*
command_loop
Parameters: None
Purpose: performs a do while loop to open a query window and gives users options to either enter a
        Magic Checkings account or to logout
Returns: Nothing
*/
void command_loop()
{
    char command;
    cout << "Welcome to Mithcell's Magic Checkings! Here is how it works: You deposit and withdraw " <<
    "money from a checkings account. Each time a transaction is made, your balance will be multiplied " <<
    "by any floating point number between 0 and 2. It is completly randomized. Play at your own risk!" << endl;
    cout << "When you logout, your Magic Checkings account balance will be deposited into you Venmo account!" << endl;
    cout << endl;

    do {
        cout << "Would you like to access a magic checkings account (c) " <<
        "or log out (q)? ";
        cin >> command;

        command = tolower(command);

        if (command == 'c')
        {
            checkings();
        }

    } while (command != 'q');
}


/*
checkings
Parameters: None
Purpose: performs a do while loop to open a query window and gives users options to either deposit,
        withdraw, or quit the simulation. This function is teither with the header file which has
        the class and its member functions used in this function
Returns: Nothing
*/
void checkings()
{
    double initial;

    cout << endl;
    cout << "Please enter an inital ammount you would like to deposit " <<
    "into your account. $";
    cin >> initial;

    CheckingsAccount userAccount(initial);

    char command;

    do {
        cout << "Would you like to withdraw (w)" <<
        ", deposit (d), or go back (q)? ";
        cin >> command;

        command = tolower(command);

        if (command == 'w')
        {
            double w_amount;
            cout << "How much would you like to withdraw? $";
            cin >> w_amount;

            userAccount.withdraw(w_amount);
            userAccount.show_acc_info();
        }
        else if (command == 'd')
        {
            double d_amount;
            cout << "How much would you like to deposit? $";
            cin >> d_amount;

            userAccount.deposit(d_amount);
            userAccount.show_acc_info();
        }
    } while (command != 'q');
}
