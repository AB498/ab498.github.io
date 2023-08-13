#include <iostream>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node(int d)
    {
        data = d;
        next = NULL;
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
        if (head == NULL)
        {
            Node *newNode = new Node(data);
            newNode->next = newNode;
            head = newNode;
            return newNode;
        }
        Node *temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        Node *newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        temp->next = head;
        return newNode;
    }
    Node *insertLast(int data)
    {
        if (head == NULL)
        {
            return insertFirst(data);
        }
        Node *temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        Node *newNode = new Node(data);

        temp->next = newNode;
        newNode->next = head;
        return newNode;
    }
    void insertAt(int index, int data)
    {
        if (head == NULL)
        {
            head = head->next;
            return;
        }
        Node *temp = head;
        Node *temp_prev = NULL;

        for (int i = 1; temp != NULL && i < index; i++)
        {
            temp_prev = temp;
            temp = temp->next;
        }

        Node *newNode = new Node(data);
        newNode->next = temp->next;
        temp->next = newNode;
    }
    void deleteFirst()
    {
        Node *temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        head = head->next;
        temp->next = head;
    }
    void deleteLast()
    {
        Node *temp = head;
        Node *temp_prev = NULL;
        while (temp->next != head)
        {
            temp_prev = temp;
            temp = temp->next;
        }
        temp_prev->next = head;
    }
    void deleteAt(int index)
    {
        if (head == NULL)
        {
            head = head->next;
            return;
        }
        Node *temp = head;
        Node *temp_prev = NULL;

        for (int i = 1; temp != NULL && i < index; i++)
        {
            temp_prev = temp;
            temp = temp->next;
        }
        if (temp == NULL)
        {
            return;
        }
        temp_prev->next = temp->next;
        delete temp;
    }
    void display()
    {
        Node *temp = head;
        do
        {
            cout << temp->data << "->";
            temp = temp->next;
        } while (temp != head);
    }
};

int main()
{
    CircularLinkedList c1;
    c1.insertFirst(5);
    c1.insertFirst(1);
    c1.insertFirst(6);
    c1.insertLast(9);
    c1.insertAt(2, 26);
    c1.display();
    cout << endl;
    c1.deleteFirst();
    c1.deleteLast();
    c1.deleteAt(2);
    c1.display();
    return 0;
}
