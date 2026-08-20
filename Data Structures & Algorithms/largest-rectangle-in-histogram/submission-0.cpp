class Solution {
public:
    int largestRectangleArea(vector<int>& h) 
    {
        int n=h.size();
        if(n==1)
        return h[0];

        vector<int>l(n),r(n);
        l[0]=-1,r[n-1]=n;
        stack<int>stk;
        stk.push(0);
        for(int i=1;i<n;i++)
        {
            while(!stk.empty() && h[stk.top()]>=h[i])
            stk.pop();

            if(stk.empty())
            l[i]=-1;
            else
            l[i]=stk.top();

            stk.push(i);
        }
        while(!stk.empty())
        stk.pop();
        
        stk.push(n-1);
        for(int i=n-2;i>=0;i--)
        {
            while(!stk.empty() && h[stk.top()]>=h[i])
            stk.pop();

            if(stk.empty())
            r[i]=n;
            else
            r[i]=stk.top();

            stk.push(i);
        }
        int maxi=0;
        for(int i=0;i<n;i++)
        {
            int width=r[i]-l[i]-1;
            maxi=max(maxi,h[i]*width);
        }
        return maxi;

    }
};
