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
    string getName()
    {
        return name;
    }
    int getCost()
    {
        return cost;
    }
    int getCost(int scholarshipPercentage)
    {
        return cost * (100 - scholarshipPercentage) / 100;
    }
    void setCost(int c)
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
    virtual string getInfo()
    {
        return "Name: " + getName() + "\nCredits: " + to_string(getCredits()) + "\nCredit Hours: " + to_string(getCreditHours());
    }
    BaseCourse(string n)
    {
        name = n;
    }
    ~BaseCourse()
    {
        // cout << "Memory freed for " << name << endl;
    }
    BaseCourse() {}
    BaseCourse(BaseCourse &course)
    {
        name = course.getName();
        credits = course.getCredits();
        creditHours = course.getCreditHours();
        cost = course.getCost();
    }
    BaseCourse operator+(BaseCourse &course)
    {
        BaseCourse temp = BaseCourse();
        temp.cost = course.getCost() + this->getCost();
        temp.name = this->getName() + (this->getName() != "" ? " + " : "") + course.getName();
        return temp;
    }
    friend void setCredits(BaseCourse *&course, int credits);
};
void setCredits(BaseCourse *&course, int credits)
{
    course->credits = credits;
}
class MandatoryFeature
{
public:
    MandatoryFeature(BaseCourse *c)
    {
        setCredits(c, 1);
    }
};
class OptionalFeature
{
public:
    OptionalFeature(BaseCourse *c)
    {
        setCredits(c, 0);
    }
};
class ENGCourse : public BaseCourse
{
public:
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
vector<BaseCourse *> courses;
int input;

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
    cout << courses[input - 1]->getInfo() << endl;
}
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

void calculateCost()
{
    system("cls");
    cout << "Showing all courses" << endl;
    int i;
    for (i = 0; i < courses.size(); i++)
    {
        cout << i + 1 << ". " << courses[i]->getName() << endl;
    }
    cout << i + 1 << ". All" << endl;

    cin >> input;
    if (input == 4)
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
    cout << i + 1 << ". All" << endl;

    int credHours = 0;
    cin >> input;
    if (input == 4)
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
    string mainScreen = "Select an option \n"
                        "1. View all courses \n"
                        "2. Add course costs \n"
                        "3. Calculate credit hours \n"
                        "4. View with scholarship \n"
                        "5. Exit\n";
    cout << mainScreen;
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
        deleteCourses();
        exit(0);
        break;
    default:
        cout << endl
             << "Invalid Option";
        deleteCourses();
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
    initializeCourses();
    homeScreen(); // inline function
    cin.ignore();
    getchar();
}