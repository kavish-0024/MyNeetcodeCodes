class Solution {
public:
    string minWindow(const string& s, const string& t) {

        if (s.empty() || t.empty() || s.size() < t.size()) return "";

        vector<int> freq(128, 0);
        for (char c : t) {
            freq[c]++;
        }

        int i = 0, j = 0;
        int required = t.size();
        
        int minLen = INT_MAX;
        int startIdx = 0;

        while (j < s.size()) {
            if (freq[s[j]] > 0) {
                required--;
            }
            freq[s[j]]--;
            j++;

            while (required == 0) {
                if (j - i < minLen) {
                    minLen = j - i;
                    startIdx = i;
                }
                freq[s[i]]++;
                if (freq[s[i]] > 0) {
                    required++;
                }
                i++;
            }
        }

        return minLen == INT_MAX ? "" : s.substr(startIdx, minLen);
    }
};