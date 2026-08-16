class Solution {
public:
    int maxProfit(const vector<int>& prices) 
    {
        int ans=0,n=prices.size(),mini=INT_MAX;
        for(int i=0;i<n;i++)
        {
            ans=max(ans,prices[i]-mini);
            mini=min(mini,prices[i]);
        }
        return ans;
    }
};
