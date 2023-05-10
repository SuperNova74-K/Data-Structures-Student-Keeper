#ifndef ALGORITHM
#define ALGORITHM

#include <iostream>
#include "Student.h"
using namespace std;

class Algorithm
{
public:
    virtual void add(Student student){}
    virtual void remove(int id){}
    virtual void search(int id){}
    virtual void printAll(){}
};

#endif