#include <iostream>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    bool isSubtree(TreeNode *root, TreeNode *subRoot)
    {
        if (root == nullptr && subRoot == nullptr)
            return true;
        if (root == nullptr || subRoot == nullptr)
            return false;
        // cout << root->val << ":" << subRoot->val << endl;
        bool res = dfs(root, subRoot);
        // cout << "res " << res << endl;
        if (!res)
        {
            return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
        }
        else
        {
            return true;
        }
    }
    bool dfs(TreeNode *root1, TreeNode *root2)
    {

        if (root1 == nullptr && root2 == nullptr)
            return true;
        if (root1 == nullptr || root2 == nullptr)
            return false;
        // cout << root1->val << ":" << root2->val << endl;
        if (root1->val == root2->val)
            if (dfs(root1->left, root2->left) && dfs(root1->right, root2->right))
                return true;
        return false;
    }
};

int main(int argc, char const *argv[])
{
    // Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
    TreeNode *root = new TreeNode(4,
                                  new TreeNode(5),
                                  new TreeNode(4,
                                               new TreeNode(1),
                                               new TreeNode(2)));
    TreeNode *subTree = new TreeNode(4,
                                     new TreeNode(1),
                                     new TreeNode(2));

    cout << Solution().isSubtree(root, subTree);
    return 0;
}
