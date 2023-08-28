#include <iostream>
#include <conio.h>
using namespace std;
void mainMenu();

class Details
{
private:
    string name, gender;
    int age;
    string address;
    int cId;
    char arr[100];

public:
    void displayinfo()
    {

        cout << "\nName:" << name << endl;
        cout << "\nGender:" << gender << endl;
        cout << "\nAge:" << age << endl;
        cout << "\nAddress:" << address << endl;
        cout << "\nCustomer ID:" << cId << endl;
    }

    Details() // default constructor
    {
        cId = 0;
        name = "Soniya";
        age = 24;
        gender = "female";
        address = "shahbag";
    }

    Details(int cId, string name, string gender, string address, int age) // parameterized constructor
    {
        cout << "parameterized constructer called" << endl;
        this->name = name;
        this->cId = cId;
        this->gender = gender;
        this->address = address;
        this->age = age;
    }

    Details(Details &d) // copy constructor

    {
        name = d.name;
        cId = d.cId;
        gender = d.gender;
        address = d.address;
        age = d.age;
    }
    ~Details()
    {
        cout << "this is a destructor" << endl;
    }
};

class Management
{
public:
    Management()
    {
        mainMenu();
    }
};
void mainMenu()
{
    int lchoice;
    int schoice;
    int back;

    cout << "\t    XYZ Airlines\n"
         << endl;
    cout << "\t __Main Menu___" << endl;

    cout << "\t_______" << endl;
    cout << "\t|\t\t\t\t\t\t|" << endl;

    cout << "\t|\t press 1 to add the Customer Details \t|" << endl;
    cout << "\t|\t press 2 for Flight Registration     \t|" << endl;
    cout << "\t|\t press 3 for Ticket and Charges      \t|" << endl;
    cout << "\t|\t press 4 to Exit                     \t|" << endl;
    cout << "\t|\t\t\t\t\t\t|" << endl;
    cout << "\t_______________" << endl;
    cout << "Enter the choice:";
    cin >> lchoice;

    switch (lchoice)
    {
    case 1:
    {
        cout << "customer details\n"
             << endl;
        Details d2(369, "Soniya", "female", "shahbag", 24);
        d2.displayinfo();
        cout << "press 1 to go back to main menu";
        cin >> back;

        if (back == 1)
        {
            mainMenu();
        }
        else
        {
            mainMenu();
        }
        break;
    }
    case 2:
    {
        cout << "book a flight using this system\n"
             << endl;

        string flights[] = {"Dubai", "Canada", "Australia"};

        for (int i = 0; i < 3; i++)
        {
            cout << i + 1 << ". Flight to " << flights[i] << endl;
        }

        cout << "Choose your flight: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nYou have chosen: ";
            cout << "\nDUB-498" << endl;
            cout << "\t21.3.2023 10hrs" << endl;
            cout << "\tTk. 14000";
            break;
        case 2:
            cout << "\nYou have chosen: ";
            cout << "\nCAN-498" << endl;
            cout << "\t21.3.2023 10hrs" << endl;
            cout << "\tTk. 15000";
            break;
        case 3:
            cout << "\nYou have chosen: ";
            cout << "\nAUS-498" << endl;
            cout << "\t21.3.2023 10hrs" << endl;
            cout << "\tTk. 16000";
            break;
        default:
            cout << "\nWrong option ";
            break;
        }
        mainMenu();
        break;
    }

    case 3:
        cout << "GET YOUR TICKET\n"
             << endl;

        cout << "Your ticket is printed.you can collect it\n"
             << endl;
        cout << "Press 1 to display your ticket";
        cin >> back;

        if (back == 1)
        {

            cout << "Press any key to go back to main menu:";
            cin >> back;

            if (back == 1)
            {
                mainMenu();
            }
            else
            {
                mainMenu();
            }
        }
        else
        {
            mainMenu();
        }
        break;

    case 4:
    {
        cout << "Thank you" << endl;
        break;
    }
    default:
    {
        cout << "Invalid input, please try again!\n"
             << endl;
        mainMenu();
        break;
    }
    }
};
// c++ virtual function

class Airlines
{
public:
    virtual void display()
    {
        cout << "welcome to airlines" << endl;
    }
};

class Dubai : public Airlines
{
public:
    void display()
    {
        cout << "Welcome the Dubai" << endl;
        cout << "Enjoy the journey" << endl;
    }
};

// function overloading
class registration
{
public:
    void getName(char Dubai)
    {
        cout << "Dubai" << endl;
    }

    void getName(char Canada, char USA)
    {
        cout << "Canada" << endl;
        cout << "USA" << endl;
    }
};

// function overriding
class regestration
{
public:
    void display()
    {
        cout << "Welcome to Dubai" << endl;
    }
};
class ticket : public regestration
{
public:
    void display()
    {
        cout << "you have successfully booked Dubai flight" << endl;
        cout << " you take the ticket" << endl;
    }
};
int main()
{
    // Details d1, d2(369, "Soniya", "female", "shahbag", 24);
    // d1.displayinfo();
    // d2.displayinfo();

    // Airlines *a;
    // Dubai d;
    // a = &d;
    // a->display();

    // regestration r;
    // ticket t;
    // t.display();
    // r.display();
    // getch();

    mainMenu();

    return 0;
}