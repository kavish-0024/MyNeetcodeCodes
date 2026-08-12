class Solution {
public:
    bool hasDuplicate(vector<int>& nums) 
    {
        unordered_set<int>st;
        for(int i=0;i<nums.size();i++)
        {
            if(st.insert(nums[i]).second==false)
            return true;
            
        }
        return false;
    }
};