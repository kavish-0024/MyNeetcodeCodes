class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) 
    {
        vector<vector<int>>adj(n);
        vector<int>vis(n,0);
        for(auto &it:edges)
        {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        int c=0;
        for(int i=0;i<n;i++)
        {
            if(!vis[i])
            {
                c++;
                queue<int>q;
                q.push(i);
                while(!q.empty())
                {
                    int node=q.front();
                    q.pop();

                    vis[node]=1;
                    for(auto &it:adj[node])
                    {
                        if(!vis[it])
                        q.push(it);
                    }
                }
            }
        }
        return c;
    }
};
