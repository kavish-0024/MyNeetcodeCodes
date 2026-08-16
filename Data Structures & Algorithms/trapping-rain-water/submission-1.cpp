class Solution {
public:
    int trap(const vector<int>& height) {
        int n = height.size();
        if (n == 0) return 0;

        int l = 0, r = n - 1;
        int lmax = height[l];
        int rmax = height[r];
        int ans = 0;

        while (l < r) {
            if (lmax < rmax) {
                l++;
                lmax = max(lmax, height[l]);
                ans += lmax - height[l];
            } else {
                r--;
                rmax = max(rmax, height[r]);
                ans += rmax - height[r];
            }
        }
        return ans;
    }
};