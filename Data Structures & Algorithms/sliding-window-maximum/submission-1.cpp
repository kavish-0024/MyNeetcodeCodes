class Solution {
public:
    vector<int> maxSlidingWindow(const vector<int>& nums, int k) 
    {
        priority_queue<pair<int,int>>pq;
        int n=nums.size();
        for(int i=0;i<k-1;i++)
        pq.push({nums[i],i});
        vector<int>ans;
        int j=0;
        for(int i=k-1;i<n;i++)
        {
            pq.push({nums[i],i});
            while(pq.top().second<j)
            pq.pop();

            ans.push_back(pq.top().first);
            j++;
        }
        return ans;
    }
};
