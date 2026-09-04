class Solution {
   public:
    vector<int> findOrder(int n, vector<vector<int>>& pre) {
        vector<vector<int>> adj(n);
        vector<int>ans;
        vector<int> inD(n, 0);
        for (auto& it : pre) {
            adj[it[0]].push_back(it[1]);
            inD[it[1]]++;
        }
        int count = 0;
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (inD[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            ans.push_back(x);
            for (auto& it : adj[x]) {
                inD[it]--;
                if (inD[it] == 0) q.push(it);
            }
            count++;
        }
        reverse(ans.begin(),ans.end());
        if(count == n)
        return ans;
        else
        return {};
    }
};
