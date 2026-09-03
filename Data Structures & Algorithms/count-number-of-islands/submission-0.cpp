class Solution {
public:
    int dx[4]={0,1,0,-1};
    int dy[4]={1,0,-1,0};
    void dfs(int r,int c,vector<vector<char>>& grid,vector<vector<int>>&vis)
    {
        vis[r][c]=1;
        for(int i=0;i<4;i++)
        {
            int nr=dx[i]+r;
            int nc=dy[i]+c;

            if(nr>=grid.size() || nc>=grid[0].size() || nr<0 || nc<0 
            || vis[nr][nc] || grid[nr][nc]=='0')
            continue;

            dfs(nr,nc,grid,vis);
        }
        return ;
    }
    int numIslands(vector<vector<char>>& grid) 
    {
        int n=grid.size();
        int m=grid[0].size();
        vector<vector<int>>vis(n,vector<int>(m,0));
        int c=0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(grid[i][j]=='1' && !vis[i][j])
                {
                    dfs(i,j,grid,vis);
                    c++;
                }
            }
        }
        return c;

    }
};
