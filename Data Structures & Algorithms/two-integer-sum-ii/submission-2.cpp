class Solution {
public:
    vector<int> twoSum(const vector<int>& nums, int target) 
    {
        int i=0,j=nums.size()-1;
        while(i<j)
        {
            if(nums[j]>target-nums[i])
            j--;
            else if(nums[j]<target-nums[i])
            i++;
            else
            return {i+1,j+1};
        }
        return {};
    }
};
