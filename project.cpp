#include <iostream>
#include <vector>

using namespace std;

class Course
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
    Course(string n)
    {
        name = n;
    }
    Course()
    {
    }
};
class EnglishCourse : public Course
{
public:
    EnglishCourse(string n) : Course(n)
    {
    }
    string getInfo()
    {
        return "Name: " + getName() + "\nCredits: " + to_string(getCredits()) + "\nCredit Hours: " + to_string(getCreditHours());
    }
};
vector<Course> courses;
int input;

void showAllCourses()
{
    cout << "Showing all courses" << endl;
    for (int i = 0; i < courses.size(); i++)
    {
        cout << i + 1 << ". " << courses[i].getName() << endl;
    }
    cin >> input;

    cout << courses[input - 1].getInfo();
}
void initializeCourses()
{
    courses.push_back(EnglishCourse("ENG-1010"));
    courses.push_back(Course("CSE-1100"));
    courses.push_back(Course("PHY-1200"));
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