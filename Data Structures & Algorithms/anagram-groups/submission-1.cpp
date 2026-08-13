// class Solution {
//    public:
//     vector<vector<string>> groupAnagrams(const vector<string>& s) 
//     {
//         unordered_map<string, vector<string>> mp;
//         for (auto& it : s) {
//             string key = it;
//             sort(key.begin(), key.end());
//             mp[key].push_back(it);
//         }
//         vector<vector<string>> ans;
//         ans.reserve(mp.size());
//         for (auto& it : mp) ans.push_back(move(it.second));
//         return ans;
//     }
// };

class Solution {
   public:
    vector<vector<string>> groupAnagrams(const vector<string>& s) 
    {
        unordered_map<string, vector<string>> mp;
        for (const auto& it : s) {
            array<int,26>freq={0};
            for(const auto &c:it)
            {
                freq[c-'a']++;
            }
            string a="";
            for(auto i=0;i<26;i++)
            {
                a+=to_string(freq[i])+"#";
            }
             mp[a].push_back(it);
        }
        vector<vector<string>> ans;
        ans.reserve(mp.size());
        for (auto& it : mp) ans.push_back(move(it.second));
        return ans;
    }
};

