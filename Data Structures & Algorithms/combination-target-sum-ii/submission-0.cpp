class Solution {
public:
    void f(int i,vector<int>& nums,vector<int>&temp,vector<vector<int>>&ans, int sum,int tar)
    {
        if(sum==tar)
        {ans.push_back(temp);
        return;}
        for(int j=i;j<nums.size();j++)
        {
            if(j > i && nums[j] == nums[j-1]) continue;
            if(sum>tar)
            return;
            temp.push_back(nums[j]);
            f(j+1,nums,temp,ans,sum+nums[j],tar);
            temp.pop_back();
        }
        return ;
    }
    vector<vector<int>> combinationSum2(vector<int>& nums, int tar) 
    {
        vector<vector<int>>ans;
        vector<int>temp;
        sort(nums.begin(),nums.end());
        f(0,nums,temp,ans,0,tar);
        return ans;
    }
};
