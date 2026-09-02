class Solution {
public:
    bool isVal(string &temp)
    {
        stack<char>stk;
        for(int i=0;i<temp.size();i++)
        {
            if(temp[i]=='(')
            stk.push('(');
            else
            {
                if(stk.empty())
                return false;
                else if(stk.top()=='(')
                stk.pop();
                else
                stk.push(')');
            }
        }
        if(stk.empty())
        return true;
        else 
        return false;
    }
    
    void f(int idx, string &temp, vector<string>&ans)
    {
        if(idx==temp.size())
        {
            if(isVal(temp))
            ans.push_back(temp);
            
            return;
        }
        
        
        unordered_set<char> used; 
        
        
        for(int i=idx; i<temp.size(); i++)
        {
           
            if(used.find(temp[i]) != used.end()) continue;
            used.insert(temp[i]);
            
            swap(temp[idx],temp[i]);
            f(idx+1,temp,ans);
            swap(temp[idx],temp[i]);
        }
    }
    
    vector<string> generateParenthesis(int n) 
    {
        string temp="";
        for(int i=0;i<n;i++)
        temp+='(';
        for(int i=n;i<2*n;i++)
        temp+=')';

        vector<string>ans;
        f(0,temp,ans);
        return ans;
    }
};

// class Solution {
// public:
//     void f(int open, int close, int n, string& temp, vector<string>& ans) {

//         if (open == n && close == n) {
//             ans.push_back(temp);
//             return;
//         }
        
//         if (open < n) {
//             temp.push_back('(');
//             f(open + 1, close, n, temp, ans);
//             temp.pop_back(); 
//         }
        
//         if (close < open) {
//             temp.push_back(')');
//             f(open, close + 1, n, temp, ans);
//             temp.pop_back(); 
//         }
//     }

//     vector<string> generateParenthesis(int n) {
//         vector<string> ans;
//         string temp = "";
//         f(0, 0, n, temp, ans);
//         return ans;
//     }
// };