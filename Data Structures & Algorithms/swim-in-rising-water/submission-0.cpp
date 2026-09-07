class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) 
    {
        int n=grid.size();
        set<pair<int,int>>st;
        priority_queue<vector<int>,vector<vector<int>>,greater<>>pq;
        vector<vector<int>>direct={
            {0,1},{0,-1},{1,0},{-1,0}
        };
        st.insert({0,0});
        pq.push({grid[0][0],0,0});
        while(!pq.empty())
        {
            auto it=pq.top();
            pq.pop();
            int t=it[0],r=it[1],c=it[2];
            if(r==n-1 && c==n-1)
            return t;
            for(auto &dir:direct)
            {
                int nr=r+dir[0];
                int nc=c+dir[1];
                if(nr<0 || nc<0 || nr>=n || nc>=n || st.count({nr,nc}))
                continue;

                st.insert({nr,nc});
                pq.push({max(t,grid[nr][nc]),nr,nc});
            }
        }
        return 0;
    }
};
