#ifndef __AVL__
#define __AVL__
#include "algorithm.h"
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

    int balanceFactor(Node *node)
    {
        if (node == NULL)
            return 0;
        return node->left->height - node->right->height;
    }

    void updateHeight(Node *node)
    {
        node->height = 1 + max(node->left->height, node->right->height);
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
            return new Node(student);

        if (student.getId() < node->student.getId())
            node->left = insert(node->left, student);
        else if (student.getId() > node->student.getId())
            node->right = insert(node->right, student);
        else // Duplicate keys not allowed
            return node;
        updateHeight(node);
        int bf = balanceFactor(node);

        // Left-Left case
        if (bf > 1 && student.getId() < node->left->student.getId())
            return rightRotate(node);

        // Right-Right case
        if (bf < -1 && student.getId() > node->right->student.getId())
            return leftRotate(node);

        // Left-Right case
        if (bf > 1 && student.getId() > node->left->student.getId())
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right-Left case
        if (bf < -1 && student.getId() < node->right->student.getId())
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node *root = NULL;

public:
    void add(Student student);
    void remove(int id){};
    void search(int id){};
    void printAll(){};
};

void
AVL::add(Student student)
{
    insert(root, student);
}

#endif