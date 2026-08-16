class Solution {
public:
    int lengthOfLongestSubstring(string s) 
    {
        unordered_map<char,int>mp;
        int j=0,n=s.size(),len=0,maxi=0;
        for(int i=0;i<n;i++)
        {
            mp[s[i]]++;
            while(mp[s[i]]!=1)
            {
                mp[s[j]]--;
                j++;
            }
            len=i-j+1;
            maxi=max(maxi,len);
        }
        return maxi;
    }
};
