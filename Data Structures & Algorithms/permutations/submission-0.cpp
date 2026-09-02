class Solution {
public:
    void f(vector<int>& nums,vector<int>vis,vector<int>temp,vector<vector<int>>&ans)
    {
        if(temp.size()==nums.size())
        {
            ans.push_back(temp);
            return;
        }
        for(int i=0;i<nums.size();i++)
        {
            if(vis[i]==0)
            {
                vis[i]=1;
                temp.push_back(nums[i]);
                f(nums,vis,temp,ans);
                temp.pop_back();
                vis[i]=0;
            }
        }
        return ;
    }
    vector<vector<int>> permute(vector<int>& nums) 
    {
        int n=nums.size();
        vector<vector<int>>ans;
        vector<int>temp;
        vector<int>vis(nums.size(),0);
        f(nums,vis,temp,ans);
        return ans;
    }
};
