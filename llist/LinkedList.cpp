#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int value)
    {
        data = value;
        next = NULL;
    }
};

class LinkedList
{
private:
    Node *head;

public:
    LinkedList()
    {
        head = NULL;
    }

    void insertFirst(int value)
    {
        Node *newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void insertLast(int value)
    {
        Node *newNode = new Node(value);
        if (head == NULL)
        {
            head = newNode;
            return;
        }

        Node *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    void insertMiddle(int value, int position)
    {
        Node *newNode = new Node(value);
        if (head == NULL || position <= 1)
        {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node *temp = head;
        int count = 1;
        while (temp != NULL && count < position - 1)
        {
            temp = temp->next;
            count++;
        }

        if (temp != NULL)
        {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    void deleteFirst()
    {
        if (head == NULL)
        {
            return;
        }
        Node *temp = head;
        head = head->next;
        delete temp;
    }

    void deleteLast()
    {
        if (head == NULL)
        {
            return;
        }
        Node *temp = head;
        Node *temp_prev = NULL;
        while (temp->next != NULL)
        {
            temp_prev = temp;
            temp = temp->next;
        }
        if (temp_prev != NULL)
        {
            temp_prev->next = NULL;
        }
        else
        {
            head = NULL; // Update head when deleting the last node
        }
        delete temp;
    }

    void deleteMiddle(int position)
    {
        if (head == NULL)
        {
            head = head->next;
            return;
        }
        Node *temp = head;
        Node *temp_prev = NULL;

        for (int i = 1; temp != NULL && i < position; i++)
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
    LinkedList linkedList;
    cout << "Insertion " << endl;
    linkedList.insertFirst(30);
    linkedList.insertFirst(20);
    linkedList.insertFirst(10);
    linkedList.insertLast(50);
    linkedList.insertLast(60);
    linkedList.insertLast(70);
    linkedList.insertMiddle(4, 40);
    linkedList.display();

    cout << "Deletion " << endl;
    linkedList.deleteFirst();
    linkedList.deleteLast();
    linkedList.deleteMiddle(2);
    linkedList.display();

    return 0;
}