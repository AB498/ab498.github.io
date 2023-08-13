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
            newNode->next = NULL;
            head = newNode;
            return newNode;
        }
        Node *newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        return newNode;
    }
    Node *insertLast(int data)
    {
        if (head == NULL)
        {
            return insertFirst(data);
        }
        Node *newNode = new Node(data);
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
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
        if (temp == NULL)
        {
            return;
        }
        temp_prev->next = temp->next;
        delete temp;
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
    CircularLinkedList circularLinkedList;
    cout << "Insertion" << endl;
    circularLinkedList.insertFirst(64);
    circularLinkedList.insertFirst(26);
    circularLinkedList.insertFirst(92);
    circularLinkedList.insertLast(43);
    circularLinkedList.insertLast(55);
    circularLinkedList.insertAt(3, 62);
    circularLinkedList.display();
    cout << "Deletion" << endl;
    circularLinkedList.deleteFirst();
    circularLinkedList.deleteLast();
    circularLinkedList.deleteAt(3);
    circularLinkedList.display();

    return 0;
}
