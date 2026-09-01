class Solution {
public:
    void f(int i,vector<int>& nums,vector<int>&temp,vector<vector<int>>&ans, int sum,int tar)
    {
        if(sum>tar)
        return;
        if(sum==tar)
        ans.push_back(temp);
        for(int j=i;j<nums.size();j++)
        {
            temp.push_back(nums[j]);
            f(j,nums,temp,ans,sum+nums[j],tar);
            temp.pop_back();
        }
        return ;
    }
    vector<vector<int>> combinationSum(vector<int>& nums, int tar) 
    {
        vector<vector<int>>ans;
        vector<int>temp;
        f(0,nums,temp,ans,0,tar);
        return ans;
    }
};
