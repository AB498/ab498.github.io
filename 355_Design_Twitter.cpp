#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

using namespace std;
class Twitter
{
public:
    vector<map<string, int>> posts;
    map<int, map<int, int>> usersToFollowers;
    int time = 0;
    Twitter()
    {
    }

    void postTweet(int userId, int tweetId)
    {
        posts.push_back({{"userId", userId}, {"time", time++}, {"tweetId", tweetId}});
    }

    vector<int> getNewsFeed(int userId)
    {
        vector<int> res;
        int count = 0;
        for (vector<map<string, int>>::reverse_iterator it = posts.rbegin(); it != posts.rend() && count < 10; ++it)
        {
            if (!usersToFollowers[it->at("userId")][userId] && it->at("userId") != userId)
                continue;
            cout << "time: " << it->at("time") << endl;
            res.push_back(it->at("tweetId"));
            count++;
        }
        return res;
    }

    void follow(int followerId, int followeeId)
    {
        usersToFollowers[followeeId][followerId] = 1;
    }

    void unfollow(int followerId, int followeeId)
    {
        usersToFollowers[followeeId][followerId] = 0;
    }
};

int main()
{

    Twitter *obj = new Twitter();
    for (int i = 0; i < 33; i++)
    {
        obj->postTweet(1, i);
        obj->postTweet(2, ++i);
        obj->postTweet(3, ++i);
    }

    obj->follow(1, 2);
    obj->follow(1, 3);
    vector<int> param_2 = obj->getNewsFeed(1);
    for (int i = 0; i < param_2.size(); i++)
        cout << param_2[i] << ' ';

    obj->unfollow(1, 2);
    return 0;
}

// Input
// ["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
// [[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
// Output
// [null, null, [5], null, null, [6, 5], null, [5]]
