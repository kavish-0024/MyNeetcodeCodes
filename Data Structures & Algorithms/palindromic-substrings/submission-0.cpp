class Solution {
public:        
    int f(string &s,int left,int right)
    {
        int cnt=0;
        while(left>=0 && right<s.size() && s[left]==s[right])
        {
            left--;
            right++;
            cnt++;
        }
        return cnt;
    }
    int countSubstrings(string s) 
    {
        int ans=0;
        for(int i=0;i<s.size();i++)
        {
            ans+=f(s,i,i)+f(s,i,i+1);
        }
        return ans;
    }
};
