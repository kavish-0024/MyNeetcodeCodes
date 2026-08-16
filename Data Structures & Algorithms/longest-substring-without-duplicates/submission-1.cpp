class Solution {
public:
    int lengthOfLongestSubstring(string s) 
    {
        vector<int>ind(256,-1);
        int n=s.size(),maxi=0,j=0;
        for(int i=0;i<n;i++)
        {
            int loc=(unsigned char)s[i];
            if(ind[loc] !=-1)
            {
                j=max(j,ind[loc]+1);
            }
                        ind[loc]=i;
            maxi=max(maxi,i-j+1);
        }
        return maxi;
    }
};
