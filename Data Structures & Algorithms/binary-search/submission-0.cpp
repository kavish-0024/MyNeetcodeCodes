class Solution {
public:
    int search(vector<int>& nums, int target) 
    {
        int n=nums.size();
        int l=0,r=n-1,m;
        while(l<=r)
        {
            m=l+(r-l)/2;
            if(nums[m]>target)
            r=m-1;
            else if(nums[m]<target)
            l=m+1;
            else
            return m;
        }
        if(l>=r)
        return -1;
    }
};
