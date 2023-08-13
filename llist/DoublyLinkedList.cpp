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
        if (head == NULL || position <= 1)
        {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node *current = head;
        int count = 1;
        while (current != NULL && count < position - 1)
        {
            current = current->next;
            count++;
        }

        if (current != NULL)
        {
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    void deleteFirst()
    {
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = head;
        head = head->next;
        if (head != NULL)
        {
            head->prev = NULL;
        }
        else
        {
            tail = NULL;
        }
        delete temp;
    }
    void deleteLast()
    {
        if (!tail)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = tail;
        tail = tail->prev;
        if (tail)
        {
            tail->next = NULL;
        }
        else
        {
            head = NULL;
        }
        delete temp;
    }
    void deleteAtMiddle(int position)
    {
        if (head == NULL || position <= 1)
        {
            deleteFirst();
            return;
        }
        Node *current = head;
        int count = 1;
        while (current != NULL && count < position - 1)
        {
            current = current->next;
            count++;
        }
        if (current != NULL && current->next != NULL)
        {
            Node *temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }
    void display()
    {
        Node *curr = head;
        while (curr)
        {
            cout << curr->data << "->";
            curr = curr->next;
        }
        cout << "NULL" << endl;
    }
};
int main()
{
    DoublyLinkedList doublyLinkedList;
    cout << "Insertion" << endl;
    doublyLinkedList.insertFirst(4);
    doublyLinkedList.insertLast(8);
    doublyLinkedList.insertFirst(2);
    doublyLinkedList.insertAtMiddle(2, 5);
    doublyLinkedList.insertLast(7);
    doublyLinkedList.display();
    cout << "Deletions" << endl;
    doublyLinkedList.deleteFirst();
    doublyLinkedList.deleteLast();
    doublyLinkedList.deleteAtMiddle(2);
    doublyLinkedList.display();
    return 0;
}
