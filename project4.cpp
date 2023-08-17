#include <iostream>
#include <vector>
using namespace std;
int input;

class drinks
{
    vector<string> options;

public:
    vector<string> getOptions()
    {
        return options;
    }
    virtual string getTitle()
    {
        // virtual function
        return "";
    }

    friend void setOptions(drinks *d, vector<string> opts);
    ~drinks() {}
};
void setOptions(drinks *d, vector<string> opts)
{
    d->options = opts;
}

class softdrinks : public drinks
{
public:
    string getTitle()
    {
        return "List of Soft Drinks";
    }
    string getTitle(string title)
    {
        // overloaded function
        return title;
    }
    softdrinks()
    {
        setOptions(this, {"Coke", "Sprite", "Mojo"});
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
        setOptions(this, {"Mango", "Strawberry", "Orange"});
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
        setOptions(this, {"Chocolate Milk", "Plain Milk", "Yogurt"});
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
        setOptions(this, {"Coffee", "Tea", "Black Coffe", "Americano", "Lemon Tea", "Masala Tea"});
    }
};
class OrderInformation
{
public:
    string size;
    string drinkName;
    int cancelled = 0;
    type_info *drinkTypeid;
    OrderInformation()
    {
        drinkTypeid = const_cast<type_info *>(&typeid(this));
    }
};

inline OrderInformation takeOrder(vector<string> drink_options, bool allow_quantity = true)
{
    OrderInformation order;
    for (int i = 0; i < drink_options.size(); i++)
    {
        cout << i + 1 << ". " << drink_options[i] << endl;
    }
    cin >> input;
    order.drinkName = drink_options[input - 1];

    system("cls");
    if (allow_quantity)
    {

        vector<int> quantity_options = {500, 1000, 2000};
        cout << "Which size do you want ?" << endl;
        for (int i = 0; i < quantity_options.size(); i++)
        {
            cout << i + 1 << ". " << quantity_options[i] << "mL" << endl;
        }
        cin >> input;
        order.size = to_string(quantity_options[input - 1]) + "mL";
    }
    else
    {
        order.size = "1 Unit";
    }

    system("cls");
    cout << "Please confirm your product" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cin >> input;
    order.cancelled = input != 1;

    return order;
}
int main()
{
    system("cls");
    cout << "welcome" << endl;
    cout << "please enter your choice" << endl;
    cout << "1.drinks" << endl;
    cout << "2.juice" << endl;
    cout << "3.dairy" << endl;
    cout << "4.tea" << endl;
    cin >> input;

    softdrinks *softdrinksObj = new softdrinks();
    dairy *dairyObj = new dairy();
    juice *juiceObj = new juice();
    coffe_tea *coffeeObj = new coffe_tea();

    system("cls");
    OrderInformation order;
    type_info *orderType = NULL;
    if (input == 1)
    {
        cout << softdrinksObj->getTitle("List of Soft Drinks") << endl;
        order = takeOrder(softdrinksObj->getOptions());
    }
    else if (input == 2)
    {
        cout << juiceObj->getTitle() << endl;
        order = takeOrder(juiceObj->getOptions());
    }
    else if (input == 3)
    {
        cout << dairyObj->getTitle() << endl;
        order = takeOrder(dairyObj->getOptions());
    }
    else if (input == 4)
    {
        cout << coffeeObj->getTitle() << endl;
        order = takeOrder(coffeeObj->getOptions(), false);
        orderType = const_cast<type_info *>(&typeid(coffeeObj));
    }

    system("cls");
    if (order.cancelled)
        cout << "You cancelled the order" << endl;
    else
    {
        cout << "Thank you for purchasing 🙂" << endl;
        cout << "You picked:" << endl;
        cout << order.drinkName << endl;
        if (orderType == &typeid(coffeeObj))
            cout << "Quantity: " << order.size << endl;
        else
            cout << "Size: " << order.size << endl;
        // cout << "TypeId: " << order.drinkTypeid << endl;
    }

    delete softdrinksObj;
    delete dairyObj;
    delete juiceObj;
    delete coffeeObj;

    return 0;
}