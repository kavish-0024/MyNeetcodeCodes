using pll=pair<int,int>;
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) 
    {
        priority_queue<pll,vector<pll>,greater<pll>>pq;
        unordered_map<int,int>mp;
        for(auto &it:nums)
        {
            mp[it]++;
        }
        for(auto &it:mp)
        {
            pq.push({it.second,it.first});
            if(pq.size()>k)
            pq.pop();
        }
        vector<int>ans;
        while(!pq.empty())
        {
            int x=pq.top().second;
            pq.pop();
            ans.push_back(x);
        }
        return ans;


    }
};
