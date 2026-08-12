class Solution {
public:
    bool hasDuplicate(vector<int>& nums) 
    {
        unordered_set<int>st;
        st.reserve(nums.size());
        for(auto it:nums)
        {
            if(st.insert(it).second==false)
            return true;
            
        }
        return false;
    }
};