#ifndef STUDENT
#define STUDENT

#include <iostream>
using namespace std;

class Student
{
private:
    int id;
    string name;
    string department;
    double gpa;

public:
    Student(){};
    void create()
    {
        cout << "Enter your id:";
        cin >> id;
        cout << "Enter your name:";
        cin >> name;
        cout << "Enter your department:";
        cin >> department;
        cout << "Enter your gpa:";
        cin >> gpa;
    }
    int getId()
    {
        return id;
    }
    double getGPA()
    {
        return gpa;
    }
    string getDepartment()
    {
        return department;
    }
    void print()
    {
        cout << "Id: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "GPA: " << gpa << endl;
    }

    Student operator=(Student student)
    {
        this->id = student.id;
        this->name = student.name;
        this->department = student.department;
        this->gpa = student.gpa;
        return *this;
    }
};

#endif