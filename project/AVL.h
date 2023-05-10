#ifndef __AVL__
#define __AVL__
#include "algorithm.h"
#include <map>
using namespace std;

class AVL : public Algorithm
{
private:
    class Node
    {
    public:
        Student student;
        Node *left;
        Node *right;
        int height;
        Node(Student student)
        {
            this->student = student;
            this->left = NULL;
            this->right = NULL;
            this->height = 1;
        }
    };

    int heightOf(Node *node)
    {
        if (node == NULL)
            return 0;
        return node->height;
    }

    int balanceFactor(Node *node)
    {
        if (node == NULL)
            return 0;
        return heightOf(node->left) - heightOf(node->right);
    }

    void updateHeight(Node *node)
    {
        node->height = 1 + max(heightOf(node->left), heightOf(node->right));
    }

    Node *rightRotate(Node *node)
    {
        Node *leftNode = node->left;
        Node *leftRightNode = leftNode->right;
        leftNode->right = node;
        node->left = leftRightNode;
        updateHeight(node);
        updateHeight(leftNode);
        return leftNode;
    }

    Node *leftRotate(Node *node)
    {
        Node *rightNode = node->right;
        Node *rightLeftNode = rightNode->left;
        rightNode->left = node;
        node->right = rightLeftNode;
        updateHeight(node);
        updateHeight(rightNode);
        return rightNode;
    }

    Node *insert(Node *node, Student student)
    {
        if (node == NULL)
        {
            return new Node(student);
        }

        if (student.getId() < node->student.getId())
        {
            node->left = insert(node->left, student);
        }
        else if (student.getId() > node->student.getId())
        {
            node->right = insert(node->right, student);
        }
        else
        {
            return node;
        }
        updateHeight(node);
        int bf = balanceFactor(node);
        // Left-Left rotation
        if (bf > 1 && balanceFactor(node->left) >= 0)
        {
            return rightRotate(node);
        }
        // Right-Right rotation
        if (bf < -1 && balanceFactor(node->right) <= 0)
        {
            return leftRotate(node);
        }
        // Left-Right rotation
        if (bf > 1 && balanceFactor(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right-Left rotation
        if (bf < -1 && balanceFactor(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(Node *node)
    {
        if (node != NULL)
        {
            inorder(node->left);
            node->student.print();
            cout << "--------------------------\n";
            inorder(node->right);
        }
    }

    Node *getLowestSuccessor(Node *node)
    {
        Node *current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }

    Node *deleteNode(Node *node, Student student)
    {
        if (node == NULL)
        {
            return node;
        }
        if (student.getId() < node->student.getId())
        {
            node->left = deleteNode(node->left, student);
        }
        else if (student.getId() > node->student.getId())
        {
            node->right = deleteNode(node->right, student);
        }
        else
        {
            if ((node->left == NULL) || (node->right == NULL))
            {
                Node *childNode = node->left ? node->left : node->right;
                if (childNode == NULL)
                {
                    childNode = node;
                    node = NULL;
                }
                else
                {
                    *node = *childNode;
                }
                free(childNode);
            }
            else
            {
                Node *rightLowestSuccessor = getLowestSuccessor(node->right);
                node->student = rightLowestSuccessor->student;
                node->right = deleteNode(node->right, rightLowestSuccessor->student);
            }
        }
        if (node == NULL)
        {
            return node;
        }
        updateHeight(node);
        int bf = balanceFactor(node);
        // Left-Left rotation
        if (bf > 1 && balanceFactor(node->left) >= 0)
        {
            return rightRotate(node);
        }
        // Left-Right rotation
        if (bf > 1 && balanceFactor(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right-Right rotation
        if (bf < -1 && balanceFactor(node->right) <= 0)
        {
            return leftRotate(node);
        }
        // Right-Left rotation
        if (bf < -1 && balanceFactor(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node *searchNode(Node *node, int id)
    {
        if (node == NULL || node->student.getId() == id)
        {
            return node;
        }
        if (node->student.getId() < id)
        {
            return searchNode(node->right, id);
        }
        return searchNode(node->left, id);
    }

    void printDepartmentCount()
    {
        for (auto department : departmentCount)
        {
            cout << department.first << " => " << department.second << '\n';
        }
    }

    Node *root = NULL;
    map<string, int> departmentCount;

public:
    void add(Student student);
    void remove(int id);
    void search(int id);
    void printAll();
};

void AVL::add(Student student)
{
    departmentCount[student.getDepartment()]++;
    root = insert(root, student);
}

void AVL::printAll()
{
    inorder(root);
    cout << "##########################\n";
    printDepartmentCount();
}

void AVL::remove(int id)
{
    Node *node = searchNode(root, id);
    if (node == NULL)
    {
        return;
    }
    departmentCount[node->student.getDepartment()]--;
    root = deleteNode(root, node->student);
}

void AVL::search(int id)
{
    Node *node = searchNode(root, id);
    if (node == NULL)
    {
        cout << "Student not found\n";
    }
    else
    {
        node->student.print();
    }
}

#endif