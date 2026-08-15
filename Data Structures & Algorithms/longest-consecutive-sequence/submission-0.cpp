class Solution {
public:
    int longestConsecutive(const vector<int>& nums) 
    {
        int n=nums.size();
        set<int>st;
        for(int i=0;i<n;i++)
        st.insert(nums[i]);

        int prev=-1e9;
        int len=0,ans=0;
        for(const auto &it:st)
        {
            if(it==prev+1)
            len++;
            else
            len=1;

            prev=it;
            ans=max(ans,len);
        }
        return ans;
    }
};
