// class Solution {
// public:
//     vector<int> productExceptSelf(const vector<int>& nums) 
//     {
//         int n=nums.size();
//         vector<int>ans(n,0),p(n,1),s(n,1);
//         for(auto i=1;i<n;i++)
//         {
//             p[i]=nums[i-1]*p[i-1];
//         }
//         for(auto i=n-2;i>=0;i--)
//         {
//             s[i]=nums[i+1]*s[i+1];
//         }
//         for(auto i=0;i<n;i++)
//         {
//             ans[i]=p[i]*s[i];
//         }
//         return ans;

//     }
// };

class Solution {
public:
    vector<int> productExceptSelf(const vector<int>& nums) 
    {
        int n=nums.size();
        vector<int>ans(n,1);
        for(auto i=1;i<n;i++)
        {
            ans[i]=nums[i-1]*ans[i-1];
        }
        int x=1;
        for(auto i=n-1;i>=0;i--)
        {
            ans[i]=ans[i]*x;
            x=nums[i]*x;
        }
        return ans;
    }
};
