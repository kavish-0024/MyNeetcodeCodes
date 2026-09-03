class Solution {
   public:
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, -1, 0, 1};
    
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) q.push({i, j});
            }
        }
        
        int cnt = 0;
        while (!q.empty()) {
            int sz = q.size();
            cnt++;
            while (sz--) {
                int r = q.front().first;
                int c = q.front().second;
                q.pop();

                for (int i = 0; i < 4; i++) {
                    int nr = dx[i] + r;
                    int nc = dy[i] + c;

                    if (nr >= n || nc >= m || nr < 0 || nc < 0 || grid[nr][nc] != 1) continue;
                    grid[nr][nc]=0;
                    q.push({nr, nc});
                }
            }
        }
        if (cnt > 0) cnt--; 
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) return -1;
            }
        }

        return cnt; 
    }
};