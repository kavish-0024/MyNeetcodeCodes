class Solution {
public:
    bool isAnagram(const string &s,const string &t) 
    {
        int n1=s.size(),n2=t.size();
        if(n1!=n2)
        return false;
        array<int, 26> freq = {0};
        for(auto i=0;i<n1;i++)
        {
            freq[s[i]-'a']++;
            freq[t[i]-'a']--;
        }
        for(auto i=0;i<26;i++)
        {
            if(freq[i]!=0)
            return false;
        }
        return true;
    }
};
