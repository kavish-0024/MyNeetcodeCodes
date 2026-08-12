class Solution {
public:
    vector<int> twoSum(const vector<int>& nums,const int target) 
    {
        int n=nums.size();
        unordered_map<int,int>mp;
        mp.reserve(nums.size());
        for(auto i=0;i<n;i++)
        {
            long long need=1LL*target-nums[i];
            auto x=mp.find(need);
            if(x!=mp.end())
                return {x->second,i};
            mp[nums[i]] = i;
        }
        return {};
    }
};
