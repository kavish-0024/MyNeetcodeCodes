class Solution {
public:

    bool f(vector<int>& nums,int n,int target,vector<vector<int>>&dp)
    {
            if (target==0)
            return true;
            if(n==0)
            return (nums[0]==target);

            if(dp[n][target]!=-1)
            return dp[n][target];

            bool nottake=f(nums,n-1,target,dp);
            bool take=false;
            if(nums[n]<=target)
            take=f(nums,n-1,target-nums[n],dp);

            return dp[n][target]=take|nottake;
    }
    bool canPartition(vector<int>& nums)
    {
        int sum=0;
        
        for(int i=0;i<nums.size();i++)
        sum+=nums[i];

        if(sum%2==1)
        return false;

        vector<vector<int>>dp(nums.size(),vector<int>(sum/2+1,-1));
        return f(nums,nums.size()-1,sum/2,dp);
        
    }
};
