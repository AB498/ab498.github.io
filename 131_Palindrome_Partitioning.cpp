#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<string>> partition(string s)
    {
        vector<vector<string>> res;
        vector<vector<string>> substrs = getSubStrs(s);
        for (int i = 0; i < substrs.size(); i++)
        {
            for (int j = 0; j < substrs[i].size(); j++)
            {
                cout << substrs[i][j] << " ";
            }
            cout << "\n";
        }
        return res;
    }
    vector<vector<string>> getSubStrs(string s)
    {
        vector<vector<string>> possibilities = {};

        // for (int length = 1; length < s.size() + 1; length++)
        // {
        string firstPartiton = s.substr(0, 1);
        string rest = s.substr(1, s.size() - 1);
        cout << "substr: " << firstPartiton << ":" << rest << endl;
        if (rest.size() == 1)
        {
            return {{rest}};
        }
        possibilities.push_back({firstPartiton, rest});
        vector<vector<string>> possiblePartitionsRest = getSubStrs(rest);
        cout << possiblePartitionsRest[0].size() << endl;
        for (int i = 0; i < possiblePartitionsRest.size(); i++)
        {
            vector<string> res;
            res.push_back(firstPartiton);
            res.insert(res.end(), possiblePartitionsRest[i].begin(), possiblePartitionsRest[i].end());
            possibilities.push_back(res);
        }
        return possibilities;
        // res[0].push_back(firstPartiton);
        // }
        // return res;
    }
};
// a b a a b
int main()
{
    vector<vector<string>> res = Solution().partition("aab");
}

// Input
// ["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
// [[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
// Output
// [null, null, [5], null, null, [6, 5], null, [5]]
