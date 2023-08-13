#include <iostream>
#include <vector>
using namespace std;
int x, y, z, z1, a;

class drinks;

void setOptions(drinks &d, vector<string> opts)
{
    d.options = opts;
}

class drinks
{
    vector<string> options;

public:
    friend void setOptions(drinks &d, vector<string> opts);

    vector<string> getOptions()
    {
        return options;
    }

    virtual string getTitle()
    {
        // virtual function
    }
};
class softdrinks : public drinks
{
public:
    softdrinks()
    {
        setOptions({"Coke", "Sprite", "Mojo"});
    }
};
class juice : public drinks
{

public:
    juice()
    {
        setOptions({"Mango", "Strawberry", "Orange"});
    }
};

class dairy : public drinks
{

public:
    dairy()
    {
        setOptions({"Chocolate Milk", "Plain Milk", "Yogurt"});
    }
};
class coffe_tea : public drinks
{

public:
    coffe_tea()
    {
        setOptions({"Coffee", "Tea", "Black Coffe", "Americano", "Lemon Tea", "Masala Tea"});
    }
};
class OrderInformation
{
public:
    int size;
    string drinkName;
    int cancelled = 0;
};

OrderInformation takeOrder(vector<string> drink_options)
{
    OrderInformation order;
    for (int i = 0; i < drink_options.size(); i++)
    {
        cout << i + 1 << ". " << drink_options[i] << endl;
    }
    cin >> x;
    order.drinkName = drink_options[x - 1];

    vector<int> sizes = {500, 1000, 2000};
    cout << "Which size do you want ?" << endl;
    for (int i = 0; i < sizes.size(); i++)
    {
        cout << i + 1 << ". " << sizes[i] << endl;
    }
    cin >> x;
    order.size = sizes[x - 1];

    cout << "Please confirm your product" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cin >> x;
    order.cancelled = x != 1;

    return order;
}
int main()
{
    cout << "welcome" << endl;
    cout << "please enter your choice" << endl;
    cout << "1.drinks" << endl;
    cout << "2.juice" << endl;
    cout << "3.dairy" << endl;
    cout << "4.tea" << endl;
    cin >> x;

    softdrinks soft;
    dairy dairy;
    juice juice;
    coffe_tea coff;

    OrderInformation order;
    if (x == 1)
    {
        order = takeOrder(soft.getOptions());
    }
    else if (x == 2)
    {
        order = takeOrder(dairy.getOptions());
    }
    else if (x == 2)
    {
        order = takeOrder(juice.getOptions());
    }
    else if (x == 2)
    {
        order = takeOrder(coff.getOptions());
    }

    if (order.cancelled == 2)
        cout << "You cancelled the order" << endl;
    else
    {
        cout << "Thank you for purchasing 🙂" << endl;
        cout << "You picked:" << endl;
        cout << order.drinkName << endl;
        cout << "Size: " << order.size << endl;
    }
    return 0;
}