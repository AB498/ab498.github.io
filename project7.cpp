#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

class Userinfo
{
private:
    string username, password;

public:
    Userinfo(string name, string pass)
    {
        username = name;
        password = pass;
    }
    ~Userinfo()
    {
    }
    friend class Register;
};

class Register : public Userinfo
{
public:
    Register(string name, string pass) : Userinfo(name, pass)
    {
    }

    void user_register(Userinfo &ob)
    {
        cout << "---User Registration Successful---" << endl;
    }
};
class menuList
{
public:
    void display_item()
    {
        cout << "1. Rice and Egg" << endl;
        cout << "2. Vegatable and Fride Rice" << endl;
        cout << "3. Muttan" << endl;
        cout << "4. Chicken" << endl;
    }
};

class totalBalance
{
public:
    string name;
    int fund;
    totalBalance(int balance)
    {
        fund = balance;
    }
    void showBalance()
    {
        cout << "Balance: " << fund << " BDT" << endl;
    }
    void reduce(int amount)
    {
        fund -= amount;
    }
};
int main()
{
    Userinfo *user = NULL;
    totalBalance *balance = new totalBalance(1000);
    string meal = "";

loop:
    int op;
    cout << "1. Register User" << endl;
    cout << "2. Menu Items" << endl;
    cout << "3. Total Balance & Remaing Balance" << endl;
    cout << "4. Total Meal" << endl;
    cout << "5. Exit" << endl;

    int input;
    string name;
    string pass;
    Register *manage;
    cout << "Enter Your Choice: ";

    cin >> op;
    cout << endl;
    switch (op)
    {
    case 1:
        cout << "Enter username: ";
        cin >> name;
        cout << "Enter password: ";
        cin >> pass;
        manage = new Register(name, pass);
        user = new Userinfo(name, pass);
        manage->user_register(*user);
        break;
    case 2:
        if (user == NULL)
        {
            cout << "Register first" << endl;
            break;
        }
        menuList m;
        m.display_item();
        cin >> input;
        if (input == 1)
        {
            meal = "Rice and Egg";
        }
        else if (input == 2)
        {
            meal = "Vegatable and Fride Rice";
        }
        else if (input == 3)
        {
            meal = "Muttan";
        }
        else if (input == 4)
        {
            meal = "Chicken";
        }
        balance->reduce(100);
        cout
            << "You have chosen: " << meal << endl;

        break;
    case 3:
        if (user == NULL)
        {
            cout << "Register first" << endl;
            break;
        }
        balance->showBalance();
        break;
    case 4:
        if (user == NULL)
        {
            cout << "Register first" << endl;
            break;
        }
        cout << "Meals Chosen: " << meal << endl;
        break;
    case 5:
        exit(0);
        break;
    default:
        cout << "Invalid option " << endl;
        break;
    }
    getch();
    goto loop;

    return 0;
}
