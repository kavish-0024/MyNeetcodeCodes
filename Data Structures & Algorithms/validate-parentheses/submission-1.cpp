class Solution {
public:
    bool isValid(const string& s) { 
        stack<char> stk;
        for(char it : s) {
            if(it == '(' || it == '{' || it == '[') {
                stk.push(it);
            } 
            else {
                if(stk.empty()) return false;
                if(it == ')' && stk.top() != '(') return false;
                if(it == '}' && stk.top() != '{') return false;
                if(it == ']' && stk.top() != '[') return false;
                stk.pop();
            }
        }
        return stk.empty();
    }
};