using pii=pair<int,pair<int,int>>;
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) 
    {
        priority_queue<pii>pq;
        for(auto &it:points)
        {
            int x=it[0];
            int y=it[1];

            pq.push({x*x+y*y,{x,y}});
            if(pq.size()>k)
            pq.pop();
        }
        vector<vector<int>>ans;
        while(!pq.empty())
        {
            int x=pq.top().second.first;
            int y=pq.top().second.second;
            pq.pop();
            ans.push_back({x,y});
        }
        return ans;
    }
};
