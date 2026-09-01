class Solution {
public:
    void f(int i,vector<int>& nums,vector<int>&temp,vector<vector<int>>&ans)
    {
    //     if(i==nums.size())
    //    { ans.push_back(temp);
    //     return;}
    ans.push_back(temp);
        for(int j=i;j<nums.size();j++)
        {
            if(j>i && nums[j]==nums[j-1])
            continue;
            temp.push_back(nums[j]);
            f(j+1,nums,temp,ans);
            temp.pop_back();
        }
        return ;
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) 
    {
        vector<vector<int>>ans;
        vector<int>temp;
        sort(nums.begin(),nums.end());
        f(0,nums,temp,ans);
        return ans;
    }
};
