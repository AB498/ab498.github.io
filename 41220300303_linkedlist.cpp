#include <iostream>

using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node *prev;
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
    Node *insertFirst(int data)
    {
        Node *newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        return newNode;
    }
    Node *insertLast(int data)
    {
        Node *newNode = new Node(data);
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        return newNode;
    }
    Node *insertAfter(Node *after, int data)
    {
        Node *newNode = new Node(data);
        Node *temp = head;
        while (temp != after)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        return newNode;
    }
    void deleteFirst()
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    void deleteLast()
    {
        Node *temp = head;
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
    }
    // 2 55 46 6 6
    void deleteMiddle(Node *someNode)
    {
        Node *temp = head;
        if (temp == someNode)
        {
            head = head->next;
            return;
        }
        while (temp->next != someNode)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
    }
    void print()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

class DoublyLinkedList
{
    Node *head;

public:
    DoublyLinkedList()
    {
        head = NULL;
    }
    Node *insertFirst(int data)
    {
        Node *newNode = new Node(data);
        newNode->next = head;
        newNode->prev = NULL;
        head = newNode;
        return newNode;
    }
    Node *insertLast(int data)
    {
        Node *newNode = new Node(data);
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
        return newNode;
    }
    Node *insertAfter(Node *after, int data)
    {
        Node *newNode = new Node(data);
        Node *temp = head;
        while (temp != after)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next = newNode;
        return newNode;
    }
    void deleteFirst()
    {
        head = head->next;
        head->prev = NULL;
    }
    void deleteLast()
    {
        Node *temp = head;
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
    }
    void deleteMiddle(Node *someNode)
    {
        Node *temp = head;
        if (temp == someNode)
        {
            head = head->next;
            head->prev = NULL;
            return;
        }
        while (temp->next != someNode)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        if (temp->next->next != NULL)
            temp->next->next->prev = temp;
    }
    void print()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

class CircularLinkedList
{
    Node *head;

public:
    CircularLinkedList()
    {
        head = NULL;
    }
    Node *insertFirst(int data)
    {
        Node *newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        return newNode;
    }
    Node *insertLast(int data)
    {
        Node *newNode = new Node(data);
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        return newNode;
    }
    Node *insertAfter(Node *after, int data)
    {
        Node *newNode = new Node(data);
        Node *temp = head;
        while (temp != after)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        return newNode;
    }
    void deleteFirst()
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    void deleteLast()
    {
        Node *temp = head;
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
    }
    void deleteMiddle(Node *someNode)
    {
        Node *temp = head;
        if (temp == someNode)
        {
            head = head->next;
            return;
        }
        while (temp->next != someNode)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
    }
    void display()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

int main()
{
    cout << "Singly Linked List" << endl;
    LinkedList singlyLL;
    singlyLL.insertFirst(1);
    Node *someNode = singlyLL.insertFirst(2);
    singlyLL.insertFirst(3);
    singlyLL.insertLast(4);
    singlyLL.insertLast(5);
    singlyLL.insertAfter(someNode, 6);
    singlyLL.deleteFirst();
    singlyLL.deleteLast();
    singlyLL.deleteMiddle(someNode);
    singlyLL.print();
    cout << endl;

    cout << "Doubly Linked List" << endl;
    DoublyLinkedList doublyLL;
    doublyLL.insertFirst(1);
    Node *someNode2 = doublyLL.insertFirst(2);
    doublyLL.insertFirst(3);
    doublyLL.insertLast(4);
    doublyLL.insertLast(5);
    doublyLL.insertAfter(someNode2, 6);
    doublyLL.deleteFirst();
    doublyLL.deleteLast();
    doublyLL.deleteMiddle(someNode2);
    doublyLL.print();
    cout << endl;

    cout << "Circular Linked List" << endl;
    CircularLinkedList circularLL;
    circularLL.insertFirst(1);
    Node *someNode3 = circularLL.insertFirst(2);
    circularLL.insertFirst(3);
    circularLL.insertLast(4);
    circularLL.insertLast(5);
    circularLL.insertAfter(someNode3, 6);
    circularLL.deleteFirst();
    circularLL.deleteLast();
    circularLL.deleteMiddle(someNode3);
    circularLL.display();
    return 0;
}