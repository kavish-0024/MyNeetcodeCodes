class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for(auto &it : flights) {
            adj[it[0]].push_back({it[1], it[2]});
        }
        
        vector<int> dis(n, 1e9);
        dis[src] = 0;
        
        queue<pair<int, int>> q;
        q.push({src, 0});
        
        int stops = 0;
        
        while(!q.empty() && stops <= k) {
            int size = q.size();
            for(int i = 0; i < size; i++) {
                int node = q.front().first;
                int cost = q.front().second;
                q.pop();
                
                for(auto &it : adj[node]) {
                    if(cost + it.second < dis[it.first]) {
                        dis[it.first] = cost + it.second;
                        q.push({it.first, dis[it.first]});
                    }
                }
            }
            stops++;
        }
        
        return dis[dst] == 1e9 ? -1 : dis[dst];
    }
};
