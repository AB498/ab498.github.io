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
        Node *n = new Node(value);
        n->next = head;
        head = n;
    }

    void insertLast(int value)
    {
        Node *n = new Node(value);
        if (head == NULL)
        {
            head = n;
            return;
        }

        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = n;
    }

    void insertMiddle(int value, int position)
    {
        Node *n = new Node(value);
        if (head == NULL)
        {
            n->next = head;
            head = n;
            return;
        }
        Node *temp = head;
        for (int count = 0; count < position; ++count)
        {
            temp = temp->next;
        }

        n->next = temp->next;
        temp->next = n;
    }

    void deleteFirst()
    {
        head = head->next;
    }

    void deleteLast()
    {
        Node *temp = head;
        Node *temp_prev = NULL;
        while (temp->next != NULL)
        {
            temp_prev = temp;
            temp = temp->next;
        }
        temp_prev->next = NULL;
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

        for (int i = 1; i < position; i++)
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
    }
};

int main()
{
    LinkedList l1;
    l1.insertFirst(4);
    l1.insertFirst(6);
    l1.insertLast(7);
    l1.insertMiddle(9, 2);
    l1.insertLast(1);
    l1.insertLast(5);
    l1.display();
    cout << endl;
    l1.deleteFirst();
    l1.deleteLast();
    l1.deleteMiddle(2);
    l1.display();

    return 0;
}