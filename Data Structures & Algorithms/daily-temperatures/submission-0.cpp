class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temp) 
    {
        stack<int>stk;
        int n=temp.size();
        vector<int>ans(n);
        for(int i=n-1;i>=0;i--)
        {
            int count=0;
            while(!stk.empty() && temp[stk.top()]<=temp[i])
            {stk.pop();
            count++;}

            if(stk.empty())
            ans[i]=0;
            else
            ans[i]=stk.top()-i;

            stk.push(i);
        }
        return ans;
    }
};
