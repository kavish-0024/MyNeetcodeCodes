// class Solution {
// public:
//     vector<int> partitionLabels(string s) 
//     {
//         int n=s.size();
//         unordered_map<char,int>mp;
//         for(int i=0;i<n;i++)
//         {
//             mp[s[i]]++;
//         }
//         unordered_set<char>st;
//         vector<int>ans;
//         int start=0;
//         for(int i=0;i<n;i++)
//         {
//             st.insert(s[i]);
//             mp[s[i]]--;
//             bool flag=true;
//             for(auto &it:st)
//             {
//                 if(mp[it]!=0)
//                 {
//                     flag=false;
//                     break;
//                 }
//             }
//             if(flag)
//             {
//                 st.clear();
//                 ans.push_back(i-start+1);
//                 start=i+1;
//             } 
//         }
//         if(!st.empty())
//         {
//             ans.push_back(n-start);
//         }
//         return ans;
//     }
// };

class Solution {
public:
    vector<int> partitionLabels(string s) {
        unordered_map<char, int> lastIndex;
        for (int i = 0; i < s.size(); i++) {
            lastIndex[s[i]] = i;
        }

        vector<int> res;
        int size = 0, end = 0;
        for (int i = 0; i < s.size(); i++) {
            size++;
            end = max(end, lastIndex[s[i]]);

            if (i == end) {
                res.push_back(size);
                size = 0;
            }
        }
        return res;
    }
};
