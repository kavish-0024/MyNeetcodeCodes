// class Solution {
// public:
//     void f(vector<int>& nums,vector<int>vis,vector<int>temp,vector<vector<int>>&ans)
//     {
//         if(temp.size()==nums.size())
//         {
//             ans.push_back(temp);
//             return;
//         }
//         for(int i=0;i<nums.size();i++)
//         {
//             if(vis[i]==0)
//             {
//                 vis[i]=1;
//                 temp.push_back(nums[i]);
//                 f(nums,vis,temp,ans);
//                 temp.pop_back();
//                 vis[i]=0;
//             }
//         }
//         return ;
//     }
//     vector<vector<int>> permute(vector<int>& nums) 
//     {
//         int n=nums.size();
//         vector<vector<int>>ans;
//         vector<int>temp;
//         vector<int>vis(nums.size(),0);
//         f(nums,vis,temp,ans);
//         return ans;
//     }
// };


class Solution {
public:
    void f(int index, vector<int>& nums, vector<vector<int>>& ans) {
        
        if (index == nums.size()) {
            ans.push_back(nums);
            return;
        }
        
        for (int i = index; i < nums.size(); i++) {
            swap(nums[index], nums[i]);       
            f(index + 1, nums, ans);          
            swap(nums[index], nums[i]);       
        }
    }
    
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        f(0, nums, ans);
        return ans;
    }
};