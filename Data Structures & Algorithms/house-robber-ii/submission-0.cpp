class Solution {
public:
    int f(vector<int>&cost,int s,int e)
    {
        vector<int>dp(e+1,0);
        dp[s]=cost[s];
        dp[s+1]=max(cost[s],cost[s+1]);
        for(int i=s+2;i<=e;i++)
        {
            dp[i]=max(dp[i-1],dp[i-2]+cost[i]);
        }
        return dp[e];  
    }
    int rob(vector<int>& cost) 
    {
        int n=cost.size();
        if(n==1)
        return cost[0];
        if(n==2)
        return max(cost[0],cost[1]);

        return max(f(cost,0,n-2),f(cost,1,n-1));
    }
};
