#include <iostream>
using namespace std;
class node
{
public:
    int data;
    node *next;

    node(int value)
    {
        data = value;
        next = NULL;
    }
};
void insertAthead(node *head, int val)
{
    node *n = new node(val);
    n->next = head;
    head = n;
    return;
}

void insertATail(node *&head, int val)
{
    node *n = new node(val);
    if (head == NULL)
    {
        head = n;
        return;
    }

    node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = n;
}

void display(node *head)
{
    node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

int main()
{
    node *head = NULL;

    insertATail(head, 1);

    insertATail(head, 2);

    insertATail(head, 3);
    insertAthead(head, 4);
    display(head);
    return 0;
}