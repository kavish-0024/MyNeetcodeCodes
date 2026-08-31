class Twitter {
public:
    unordered_map<int,vector<pair<int,int>>>mp;
    unordered_map<int,unordered_set<int>>f;
    int count=0;
    
    Twitter() 
    {
        
    }
    
    void postTweet(int userId, int tweetId) 
    {
        count++;
        mp[userId].push_back({count,tweetId});
    }
    
    vector<int> getNewsFeed(int userId) 
    {
        vector<int>ans;
        priority_queue<pair<int,int>>pq;
        
        for(auto &tweet : mp[userId]) {
            pq.push(tweet);
        }
        
        for(auto &followeeId : f[userId]) {
            for(auto &tweet : mp[followeeId]) {
                pq.push(tweet);
            }
        }
        
        while(!pq.empty() && ans.size() < 10) {
            ans.push_back(pq.top().second);
            pq.pop();
        }
        
        return ans;
    }
    
    void follow(int followerId, int followeeId) 
    {
        f[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) 
    {
        f[followerId].erase(followeeId);
    }
};