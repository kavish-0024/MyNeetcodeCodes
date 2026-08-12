class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        int n=nums.size();
        unordered_map<int,int>mp;
        for(auto i=0;i<n;i++)
        {
            int need=target-nums[i];
            if(mp.count(need))
                return {mp[need],i};
            mp[nums[i]] = i;
        }
        return {};
    }
};
