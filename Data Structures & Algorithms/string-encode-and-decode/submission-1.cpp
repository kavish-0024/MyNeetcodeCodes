class Solution {
   public:
    string encode(const vector<string>& strs) {
        string ans = "";
        for (const auto& s : strs) {
            int x = s.size();
            ans += to_string(x);
            ans += '#';
            ans += s;
        }
        return ans;
    }

    vector<string> decode(const string& s) {
        vector<string> ans;
        int n = s.size();
        int i = 0;

        while (i < n) {
            int j = i;
            while (s[j] != '#') {
                j++;
            }
            int len = stoi(s.substr(i, j - i));

            i = j + 1;
            ans.push_back(s.substr(i, len));

            i += len;
        }

        return ans;
    }
};