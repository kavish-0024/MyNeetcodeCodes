class Solution { 
public: 
    string foreignDictionary(vector<string>& words) { 
        unordered_map<char,unordered_set<char>>adj; 
        unordered_map<char,int>inD; 
        for(string w:words) { 
            for(char c:w) { 
                adj[c]=unordered_set<char>(); 
                inD[c]=0; 
            } 
        } 
        for(int i=0;i<words.size()-1;i++) { 
            string w1=words[i],w2=words[i+1]; 
            int mini=min(w1.size(),w2.size()); 
            if(w1.size()>w2.size() && w1.substr(0, mini) == w2.substr(0, mini)) return ""; 
            for(int j=0;j<mini;j++) { 
                if (w1[j] != w2[j]) { 
                    if (!adj[w1[j]].count(w2[j])) { 
                        adj[w1[j]].insert(w2[j]); 
                        inD[w2[j]]++; 
                    } 
                    break; 
                } 
            } 
        } 
        queue<char>q; 
        for(auto &[c,deg]:inD) { 
            if(deg==0) q.push(c); 
        } 
        string res; 
        while (!q.empty()) { 
            char char_ = q.front(); 
            q.pop(); 
            res += char_; 
            for (char neighbor : adj[char_]) { 
                inD[neighbor]--; 
                if (inD[neighbor] == 0) { 
                    q.push(neighbor); 
                } 
            } 
        } 
        return res.size() == inD.size() ? res : ""; 
    } 
};
