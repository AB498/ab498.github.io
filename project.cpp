#include <iostream>
#include <vector>
#include <string>

using namespace std;

void renderHomeScreen();

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
    friend void setCredits(BaseCourse &course, int credits);
};
void setCredits(BaseCourse *&course, int credits)
{
    course->setCredits(credits);
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

void displayCources()
{
    system("cls");
    cout << "Showing all courses" << endl;
    for (int i = 0; i < courses.size(); i++)
    {
        cout << i + 1 << ". " << courses[i]->getName() << endl;
    }
}
void showAllCourses()
{
    displayCources();
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
vector<int> getInputArray()
{
    vector<int> arr;
    string input;
    cin.ignore();
    getline(cin, input);
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == ' ')
        {
            continue;
        }
        int index = input[i] - '0';
        arr.push_back(index);
    }
    return arr;
}
void addCourseCosts()
{
    displayCources();
    cout << "Type a space-seperated list of courses: " << endl;
    vector<int> input = getInputArray();

    BaseCourse course = BaseCourse();
    course.setCost(0);
    for (int i = 0; i < input.size(); i++)
        course = course + *courses[input[i] - 1];
    system("cls");
    cout << "Total cost for " << course.getName() << ": " << course.getCost() << " BDT" << endl;
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
        cout << i + 1 << ". " << courses[i]->getName() << ": " << courses[i]->getCost() << " -> " << courses[i]->getCost() * (100 - scholarshipPercentage) / 100 << endl;
    }
}
void calculateCreditHours()
{
    displayCources();
    cout << "Type a space-seperated list of courses: " << endl;
    vector<int> input = getInputArray();

    system("cls");
    int credHours = 0;
    for (int i = 0; i < input.size(); i++)
    {
        credHours = credHours + courses[input[i] - 1]->getCreditHours();
        cout << "Credit hours for " << courses[input[i] - 1]->getName() << (courses[input[i] - 1]->getCredits() == 0 ? " (Optional)" : " (Mandatory)")
             << ": " << courses[input[i] - 1]->getCreditHours() << endl;
    }
    cout << "Total credit hours: " << credHours << endl;
}
void renderHomeScreen()
{
    system("cls");
    string mainScreen = "Select an option \n"
                        "1. View all courses \n"
                        "2. Add course costs \n"
                        "3. Calculate credit hours \n"
                        "4. View with scholarship \n";
    cout << mainScreen;
    cin >> input;
    switch (input)
    {
    case 1:
        showAllCourses();
        break;
    case 2:
        addCourseCosts();
        break;
    case 3:
        calculateCreditHours();
        break;
    case 4:
        viewScholarshipApplied();
        break;
    default:
        break;
    }
    cout << endl
         << "Press Enter to return to Home Screen" << endl;
    cin.ignore(); // Clear any residual characters from the input buffer
    getchar();
    renderHomeScreen();
}

int main()
{
    initializeCourses();
    renderHomeScreen();
    cin.ignore(); // Clear any residual characters from the input buffer
    getchar();
}