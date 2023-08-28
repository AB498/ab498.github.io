#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        return {nums};
    }
};

int main(int argc, char const *argv[])
{
    vector<int> v = {1, 2, 4, 5, 7};

    Solution().subsetsWithDup(v);
    return 0;
}
