class Solution { 
public: 
    string encode(vector<string>& strs) { 
        string ans = ""; 
        for (auto s : strs) { 
            ans += s; 
            ans += '\0'; 
        } 
        return ans; 
    } 

    vector<string> decode(string s) { 
        vector<string> ans; 
        int n = s.size(), i = 0; 
        string str = ""; 
        
        while (i < n) { 
            if (s[i] == '\0') {
                ans.push_back(str); 
                str = ""; 
            } else { 
                str += s[i]; 
            } 
            i++;
        } 
        return ans; 
    } 
};