class Solution {
   public:
    vector<vector<string>> groupAnagrams(const vector<string>& s) 
    {
        unordered_map<string, vector<string>> mp;
        for (auto& it : s) {
            string key = it;
            sort(key.begin(), key.end());
            mp[key].push_back(it);
        }

        vector<vector<string>> ans;
        for (auto& it : mp) ans.push_back(it.second);
        return ans;
    }
};
