#include <iostream>
#include <string>
using namespace std;
class BaseClass
{
    string name;
    int credits;
    int creditHours;

public:
    int multiplier;
    BaseClass()
    {
        multiplier = 5;
    }
    BaseClass(int creds)
    {
        multiplier = 5;
        credits = creds;
    }
    int getCreditHours()
    {
        return credits * multiplier;
    }
    string getName()
    {
        return name;
    }
    void setName(string n)
    {
        name = n;
    }
    void setMultiplier(int m)
    {
        multiplier = m;
    }
    void setCredits(int c)
    {
        credits = c;
    }
    int getCredits()
    {
        return credits;
    }
    BaseClass operator+(BaseClass c)
    {
        return BaseClass(c.getCredits() + getCredits());
    }
};
class Mandatory
{
public:
    int isMandatory = 1;
};
class Optional
{
public:
    int isMandatory = 0;
};
// single inheritance
class CreditlessCourse : public BaseClass
{
public:
    CreditlessCourse(int c)
    {
        setMultiplier(0);
        setCredits(c);
    }
};
// single inheritance
class BaseCourse : public BaseClass
{
public:
    BaseCourse(int c)
    {
        setCredits(c);
    }
};
// multiple inheritance: Mandatory, BaseCourse > ENG_Course
// multi-level inheritance: Course > BaseCourse > ENG_Course
class ENG_Course : public Mandatory, public BaseCourse
{
public:
    ENG_Course(string n) : BaseCourse(10)
    {
        setName(n);
    }
};

int main()
{
    ENG_Course en = ENG_Course("ENG-1100");
    cout << en.getName() << endl;
    cout << (en + en + en).getCreditHours() << endl;
    return 0;
}
