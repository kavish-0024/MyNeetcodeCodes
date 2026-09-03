// class Solution {
// public:
//     int dx[4]={0,1,0,-1};
//     int dy[4]={1,0,-1,0};
//     void bfs(int r,int c,vector<vector<int>>& grid,int dis)
//     {
//         for(int i=0;i<4;i++)
//         {
//             int nr=r+dx[i];
//             int nc=c+dy[i];

//             if(nr>=grid.size() || nc>=grid[0].size() || nr<0 || nc<0 
//             || grid[nr][nc]==-1 || dis+1>=grid[nr][nc])
//             continue;

//             grid[nr][nc]=dis+1;
//             bfs(nr,nc,grid,dis+1);
//         }
//     }
//     void islandsAndTreasure(vector<vector<int>>& grid) 
//     {
//         int n=grid.size();
//         int m=grid[0].size();
//         for(int i=0;i<n;i++)
//         {
//             for(int j=0;j<m;j++)
//             {
//                 if(grid[i][j]==0)
//                 bfs(i,j,grid,0);
//             }
//         }
//     }
// };

class Solution {
public:
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    
    void islandsAndTreasure(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        queue<pair<int, int>> q;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }
        
        while (!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            
            for (int i = 0; i < 4; i++) {
                int nr = r + dx[i];
                int nc = c + dy[i];

                if (nr < 0 || nc < 0 || nr >= n || nc >= m 
                || grid[nr][nc] != INT_MAX) {
                    continue;
                }

                grid[nr][nc] = grid[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
};
