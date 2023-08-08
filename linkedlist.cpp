#include <iostream>

using namespace std;
class Node
{
    int data;

public:
    Node *next;
    Node(int d)
    {
        data = d;
        next = NULL;
    }
};
class LinkedList
{
    Node *head;

public:
    LinkedList()
    {
        head = NULL;
    }
    void insertFirst(int data)
    {
        Node *newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }
    void insertLast(int data)
    {
        Node *newNode = new Node(data);
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
};

int main()
{
    LinkedList list;
    list.insertFirst(1);
    list.insertFirst(2);
}