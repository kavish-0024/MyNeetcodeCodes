class Solution {
   public:
    int longestConsecutive(const vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> st;
        for (int i = 0; i < n; i++) st.insert(nums[i]);

        int prev = -1e9;
        int len = 0, ans = 0, x = 0;
        for (const auto& it : st) {
            x = it;
            len = 1;
            if (st.find(x - 1) == st.end()) {
                while (st.find(x + 1) != st.end()) {
                    len++;
                    x++;
                }
            }
            ans = max(ans, len);
        }
        return ans;
    }
};
