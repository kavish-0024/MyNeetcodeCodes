class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, multiset<string>> adj;
        for (const auto& ticket : tickets) {
            adj[ticket[0]].insert(ticket[1]);
        }

        vector<string> res;
        dfs("JFK", adj, res);
        
        reverse(res.begin(), res.end());
        return res;
    }

private:
    void dfs(const string& src, unordered_map<string, multiset<string>>& adj, vector<string>& res) {
        while (!adj[src].empty()) {
            string dst = *adj[src].begin();
            adj[src].erase(adj[src].begin());
            dfs(dst, adj, res);
        }
        res.push_back(src);
    }
};
