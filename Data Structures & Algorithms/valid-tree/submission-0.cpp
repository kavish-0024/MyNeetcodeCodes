class Solution {
public:
    int find(int node, vector<int>& parent) {
        if (parent[node] == node) 
        return node;
        return parent[node] = find(parent[node], parent);
    }

    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) return false;

        vector<int> parent(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

        for (auto& edge : edges) {
            int rootU = find(edge[0], parent);
            int rootV = find(edge[1], parent);

            if (rootU == rootV) return false;

            parent[rootU] = rootV;
        }

        return true;
    }
};