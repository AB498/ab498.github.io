#include <iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void display(ListNode *head)
{
    while (head != nullptr)
    {
        cout << head->val << " ";
        head = head->next;
    }
}
class Solution
{
public:
    void reorderList(ListNode *head)
    {
        // zero elements
        if (head == NULL)
        {
            return;
        }
        // one element
        if (head->next == NULL)
        {
            return;
        }
        // split in half
        ListNode *s = head;
        ListNode *f = head->next;
        while (true)
        {
            if (f == NULL)
                break;
            f = f->next;
            if (f == NULL)
                break;
            f = f->next;
            if (f == NULL)
                break;
            s = s->next;
        }
        ListNode *l1;
        ListNode *l2;
        l1 = head;
        l2 = s->next;
        s->next = NULL;

        // reverse second half
        ListNode *temp = NULL;
        while (l2->next != NULL)
        {
            ListNode *next = l2->next;
            l2->next = temp;
            temp = l2;
            l2 = next;
        }
        l2->next = temp;

        // reordered merge
        ListNode *head_temp = new ListNode(0);
        ListNode *tail = head_temp;
        while (true)
        {
            if (l1 == NULL && l2 == NULL)
                break;
            if (l1 != NULL)
            {
                tail->next = l1;
                l1 = l1->next;
                tail = tail->next;
            }
            if (l2 != NULL)
            {
                tail->next = l2;
                l2 = l2->next;
                tail = tail->next;
            }
        }
        head = head_temp->next;
    }
};

int main()
{
    ListNode *list1 = new ListNode(3);
    list1->next = new ListNode(4);
    list1->next->next = new ListNode(7);
    list1->next->next->next = new ListNode(1);
    list1->next->next->next->next = new ListNode(2);
    Solution().reorderList(list1);
    display(list1);
}