class Solution {
public:
    int evalRPN(const vector<string>& tokens) 
    {
        int n=tokens.size();
        stack<int>stk;
        int ans=0;
        for(const auto&ch:tokens)
        {
            if(ch != "+" && ch != "-" && ch != "*" && ch != "/")
            {
                stk.push(stoi(ch));
            }
            else if(!stk.empty())
            {
                int y=stk.top();
                stk.pop();
                int x=stk.top();
                stk.pop();

                if(ch=="+")
                ans=x+y;
                else if(ch=="-")
                ans=x-y;
                else if(ch=="*")
                ans=x*y;
                else if(ch=="/")
                ans=x/y;

                stk.push(ans);
            }
        }
        return stk.top();
    }
};
