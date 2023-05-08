#ifndef STUDENT
#define STUDENT

#include <iostream>
using namespace std;

class Student
{
private:
    int id;
    string name;
    string depratment;
    double gpa;
public:
    Student()
    {
        cout << "Enter your id:";
        cin >> id;
        cout << "Enter your name:";
        cin >> name;
        cout << "Enter your department:";
        cin >> department;
        cout << "Enter your gpa:";
        cin >> gpa;
    };
    int getId()
    {
        return id;
    };
    void print()
    {
        cout << "Id: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "GPA: " << gpa << endl;
    };
}

#endif