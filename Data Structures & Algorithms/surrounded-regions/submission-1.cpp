class Solution {
public:
    int dx[4]={0,1,0,-1};
    int dy[4]={1,0,-1,0};
    void dfs(int r,int c,vector<vector<int>>&vis,vector<vector<char>>& b)
    {
        vis[r][c]=1;
        for(int i=0;i<4;i++)
        {
            int nr=dx[i]+r;
            int nc=dy[i]+c;

            if(nr>=b.size() || nc>=b[0].size() || nr<0 || nc<0 || b[nr][nc]=='X' 
            || vis[nr][nc]==1)
            continue;

            dfs(nr,nc,vis,b);
        }
    }
    void solve(vector<vector<char>>& b) 
    {
        int n=b.size();
        int m=b[0].size();
        vector<vector<int>>vis(n,vector<int>(m,0));
        for(int i=0;i<n;i++)
        {
            if(!vis[i][0] && b[i][0]=='O')
            dfs(i,0,vis,b);

            if(!vis[i][m-1] && b[i][m-1]=='O')
            dfs(i,m-1,vis,b);
        }
        for(int j=0;j<m;j++)
        {
            if(!vis[0][j] && b[0][j]=='O')
            dfs(0,j,vis,b);

            if(!vis[n-1][j] && b[n-1][j]=='O')
            dfs(n-1,j,vis,b);
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(b[i][j]=='O' && !vis[i][j])
                b[i][j]='X';
            }
        }

    }
};
