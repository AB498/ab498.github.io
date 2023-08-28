#include <iostream>
#include <conio.h>
using namespace std;
int input;

class drinks
{
    string optionsString;

public:
    friend void setOptions(drinks &drinks, string opts);
    virtual string getTitle()
    {

        return "  ";
    }
    void showSize()
    {

        cout << "Which size do you want?" << endl;
        cout << "1. 500ml" << endl;
        cout << "2. 1000ml" << endl;
        cout << "3. 2000ml" << endl;
    }
    void showOptions()
    {
        cout << optionsString;
    }
    void setOptions(string options)
    {
        optionsString = options;
    }

    void confirm()
    {

        cout << "Please confirm " << endl;
        cout << "1. Yes" << endl;
        cout << "2. no" << endl;
    }

    ~drinks() {}
};

class softdrinks : public drinks
{
public:
    string getTitle()
    {
        return "List of Soft Drinks";
    }
    string getTitle(string title)
    {

        return title;
    }
    softdrinks()
    {
        setOptions("1. Coke\n"
                   "2. Sprite\n"
                   "3. Mirinda\n");
    }
};

class juice : public drinks
{

public:
    string getTitle()
    {
        return "List of Juice";
    }
    juice()
    {
        setOptions("1. Mango\n"
                   "2. Orange\n"
                   "3. Apple\n"
                   "4. Pineaple\n");
    }
};

class dairy : public drinks
{

public:
    string getTitle()
    {
        return "List of Dairy";
    }
    dairy()
    {
        setOptions("1. Plain Milk\n "
                   "2. Mango Milk\n"
                   "3. Chocolate Milk\n");
    }
};
class coffe_tea : public drinks
{

public:
    string getTitle()
    {
        return "List of Coffee/Tea";
    }
    coffe_tea()
    {
        setOptions("1. Tea\n"
                   "2. Coffee\n");
    }
};

void setOptions(drinks &drinks, string opts)
{
    drinks.optionsString = opts;
}

inline void intro()
{
    cout << "Welcome :)" << endl;
    cout << "Please enter your choice" << endl;
    cout << "1.Drinks" << endl;
    cout << "2.Juice" << endl;
    cout << "3.Dairy" << endl;
    cout << "4.Tea" << endl;
}
int main()
{
    system("cls");
    intro();

    softdrinks *drinks0 = new softdrinks();
    dairy *dairy0 = new dairy();
    juice *juice0 = new juice();
    coffe_tea *coffee0 = new coffe_tea();
    setOptions(*drinks0, "1. Coke\n"
                         "2. Sprite\n"
                         "3. Mirinda\n");
    cin >> input;

    if (input == 1)
    {
        system("cls");
        cout << drinks0->getTitle("List of Soft Drinks") << endl;
        drinks0->showOptions();
        cin >> input;
        if (input != 1 && input != 2 && input != 3)
        {
            cout << "Invalid option!!";
            getch();
            return 0;
        }

        system("cls");
        drinks0->showSize();
        cin >> input;
        if (input != 1 && input != 2 && input != 3)
        {
            cout << "Invalid option!!";
            getch();
            return 0;
        }
        system("cls");
        drinks0->confirm();
        cin >> input;
        if (input == 1)
        {
            cout << "Thank you for your purchase!! ";
        }
        else if (input == 2)
        {
            cout << "Order canceled!!";
        }
        else
        {
            cout << "Invalid option!!";
        }

        getch();
        return 0;
    }
    else if (input == 2)
    {
        system("cls");
        cout << juice0->getTitle() << endl;
        juice0->showOptions();
        cin >> input;
        if (input != 1 && input != 2 && input != 3 && input != 4)
        {
            cout << "Invalid option!!";
            getch();
            return 0;
        }
        system("cls");
        juice0->showSize();
        cin >> input;
        if (input != 1 && input != 2 && input != 3)
        {
            cout << "Invalid option!!";
            getch();
            return 0;
        }
        system("cls");
        juice0->confirm();
        cin >> input;
        if (input == 1)
        {
            cout << "Thank you for your purchase!! ";
        }
        else if (input == 2)
        {
            cout << "Order canceled!!";
        }
        else
        {
            cout << "Invalid option!!";
        }

        getch();
        return 0;
    }
    else if (input == 3)
    {
        system("cls");
        cout << dairy0->getTitle() << endl;
        dairy0->showOptions();
        cin >> input;
        if (input != 1 && input != 2 && input != 3)
        {
            cout << "Invalid option!!";
            getch();
            return 0;
        }
        system("cls");
        dairy0->showSize();
        cin >> input;
        if (input != 1 && input != 2 && input != 3)
        {
            cout << "Invalid option!!";
            getch();
            return 0;
        }
        system("cls");
        dairy0->confirm();
        cin >> input;
        if (input == 1)
        {
            cout << "Thank you for your purchase!! ";
        }
        else if (input == 2)
        {
            cout << "Order canceled!!";
        }
        else
        {
            cout << "Invalid option!!";
        }

        getch();
        return 0;
    }
    else if (input == 4)
    {
        system("cls");
        cout << coffee0->getTitle() << endl;
        coffee0->showOptions();
        cin >> input;
        if (input != 1 && input != 2)
        {
            cout << "Invalid option!!";
            getch();
            return 0;
        }
        system("cls");
        coffee0->showSize();
        cin >> input;
        if (input != 1 && input != 2 && input != 3)
        {
            cout << "Invalid option!!";
            getch();
            return 0;
        }
        system("cls");
        coffee0->confirm();
        cin >> input;
        if (input == 1)
        {
            cout << "Thank you for your purchase!! ";
        }
        else if (input == 2)
        {
            cout << "Order canceled!!";
        }
        else
        {
            cout << "Invalid option!!";
        }

        getch();
        return 0;
    }
    else
    {
        cout << "Invalid option!!";
    }

    delete drinks0;
    delete dairy0;
    delete juice0;
    delete coffee0;

    cin.ignore();
    getch();
    return 0;
}