// using pll=pair<int,int>;
// class Solution {
// public:
//     vector<int> topKFrequent(const vector<int>& nums, int k)
//     {
//         priority_queue<pll,vector<pll>,greater<pll>>pq;
//         unordered_map<int,int>mp;
//         for(auto &it:nums)
//         {
//             mp[it]++;
//         }
//         for(auto &it:mp)
//         {
//             pq.push({it.second,it.first});
//             if(pq.size()>k)
//             pq.pop();
//         }
//         vector<int>ans;
//         ans.reserve(k);
//         while(!pq.empty())
//         {
//             int x=pq.top().second;
//             pq.pop();
//             ans.push_back(x);
//         }
//         return ans;
//     }
// };

class Solution {
   public:
    vector<int> topKFrequent(const vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for (auto& it : nums) {
            mp[it]++;
        }
        int n = nums.size();
        vector<vector<int>> freq(n + 1);
        for (auto& it : mp) {
            freq[it.second].push_back(it.first);
        }
        vector<int> ans;
        ans.reserve(k);
        for (auto i = n; i >= 0 && k > 0; i--) {
            if (freq[i].size() != 0) {
                for (auto& it : freq[i]) {
                    if (k > 0) {
                        ans.push_back(it);
                        k--;
                    } else {
                        return ans;
                    }
                }
            }
        }
        return ans;
    }
};
