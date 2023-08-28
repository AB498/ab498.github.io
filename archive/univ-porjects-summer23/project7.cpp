#include <iostream>
#include <string>
using namespace std;

class Userinfo
{
private:
    string username, password;

public:
    Userinfo(string name, string pass) : username(name), password(pass) {}

    ~Userinfo() {}
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

class MenuItem
{
public:
    virtual void display() = 0;
    virtual int getPrice() = 0;
    virtual string getName() = 0;
};

class RiceAndEgg : public MenuItem
{
public:
    void display() override
    {
        cout << "1. Rice and Egg" << endl;
    }
    string getName() override
    {
        return "";
    }
    int getPrice() override
    {
        return 100;
    }
};

class VegetableAndFriedRice : public MenuItem
{
public:
    void display() override
    {
        cout << "2. Vegetable and Fried Rice" << endl;
    }
    string getName() override
    {
        return "";
    };
    int getPrice() override
    {
        return 150;
    }
};

class Mutton : public MenuItem
{
public:
    void display() override
    {
        cout << "3. Mutton" << endl;
    }
    string getName() override
    {
        return "";
    };
    int getPrice() override
    {
        return 200;
    }
};

class Chicken : public MenuItem
{
public:
    void display() override
    {
        cout << "4. Chicken" << endl;
    }
    string getName() override
    {
        return "";
    };
    int getPrice() override
    {
        return 250;
    }
};

class totalBalance
{
private:
    string name;
    int fund;

public:
    totalBalance(int balance) : fund(balance) {}

    void showBalance()
    {
        cout << "Balance: " << fund << " BDT" << endl;
    }

    bool reduce(int amount)
    {
        if (fund >= amount)
        {
            fund -= amount;
            return true; // Reduction successful
        }
        else
        {
            cout << "Insufficient balance." << endl;
            return false; // Reduction failed
        }
    }
};
int main()
{
    Userinfo *user = nullptr;
    totalBalance balance(1000);
    string meal = "";

    int op;
    string name, pass;
    Register *manage;

    while (true)
    {
        cout << "1. Register User" << endl;
        cout << "2. Menu Items" << endl;
        cout << "3. Total Balance & Remaining Balance" << endl;
        cout << "4. Total Meal" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter Your Choice: ";
        cin >> op;
        cout << endl;

        RiceAndEgg rice;
        VegetableAndFriedRice vegetableAndFriedRice;
        Mutton mutton;
        Chicken chicken;
        MenuItem *chosenItem = nullptr;
        switch (op)
        {
        case 1:
            cout << "Enter username: ";
            cin >> name;
            cout << "Enter password: ";
            cin >> pass;
            user = new Userinfo(name, pass);
            cout << "---User Registration Successful---" << endl;
            break;
        case 2:
            if (user == nullptr)
            {
                cout << "Register first" << endl;
                break;
            }

            int input;

            rice.display();
            vegetableAndFriedRice.display();
            mutton.display();
            chicken.display();

            cin >> input;

            if (input == 1)
            {
                chosenItem = &rice;
            }
            else if (input == 2)
            {
                chosenItem = &vegetableAndFriedRice;
            }
            else if (input == 3)
            {
                chosenItem = &mutton;
            }
            else if (input == 4)
            {
                chosenItem = &chicken;
            }

            if (chosenItem != nullptr)
            {
                chosenItem->display();
                meal = chosenItem->getName();
                if (balance.reduce(chosenItem->getPrice()))
                {
                    cout << "You have chosen: " << meal << endl;
                }
            }
            else
            {
                cout << "Invalid choice" << endl;
            }

            break;
        case 3:
            balance.showBalance();
            break;
        case 4:
            cout << "Total Meal: " << meal << endl;
            break;
        case 5:
            delete user;
            return 0;
        default:
            cout << "Invalid option " << endl;
            break;
        }
    }

    return 0;
}
