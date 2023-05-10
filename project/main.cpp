#include "algorithm.h"

Algorithm *algorithm;

void BSTAndAVLMenu()
{
    cout << "What do you want to do?\n";
    cout << "1- Add student\n";
    cout << "2- Remove student\n";
    cout << "3- Search for a student\n";
    cout << "4- Print all students\n";
    cout << "5- Return to main menu\n";
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        Student student;
        student.create();
        algorithm->add(student);
        break;
    case 2:
        int id;
        cout << "Enter the id of the student you want to remove: ";
        cin >> id;
        algorithm->remove(id);
        break;
    case 3:
        cout << "Enter the id of the student you want to search for: ";
        cin >> id;
        algorithm->search(id);
        break;
    case 4:
        algorithm->printAll();
        break;
    case 5:
        return;
        break;
    }
    BSTAndAVLMenu();
}

void minAndMaxHeapMenu()
{
    cout << "What do you want to do?\n";
    cout << "1- Add student\n";
    cout << "4- Print all students\n";
    cout << "5- Return to main menu\n";
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        Student student;
        student.create();
        algorithm->add(student);
        break;
    case 2:
        algorithm->printAll();
        break;
    case 3:
        return;
        break;
    }
    minAndMaxHeapMenu();
}

void printAlgoirthmsMenu()
{
    cout << "Choose the algorithm you want to use: " << '\n';
    cout << "1- BST\n";
    cout << "2- AVL\n";
    cout << "3- Min Heap\n";
    cout << "4- Max Heap\n";
    cout << "5- Exit\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        algorithm = new BST();
        BSTAndAVLMenu();
        break;
    case 2:
        algorithm = new AVL();
        BSTAndAVLMenu();
        break;
    case 3:
        algorithm = new MinHeap();
        minAndMaxHeapMenu();
        break;
    case 4:
        algorithm = new MaxHeap();
        minAndMaxHeapMenu();
        break;
    case 5:
        return;
        break;
    }
}

int main()
{
    printAlgoirthmsMenu();
}
