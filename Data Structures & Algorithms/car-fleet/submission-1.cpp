class Solution {
   public:
    int carFleet(int tar, vector<int>& pos, vector<int>& sp) {
        int n = pos.size();
        if(n==1)
        return 1;

        vector<pair<int, int>> pr;
        for (int i = 0; i < n; i++) pr.push_back({pos[i], sp[i]});
        sort(pr.begin(),pr.end());

        int count = 1;
        int pp = pr[n-1].first, ps = pr[n-1].second;
        for (int i = n-2; i >= 0; i--) {
            int cp = pr[i].first;
            int cs = pr[i].second;

            if (ps >= cs) {
                count++;
                ps = cs;
                pp = cp;
            } else {
                float dis = (1.0)*(tar-cp)/cs;
                if (((1.0)*(tar-pp)/ps)>=dis)
                    continue;
                else {
                    count++;
                    ps = cs;
                    pp = cp;
                }
            }
        }
        return count;
    }
};
