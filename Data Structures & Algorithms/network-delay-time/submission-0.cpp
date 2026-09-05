class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) 
    {
        vector<vector<pair<int,int>>>adj(n+1);
        for(auto &it:times)
        {
            adj[it[0]].push_back({it[1],it[2]});
        }
        queue<int>q;
        q.push(k);
        vector<int>dis(n+1,1e9);
        dis[k]=0;
        while(!q.empty())
        {
            int sz=q.size();
            while(sz--)
            {
                int node=q.front();
                q.pop();

                for(auto &it:adj[node])
                {
                    int neig=it.first;
                    int t=it.second;
                    if(dis[neig]>dis[node]+t)
                    {
                        dis[neig]=dis[node]+t;
                        q.push(neig);
                    }
                }
            }
        }
        int maxi=0;
        for(int i=1;i<=n;i++)
        {
            maxi=max(maxi,dis[i]);
        }
        if(maxi==1e9)
        return -1;

        return maxi;
    }
};
