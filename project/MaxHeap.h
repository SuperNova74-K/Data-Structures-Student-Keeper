#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "Algorithm.h"
#include "Student.h"

class MaxHeap : public Algorithm
{
private:
    Student *students; // Dynamic array to store students
    int maxSize;       // Maximum size of the heap
    int currentSize;   // Current size of the heap

    void heapify(int i){
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (left < currentSize && students[left].getGPA() > students[largest].getGPA())
            largest = left;
        if (right < currentSize && students[right].getGPA() > students[largest].getGPA())
            largest = right;
        if (largest != i)
        {
            swap(students[i], students[largest]);
            heapify(largest);
        }
    };
    void swap(Student a, Student b){
        Student temp = a;
        a = b;
        b = temp;
    };

public:
    MaxHeap(){
        maxSize = 100;           // Set the maximum size of the heap
        students = new Student[maxSize]; // Create a dynamic array to store students
        currentSize = 0;         // Set the current size to 0
    };
    ~MaxHeap(){
        delete[] students; // Delete the dynamic array
    };

    void add(Student student){
        if (currentSize == maxSize)
        {
            std::cout << "Heap is full. Cannot add more students.\n";
            return;
        }

        students[currentSize] = student;
        int currentIndex = currentSize;
        currentSize++;

        // Move the added student up the heap to maintain the Max Heap property
        while (currentIndex > 0 && students[currentIndex].getId() > students[(currentIndex - 1) / 2].getId())
        {
            swap(students[currentIndex], students[(currentIndex - 1) / 2]);
            currentIndex = (currentIndex - 1) / 2;
        }
    };
    void remove(int id){
        // Find the index of the student with the specified ID
        int index = -1;
        for (int i = 0; i < currentSize; i++)
        {
            if (students[i].getId() == id)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            std::cout << "Student with ID " << id << " not found.\n";
            return;
        }

        // Replace the student with the last student in the heap
        students[index] = students[currentSize - 1];
        currentSize--;

        // Adjust the heap by heapifying the element at the removed student's index
        heapify(index);
    };
    void search(int id){
        for (int i = 0; i < currentSize; i++)
        {
            if (students[i].getId() == id)
            {
                std::cout << "Student with ID " << id << " found.\n";
                return;
            }
        }

    };
    void printAll(){
        for (int i = 0; i < currentSize; i++){
            std::cout << "Student " << i + 1 << ":\n";
            students[i].print();
        }
    };
};

#endif
