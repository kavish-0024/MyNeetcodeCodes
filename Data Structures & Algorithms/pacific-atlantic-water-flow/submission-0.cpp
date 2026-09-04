class Solution {
public:
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    
    void dfs(int r, int c, vector<vector<int>>& vis, vector<vector<int>>& h) {
        vis[r][c] = 1; 
        
        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i];
            int nc = c + dy[i];
            
            if (nr >= 0 && nr < h.size() && nc >= 0 && nc < h[0].size() && 
                !vis[nr][nc] && h[nr][nc] >= h[r][c]) {
                dfs(nr, nc, vis, h);
            }
        }
    }
    
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        
        vector<vector<int>> pac(n, vector<int>(m, 0));
        vector<vector<int>> atl(n, vector<int>(m, 0));
        
        for (int i = 0; i < n; i++) {
            dfs(i, 0, pac, heights);       
            dfs(i, m - 1, atl, heights);   
        }

        for (int j = 0; j < m; j++) {
            dfs(0, j, pac, heights);       
            dfs(n - 1, j, atl, heights);   
        }
        
        vector<vector<int>> ans;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (pac[i][j] && atl[i][j]) {
                    ans.push_back({i, j});
                }
            }
        }
        
        return ans;
    }
};