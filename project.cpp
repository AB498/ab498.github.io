#include <iostream>
#include <vector>

using namespace std;

class BaseClass
{
    string name;
    int credits;
    int creditHours;

public:
    string getName()
    {
        return name;
    }
    int getCredits()
    {
        return credits;
    }
    int getCreditHours()
    {
        return creditHours;
    }
    string getInfo()
    {
        return "Generic Course: No Info";
    }
    BaseClass(string n)
    {
        name = n;
    }
    BaseClass()
    {
    }
};
class DerivedClass : public BaseClass
{
public:
    string getInfo()
    {
        return "Name: " + getName() + "\nCredits: " + to_string(getCredits()) + "\nCredit Hours: " + to_string(getCreditHours());
    }
    DerivedClass(string n) : BaseClass(n)
    {
    }
};
vector<BaseClass *> list;
int input;

void showAllCourses()
{
    cout << "Showing all courses" << endl;
    for (int i = 0; i < list.size(); i++)
    {
        cout << i + 1 << ". " << list[i]->getName() << endl;
    }
    cin >> input;

    cout << list[input - 1]->getInfo();
}
void initializeCourses()
{
    DerivedClass *en = new DerivedClass("ENG-1010");
    list.push_back(en);
    cout << en->getInfo() << endl;
    cout << list[0]->getInfo() << endl;
    list.push_back(new BaseClass("CSE-1100"));
    list.push_back(new BaseClass("PHY-1200"));
}

int main()
{
    initializeCourses();
    string mainScreen = "Select an option \n"
                        "1. View all courses \n";
    cout << mainScreen;
    cin >> input;
    switch (input)
    {
    case 1:
        showAllCourses();
        break;
    case 2:
        showAllCourses();
        break;
    default:
        break;
    }
}