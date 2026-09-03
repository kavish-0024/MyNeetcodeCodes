class Solution {
public:

    vector<string>c={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    void f(int idx, string temp,vector<string>&ans,string &digits)
    {
        int n=digits.size();
        if(idx==n)
        {
            if(temp.size()==n)
            ans.push_back(temp);
            return;
        }
        int num=digits[idx]-'0';
        for(int i=0;i<c[num].size();i++)
        {
            temp.push_back(c[num][i]);
            f(idx+1,temp,ans,digits);
            temp.pop_back();
        }
        return;
    }
    vector<string> letterCombinations(string digits) 
    {
        vector<string>ans;
        string temp="";
        if(digits=="")
        return ans;

        for(int i=0;i<digits.size();i++)
        {
            f(i,temp,ans,digits);
        }
        return ans;
    }
};
