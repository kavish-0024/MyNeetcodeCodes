class Solution {
public:
    vector<int> partitionLabels(string s) 
    {
        int n=s.size();
        unordered_map<char,int>mp;
        for(int i=0;i<n;i++)
        {
            mp[s[i]]++;
        }
        unordered_set<char>st;
        vector<int>ans;
        int start=0;
        for(int i=0;i<n;i++)
        {
            st.insert(s[i]);
            mp[s[i]]--;
            bool flag=true;
            for(auto &it:st)
            {
                if(mp[it]!=0)
                {
                    flag=false;
                    break;
                }
            }
            if(flag)
            {
                st.clear();
                ans.push_back(i-start+1);
                start=i+1;
            } 
        }
        if(!st.empty())
        {
            ans.push_back(n-start);
        }
        return ans;
    }
};
