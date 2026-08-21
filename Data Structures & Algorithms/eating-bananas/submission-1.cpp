class Solution {
public:
    bool chk(int m,vector<int>& piles, int h)
    {
        int ans=0;
        for(int i=0;i<piles.size();i++)
        {
            ans+=(piles[i]+m-1)/m;
            if(ans>h)
            return false;
        }
        return ans<=h;
    }
    int minEatingSpeed(vector<int>& piles, int h) 
    {
        int r=*max_element(piles.begin(),piles.end());
        int l=1;
        while(l<r)
        {
            int m=l+(r-l)/2;
            bool x=chk(m,piles,h);
            if(!x)
            l=m+1;
            else
            r=m;
        }
        return l;
    }
};
