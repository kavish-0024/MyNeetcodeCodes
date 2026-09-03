class Solution {
   public:
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    void dfs(int r, int c, vector<vector<int>>& grid,int &ans) {
        grid[r][c] = 0;
        ans++;

        for (int i = 0; i < 4; i++) {
            int nr = dx[i] + r;
            int nc = dy[i] + c;

            if (nr >= grid.size() || nc >= grid[0].size() || nr < 0 || nc < 0 ||
                grid[nr][nc] == 0)
                continue;

            dfs(nr, nc, grid,ans);
        }
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int maxi=0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    int ans=0;
                    dfs(i, j, grid,ans);
                    maxi=max(maxi,ans); 
                }
            }
        }
        return maxi;
    }
};