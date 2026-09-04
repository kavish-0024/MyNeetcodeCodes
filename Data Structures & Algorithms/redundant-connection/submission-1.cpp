class Solution {
public:
    int find(int node, vector<int>& parent) {
        if (parent[node] == node) {
            return node;
        }
        return parent[node] = find(parent[node], parent); 
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> parent(n + 1);
        
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
        
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            
            int rootU = find(u, parent);
            int rootV = find(v, parent);
            
            if (rootU == rootV) {
                return edge;
            }
            
            parent[rootU] = rootV;
        }
        
        return {}; 
    }
};