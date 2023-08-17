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
        prev = NULL;
    }
    Node(int d, Node *&n, Node *&p)
    {
        data = d;
        next = n;
        prev = p;
    }
};

class DoublyLL
{
    Node *head = NULL;

public:
    void addAhead(int value)
    {
        Node *newNode = new Node(value);
        if (!head) // size 0
        {
            head = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    void addBack(int value)
    {
        Node *newNode = new Node(value);
        if (!head)
        {
            head = newNode;
            return;
        }
        Node *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        newNode->prev = temp;
        temp->next = newNode;
    }
    void insertAt(int index, int value)
    {

        Node *newNode = new Node(value);
        Node *temp = head;
        Node *temp_prev = head;
        for (int i = 0; i != index; i++)
        {
            temp_prev = temp;
            temp = temp->next;
        }
        newNode->prev = temp_prev;
        newNode->next = temp_prev->next;
        temp_prev->next->prev = newNode;
        temp_prev->next = newNode;
    }
    void deleteAt(int index)
    {

        Node *temp = head;
        Node *temp_prev = head;
        for (int i = 0; i != index; i++)
        {
            temp_prev = temp;
            temp = temp->next;
        }
        temp_prev->next->next->prev = temp_prev;
        temp_prev->next = temp_prev->next->next;
    }
    void display()
    {
        Node *temp = head;
        while (temp->next)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << temp->data << " -> ";
        cout << "NULL" << endl;
    }

    void reverse()
    {
        Node *last = NULL;
        Node *last_last = NULL;
        Node *curr = head;

        while (curr->next)
        {
            if (last && last_last)
            {
                last->next = last_last;
                // cout << last_last->data << ":" << last->data << ":" << curr->data << "->";
            }
            last_last = last;
            last = curr;
            curr = curr->next;
        }
        last->next = last_last;
        curr->next = last;
        head->next = NULL;
        head = curr;
    }
};

int main()
{
    DoublyLL dll;
    dll.addAhead(3);
    dll.addAhead(7);
    dll.addAhead(2);
    dll.addBack(1);
    dll.addBack(9);
    dll.insertAt(2, 34);

    dll.display();
    dll.reverse();
    dll.display();
}
