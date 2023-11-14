#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        return {nums, nums};
    }
};

int main(int argc, char const *argv[])
{
    vector<int> v = {1, 2};
    v;
    Solution().subsetsWithDup(v);
    return 0; 
}
