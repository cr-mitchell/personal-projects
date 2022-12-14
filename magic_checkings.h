// magic_checkings.h
// by: Charles Mitchell

/* This is the header file used in magic_checkings.cpp. It contains the class member functions
used the cpp file */

#include <iostream>
#include <random>
using namespace std;

class CheckingsAccount {
    public:
        CheckingsAccount();
        CheckingsAccount(double given_balance);
        void withdraw(double amount);
        void deposit(double amount);
        double UpdatedBalance();
        void show_acc_info();

    private:
        double balance;
};

CheckingsAccount::CheckingsAccount()
{
    balance = 0.0;
}

CheckingsAccount::CheckingsAccount(double given_balance)
{
    balance = given_balance;
}

void CheckingsAccount::withdraw(double amount)
{
    if (balance < amount)
    {
        balance = balance
    }
    else if (balance > amount)
    {
        balance -= amount;
    }
}

void CheckingsAccount::deposit(double amount)
{
    balance += amount;
}

double CheckingsAccount::UpdatedBalance()
{
    double temp = (rand() % 21) / 10.0;

    // rounds the balance to 2 decimal places
    balance *= temp;

    // rounds the balance to 2 decimal places using int typecast
    balance = (int) (balance * 100.0 + 0.5);
    balance = balance / 100.0;

    return balance;
}

void CheckingsAccount::show_acc_info()
{
    cout << "Checking Account Balance with randomized adjustment: $" << UpdatedBalance() << endl;
}
