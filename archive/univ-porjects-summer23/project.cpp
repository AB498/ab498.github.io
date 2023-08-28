#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BaseCourse
{
private:
    string name;
    int credits = 1;
    int creditHours;
    int cost = 1000;

public:
    string getName() // getter function
    {
        return name;
    }
    int getCost()
    {
        return cost;
    }
    int getCost(int scholarshipPercentage) // function overload
    {
        return cost * (100 - scholarshipPercentage) / 100;
    }
    void setCost(int c) // setter function
    {
        cost = c;
    }
    int getCredits()
    {
        return credits;
    }
    void setCredits(int cred)
    {
        credits = cred;
    }
    int getCreditHours()
    {
        return credits * 3;
    }
    virtual string getInfo() // to be overridden
    {
        return "Name: " + getName() + "\nCredits: " + to_string(getCredits()) + "\nCredit Hours: " + to_string(getCreditHours());
    }
    ~BaseCourse() // destructor
    {
        // cout << "Memory freed for " << name << endl;
    }
    BaseCourse() {}                // default constructor
    BaseCourse(BaseCourse &course) // copy constructor
    {
        name = course.getName();
        credits = course.getCredits();
        creditHours = course.getCreditHours();
        cost = course.getCost();
    }
    BaseCourse(string name) // parameterized constructor
    {
        this->name = name;
    }
    BaseCourse operator+(BaseCourse &course) // operator overload
    {
        BaseCourse temp = BaseCourse();
        temp.cost = course.getCost() + this->getCost();
        temp.name = this->getName() + (this->getName() != "" ? " + " : "") + course.getName();
        return temp;
    }
    friend void setCredits(BaseCourse *&course, int credits);
};

int input;
vector<BaseCourse *> courses; // array of all courses

void setCredits(BaseCourse *&course, int credits) // friend function
{
    course->credits = credits;
}
class MandatoryFeature
{
public:
    MandatoryFeature(BaseCourse *c)
    {
        setCredits(c, 1); // mandatory, so credits=1
    }
};
class OptionalFeature
{
public:
    OptionalFeature(BaseCourse *c)
    {
        setCredits(c, 0); // no credits for optional
    }
};
class ENGCourse : public BaseCourse
{
public:
    string getInfo() // function override
    {
        return "Name: " + getName() + "\nCredits: " + to_string(getCredits()) + "\nCredit Hours: " + to_string(getCreditHours());
    }
    ENGCourse(string n) : BaseCourse(n)
    {
    }
};
class CSECourse : public BaseCourse
{
public:
    CSECourse(string n) : BaseCourse(n)
    {
    }
};
class PHYCourse : public BaseCourse
{
public:
    PHYCourse(string n) : BaseCourse(n)
    {
    }
};
class ENG1010 : public ENGCourse, public MandatoryFeature
{
public:
    ENG1010() : ENGCourse("ENG-1010"), MandatoryFeature(this)
    {
    }
};
class CSE1100 : public CSECourse, public MandatoryFeature
{
public:
    CSE1100() : CSECourse("CSE-1100"), MandatoryFeature(this)
    {
    }
};
class PHY1200 : public PHYCourse, public OptionalFeature
{
public:
    PHY1200() : PHYCourse("PHY-1200"), OptionalFeature(this)
    {
    }
};

void initializeCourses()
{
    courses.push_back(new ENG1010());
    courses.push_back(new CSE1100());
    courses.push_back(new PHY1200());
}
void deleteCourses()
{
    delete courses[0];
    delete courses[1];
    delete courses[2];
}
void showAllCourses()
{
    system("cls");
    cout << "Showing all courses" << endl;
    for (int i = 0; i < courses.size(); i++)
    {
        cout << i + 1 << ". " << courses[i]->getName() << endl;
    }
    cin >> input;
    system("cls");
    if (input < 1 || input > 3)
    {
        cout << "Invalid option" << endl;
        return;
    }
    cout << courses[input - 1]->getInfo() << endl;
}

void calculateCost()
{
    system("cls");
    cout << "Showing all courses" << endl;
    int i;
    for (i = 0; i < courses.size(); i++)
    {
        cout << i + 1 << ". " << courses[i]->getName() << endl;
    }
    cout << i + 1 << ". All" << endl; // option 4: all

    cin >> input;
    if (input < 1 || input > 4)
    {
        cout << "Invalid option" << endl;
        return;
    }
    if (input == 4) // option 4: all
    {
        BaseCourse course = BaseCourse();
        course.setCost(0);
        for (int i = 0; i < courses.size(); i++)
        {
            course = course + *courses[i];
        }
        cout << "Total cost for " << course.getName() << ": " << course.getCost() << " BDT" << endl;
    }
    else
    {
        cout << "Total cost for " << courses[input - 1]->getName() << ": " << courses[input - 1]->getCost() << " BDT" << endl;
    }
}
void viewScholarshipApplied()
{
    system("cls");
    cout << "Enter scholarship percentage: " << endl;
    int scholarshipPercentage;
    cin >> scholarshipPercentage;
    system("cls");
    cout << "Showing all courses" << endl;
    for (int i = 0; i < courses.size(); i++)
    {
        cout << i + 1 << ". " << courses[i]->getName() << ": " << courses[i]->getCost() << " BDT -> " << courses[i]->getCost(scholarshipPercentage) << " BDT" << endl;
    }
}
void calculateCreditHours()
{
    system("cls");
    cout << "Showing all courses" << endl;
    int i;
    for (i = 0; i < courses.size(); i++)
    {
        cout << i + 1 << ". " << courses[i]->getName() << endl;
    }
    cout << i + 1 << ". All" << endl; // option 4: all

    int credHours = 0;
    cin >> input;
    if (input < 1 || input > 4)
    {
        cout << "Invalid option" << endl;
        return;
    }
    if (input == 4) // option 4: all
    {
        for (int i = 0; i < courses.size(); i++)
        {
            credHours = credHours + courses[i]->getCreditHours();
            cout << "Credit hours for " << courses[i]->getName() << (courses[i]->getCredits() == 0 ? " (Optional)" : " (Mandatory)")
                 << ": " << courses[i]->getCreditHours() << endl; // getCost is overloaded function
        }
    }
    else
    {
        cout << "Credit hours for " << courses[input - 1]->getName() << (courses[input - 1]->getCredits() == 0 ? " (Optional)" : " (Mandatory)")
             << ": " << courses[input - 1]->getCreditHours() << endl;
    }
    cout << "Total credit hours: " << credHours << endl;
}
inline void homeScreen()
{
    system("cls");
    cout << "Select an option \n"
            "1. View all courses \n"
            "2. Add course costs \n"
            "3. Calculate credit hours \n"
            "4. View with scholarship \n"
            "5. Exit\n";
    cin >> input;
    switch (input)
    {
    case 1:
        showAllCourses();
        break;
    case 2:
        calculateCost();
        break;
    case 3:
        calculateCreditHours();
        break;
    case 4:
        viewScholarshipApplied();
        break;
    case 5:
        deleteCourses(); // delete keyword
        exit(0);
        break;
    default:
        cout << endl
             << "Invalid Option";
        deleteCourses(); // delete keyword
        exit(0);
        break;
    }
    cout << endl
         << "Press Enter to return to Home Screen" << endl;
    cin.ignore();
    getchar();
    homeScreen();
}

int main()
{
    initializeCourses(); // dynamic memory allocation
    homeScreen();        // inline function
    cin.ignore();
    getchar();
}