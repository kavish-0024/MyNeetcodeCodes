class Solution {
public:
    int maxArea(const vector<int>& heights) 
    {
        int l=0,r=heights.size()-1;
        int ans=0,h,w;
        while(l<r)
        {
            h=min(heights[l],heights[r]);
            w=(r-l);
            ans=max(ans,h*w);

            if(heights[l]>heights[r])
            r--;
            else
            l++;
        }
        return ans;
    }
};
