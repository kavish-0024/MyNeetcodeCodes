class Solution {
public:
    bool hasDuplicate(vector<int>& nums) 
    {
        unordered_set<int>st;
        for(auto it:nums)
        {
            if(st.insert(it).second==false)
            return true;
            
        }
        return false;
    }
};