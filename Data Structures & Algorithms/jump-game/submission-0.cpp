class Solution { 
public: 
    bool canJump(vector<int>& nums) { 
        int n = nums.size(); 
        int i = 0; 
        while (1) { 
            int maxi = 0, maxii = -1, j = 0; 
            for (j = 0; j <= nums[i]; j++) { 
                if (i + j >= n-1 ) return true; 
                if (i + j + nums[i + j] >= maxi) { 
                    maxii = i + j; 
                    maxi = i + j + nums[i + j]; 
                } 
            } 
            if (maxii == i) return false; 
            
            i = maxii; 
        } 
        return false; 
    } 
};
