class Solution {
public:
    int expand(const string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1; 
    }
    
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        
        int start = 0;
        int ans = 0;
        
        for (int i = 0; i < s.size(); i++) {
            int len1 = expand(s, i, i);
            int len2 = expand(s, i, i + 1);
            int maxi = max(len1, len2);
            if (maxi > ans) {
                ans = maxi;
                start = i - (maxi - 1) / 2; 
            }
        }  
        return s.substr(start, ans);
    }
};