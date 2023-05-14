#ifndef __BST__
#define __BST__

#include <unordered_map>
#include "Algorithm.h"
#include "stack"
using namespace std;

/**
 * @author Khaled Waleed Salah
 * @date 12-May-2023
 * @Purpose Binary Search Tree to save students records and access them using IDs
 * @Interface add (Student), remove(id), search(id), printAll()
 */
class BST : public Algorithm
{
private:
    class Node{
    public:
        Node* right = nullptr;
        Node* left = nullptr;
        Student value;

        explicit Node(const Student & student) : value(student){}


    };

    Node * root = nullptr;

    /**
     * @param head: the root of the sub-tree you want to get the minimum of
     */
    static Node* minNodeStartingAt(Node* head){
        while (head and head->left)
            head = head->left;
        return head;
    }

    /**
     * @param id id of the student you want to remove
     * @param head the head of the tree you want to remove student with id from.
     * @returns the root of the sub-tree whose root was (maybe still) head but after removing the student with id of id
     */
    Node* remove(int id, Node* head){
        if(not head)
            return nullptr;

        if(id < head->value.getId()){
            head->left = remove(id, head->left);
        }else if(id > head->value.getId()){
            head->right = remove(id, head->right);
        }else{ // we have reached the node we want to remove

            Node* originalPlaceOfHead = head; // keeping the place of head, so we can later delete it if needed

            if(not head->left and not head->right){
                head = nullptr;

            }else if(not head->right){ // this means there must be a left node.
                head = head->left;

            }else if(not head->left){ // this means there must be a right node
                head = head->right;
            }else{
                // getting here means that there is 2 children for head (head)
                Node* mn = minNodeStartingAt(head->right);
                head->value = mn->value;
                head->right = remove(mn->value.getId(), head->right);

                originalPlaceOfHead = nullptr;
            }

            if(originalPlaceOfHead)
                delete originalPlaceOfHead;
        }
        return head;
    }

public:
    /**
     * @param student the student you want to add
     */
    void add(Student student) override{
        Node * head = root;
        if(not root){
            root = new Node(student);
            return;
        }

        while(true){
            if(student.getId() < head->value.getId()){
                if(head->left)
                    head = head->left;
                else{
                    head->left = new Node(student);
                    return;
                }

            }else if(student.getId() > head->value.getId()){
                if(head->right)
                    head = head->right;
                else{
                    head->right = new Node(student);
                    return;
                }
            }
        }
    };

    void remove(int id){
        root = remove(id, root);
    }

    void search(int id){
        Node * head = root;
        if(not head){
            return;
        }

        while(true){
            if(not head)
                return;

            if(id < head->value.getId()){
                head = head->left;
            }else if(id > head->value.getId()){
                head = head->right;
            }else{
                head->value.print();
                return;
            }
        }
    }

    void printAll(){
        Node * head = root;
        if(not root)
            return;

        stack<Node *>stk;
        unordered_map<string, int> departments;

        while(not stk.empty() or head){
            if(head){
                stk.push(head);
                head = head->left;
            }else{
                stk.top()->value.print();
                departments[stk.top()->value.getDepartment()]++;
                cout << endl;
                cout << "_______________________";
                cout << endl;
                head = stk.top()->right;
                stk.pop();
            }
        }

        cout << "Department Name   ->  Number Of Students" << endl;
        for(auto & department : departments){
            cout << department.first << " -> " << department.second << endl;
        }

        cout << endl << "_______________________" << endl;

    }

    ~BST(){
        Node * head = root;
        if(not root)
            return;

        stack<Node *>stk;

        while(not stk.empty() or head){
            if(head){
                stk.push(head);
                head = head->left;
            }else{
                Node * temp = stk.top();
                stk.pop();
                head = temp->right;
                delete temp;
            }
        }
    }
};

#endif