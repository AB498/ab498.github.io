#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// / 5 2 4
// 1 2 5 3

class Solution
{
public:
    void display(ListNode *head)
    {
        while (head != nullptr)
        {
            cout << head->val << " ";
            head = head->next;
        }
    }
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *temp_head = new ListNode(0);
        ListNode *tail = temp_head;

        while (true)
        {
            if (list1 == nullptr)
            {
                tail->next = list2;
                break;
            }
            else if (list2 == nullptr)
            {
                tail->next = list1;
                break;
            }

            // cout << list1->val << ":" << list2->val << endl;

            if (list1->val < list2->val)
            {
                tail->next = list1;
                list1 = list1->next;
            }
            else
            {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        return temp_head->next;
    }
    ListNode *merge(ListNode *l1)
    {
        if (l1 == nullptr || l1->next == nullptr)
            return l1;
        pair<ListNode *, ListNode *> lns = split(l1);
        l1 = merge(lns.first);
        ListNode *l2 = merge(lns.second);

        // display(l1);
        // cout << endl;
        // display(l2);
        // cout << endl;
        // if (l1->next == nullptr || l2->next == nullptr)
        //     return mergeTwoLists(l1, l2);
        // if (l1->next == nullptr && l2->next == nullptr)
        //     return l1;
        return mergeTwoLists(l1, l2);
    }
    pair<ListNode *, ListNode *> split(ListNode *l1)
    {
        ListNode *slow = l1;
        ListNode *fast = slow->next;

        while (true)
        {
            if (fast == nullptr)
                break;
            // cout << slow->val << ":" << fast->val << endl;
            fast = fast->next;
            if (fast == nullptr)
                break;
            fast = fast->next;
            if (fast == nullptr)
                break;
            slow = slow->next;
        }
        ListNode *l2 = slow->next;
        slow->next = NULL;
        return {l1, l2};
    }
};

int main()
{
    ListNode *list1 = new ListNode(3);
    list1->next = new ListNode(4);
    list1->next->next = new ListNode(7);
    list1->next->next->next = new ListNode(1);
    list1->next->next->next->next = new ListNode(2);
    list1->next->next->next->next->next = new ListNode(9);
    ListNode *list2 = new ListNode(3);
    list2->next = new ListNode(4);
    list2->next->next = new ListNode(7);
    list2->next->next->next = new ListNode(1);
    list2->next->next->next->next = new ListNode(2);
    Solution().display(Solution().merge(list1));
}