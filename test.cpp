#include <iostream>
using namespace std;

class node
{
public:
    int data;
    node *next;

    node(int val)
    {
        data = val;
        next = NULL;
    }
};
void insfirst(node *&head, int val)
{
    node *n = new node(val);
    n->next = head;
    head = n;
}
void insmiddle(node *head, int val, int position)
{
    node *n = new node(val);

    if (head == NULL)
    {
        n->next = head;
        head = n;
        return;
    }

    node *temp = head;
    node *temp_prev = NULL;

    for (int count = 0; count < position; ++count)
    {
        temp_prev = temp;
        temp = temp->next;
    }
    n->next = temp_prev->next;
    temp_prev->next = n;
}

void inslast(node *&head, int val)
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
        cout << temp->data << " ->";
        temp = temp->next;
    }
    cout << endl;
}

int main()
{
    node *head = NULL;
    insfirst(head, 1);
    inslast(head, 2);
    inslast(head, 3);
    inslast(head, 4);
    insmiddle(head, 5, 2);
    inslast(head, 6);
    inslast(head, 7);
    display(head);

    return 0;
}