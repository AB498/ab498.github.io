#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *prev;
    Node *next;
    Node(int value)
    {
        data = value;
        prev = NULL;
        next = NULL;
    }
};
class DoublyLinkedList
{
private:
    Node *head;
    Node *tail;

public:
    DoublyLinkedList()
    {
        head = NULL;
        tail = NULL;
    }
    void insertFirst(int value)
    {
        Node *newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    void insertLast(int value)
    {
        Node *newNode = new Node(value);
        if (!tail)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }
    void insertAtMiddle(int value, int position)
    {
        Node *newNode = new Node(value);
        if (head == NULL)
        {
            head = tail = newNode;
        }

        Node *temp = head;
        for (int count = 0; count < position; ++count)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp->next->next->prev;
        temp->next = newNode;
        temp->next->next->prev = newNode;
    }
    void deleteFirst()
    {
        head = head->next;
        head->prev = NULL;
    }
    void deleteLast()
    {
        tail = tail->prev;
        tail->next = NULL;
    }
    void deleteAtMiddle(int index)
    {
        if (index < 0)
            return;

        Node *temp = head;
        for (int count = 0; count < index && temp != nullptr; ++count)
        {
            temp = temp->next;
        }

        if (temp == nullptr || temp->next == nullptr)
            return;

        Node *nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;
        if (nodeToDelete->next != nullptr)
        {
            nodeToDelete->next->prev = temp;
        }
        delete nodeToDelete;
    }
    void display()
    {
        Node *curr = head;
        while (curr)
        {
            cout << curr->data << "->";
            curr = curr->next;
        }
    }
};
int main()
{
    DoublyLinkedList d1;
    d1.insertFirst(4);
    d1.insertLast(8);
    d1.insertFirst(5);
    d1.insertFirst(2);
    d1.insertAtMiddle(6, 1);
    d1.insertFirst(3);
    d1.insertLast(7);
    d1.display();
    cout << endl;
    d1.deleteFirst();
    d1.deleteFirst();
    d1.deleteLast();
    d1.deleteAtMiddle(2);
    d1.display();
    return 0;
}
