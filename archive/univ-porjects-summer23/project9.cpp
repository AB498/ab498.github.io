#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student
{
private:
    string name;
    int rollNumber;
    float marks;

public:
    // Constructor
    Student(string &studentName, int studentRollNumber, float studentMarks)
        : name(studentName), rollNumber(studentRollNumber), marks(studentMarks) {}

    // Member functions to get information
    string getName()
    {
        return name;
    }

    int getRollNumber()
    {
        return rollNumber;
    }

    float getMarks()
    {
        return marks;
    }

    void setName(string n)
    {
        name = n;
    }
    void setName()
    {
        name = "No Name";
    }
    void setRollNumber(int roll)
    {
        rollNumber = roll;
    }

    void setMarks(float m)
    {
        marks = m;
    }

    // Member function to display student information
    virtual void display()
    {
        cout << "Name: " << name << "\n";
        cout << "Roll Number: " << rollNumber << "\n";
        cout << "Marks: " << marks << "\n";
    }
};

class SchoolStudent : public Student
{
public:
    SchoolStudent(string studentName, int studentRollNumber, float studentMarks) : Student(studentName, studentRollNumber, studentMarks)
    {
    }
    void display()
    {
        cout << "School student\n";
        cout << "Name: " << getName() << "\n";
        cout << "Roll Number: " << getRollNumber() << "\n";
        cout << "Marks: " << getMarks() << "\n";
    }
};

class CollegeStudent : public Student
{
public:
    CollegeStudent(string studentName, int studentRollNumber, float studentMarks) : Student(studentName, studentRollNumber, studentMarks)
    {
    }
    void display()
    {
        cout << "College student\n";
        cout << "Name: " << getName() << "\n";
        cout << "Roll Number: " << getRollNumber() << "\n";
        cout << "Marks: " << getMarks() << "\n";
    }
};

class UniversityStudent : public Student
{
public:
    UniversityStudent(string studentName, int studentRollNumber, float studentMarks) : Student(studentName, studentRollNumber, studentMarks)
    {
    }
    void display()
    {
        cout << "University student\n";
        cout << "Name: " << getName() << "\n";
        cout << "Roll Number: " << getRollNumber() << "\n";
        cout << "Marks: " << getMarks() << "\n";
    }
};

class StudentManagementSystem
{
private:
    vector<SchoolStudent> schoolStudents;
    vector<CollegeStudent> collegeStudents;
    vector<UniversityStudent> universityStudents;

public:
    // Member function to add a student to the system
    void addSchoolStudent(SchoolStudent student)
    {
        schoolStudents.push_back(student);
    }
    void addCollegeStudent(CollegeStudent student)
    {
        collegeStudents.push_back(student);
    }
    void addUniversityStudent(UniversityStudent student)
    {
        universityStudents.push_back(student);
    }

    // Member function to display all student information
    void displayAllStudents()
    {
        for (SchoolStudent &student : schoolStudents)
        {
            student.display();
            cout << "-------------------------\n";
        }
    }
    void displayAllCollegeStudents()
    {
        for (CollegeStudent &student : collegeStudents)
        {
            student.display();
            cout << "-------------------------\n";
        }
    }
    void displayAllUniversityStudents()
    {
        for (UniversityStudent &student : universityStudents)
        {
            student.display();
            cout << "-------------------------\n";
        }
    }
};

int main()
{

    // Displaying all students
    cout << "Student Management System\n";
    cout << "-------------------------\n";
    StudentManagementSystem management;

    // Adding students to the system
    management.addSchoolStudent(SchoolStudent("rakib", 101, 95.5));
    management.addSchoolStudent(SchoolStudent("samin", 102, 87.0));
    management.addSchoolStudent(SchoolStudent("ramjun", 103, 78.5));

    management.addCollegeStudent(CollegeStudent("rakib", 101, 95.5));
    management.addCollegeStudent(CollegeStudent("samin", 102, 87.0));
    management.addCollegeStudent(CollegeStudent("ramjun", 103, 78.5));

    management.addUniversityStudent(UniversityStudent("zubaer", 101, 95.5));
    management.addUniversityStudent(UniversityStudent("samin", 102, 87.0));
    management.addUniversityStudent(UniversityStudent("ramjun", 103, 78.5));

    // getch ();

    cout << "Enter option: \n"
            "1. Display all school students\n"
            "2. Display all college students\n"
            "3. Display all university students\n";

    int input;

    cin >> input;

    if (input == 1)
    {
        management.displayAllStudents();
    }
    else if (input == 2)
    {
        management.displayAllCollegeStudents();
    }
    else if (input == 3)
    {
        management.displayAllUniversityStudents();
    }
}