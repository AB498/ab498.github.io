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
    void insertAfter(int data, int after)
    {
        Node *newNode = new Node(data);
        Node *temp = head;
        while (temp->data != after)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
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
    void deleteMiddle(int at)
    {
        Node *temp = head;
        while (temp->next->data != at)
        {
            temp = temp->next;
        }
        Node *temp2 = temp->next;
        temp->next = temp->next->next;
        delete temp2;
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
    void insertFirst(int data)
    {
        Node *newNode = new Node(data);
        newNode->next = head;
        newNode->prev = NULL;
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
        newNode->prev = temp;
    }
    void insertAfter(int data, int after)
    {
        Node *newNode = new Node(data);
        Node *temp = head;
        while (temp->data != after)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next = newNode;
    }
    void deleteFirst()
    {
        Node *temp = head;
        head = head->next;
        head->prev = NULL;
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
    void deleteMiddle(int at)
    {
        Node *temp = head;
        while (temp->next->data != at)
        {
            temp = temp->next;
        }
        Node *temp2 = temp->next;
        temp->next = temp->next->next;
        if (temp->next != NULL)
            temp->next->prev = temp;
        delete temp2;
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
    void insertAfter(int data, int after)
    {
        Node *newNode = new Node(data);
        Node *temp = head;
        while (temp->data != after)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
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
    void deleteMiddle(int at)
    {
        Node *temp = head;
        while (temp->next->data != at)
        {
            temp = temp->next;
        }
        Node *temp2 = temp->next;
        temp->next = temp->next->next;
        delete temp2;
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

int main()
{
    cout << "Single Linked List" << endl;
    LinkedList list;
    list.insertFirst(1);
    list.insertFirst(2);
    list.insertFirst(3);
    list.insertLast(4);
    list.insertLast(5);
    list.insertAfter(6, 3);
    list.print();
    list.deleteFirst();
    list.deleteLast();
    list.deleteMiddle(4);
    list.print();

    cout << "Double Linked List" << endl;
    DoublyLinkedList dlist;
    dlist.insertFirst(1);
    dlist.insertFirst(2);
    dlist.insertFirst(3);
    dlist.insertLast(4);
    dlist.insertLast(5);
    dlist.insertAfter(6, 3);
    dlist.print();
    dlist.deleteFirst();
    dlist.deleteLast();
    dlist.deleteMiddle(4);
    dlist.print();

    cout << "Circular Linked List" << endl;
    CircularLinkedList clist;
    clist.insertFirst(1);
    clist.insertFirst(2);
    clist.insertFirst(3);
    clist.insertLast(4);
    clist.insertLast(5);
    clist.insertAfter(6, 3);
    clist.print();
    clist.deleteFirst();
    clist.deleteLast();
    clist.deleteMiddle(4);
    clist.print();
    return 0;
}