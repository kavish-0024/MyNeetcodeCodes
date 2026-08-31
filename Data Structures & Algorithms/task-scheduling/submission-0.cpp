class Solution {
public:
    int leastInterval(vector<char>& t, int n) 
    {
        priority_queue<pair<int,char>>pq;
        queue<pair<char,pair<int,int>>>q;
        unordered_map<char,int>mp;
        for(int i=0;i<t.size();i++)
        mp[t[i]]++;

        for(auto &it:mp)
        {
            pq.push({it.second,it.first});
        }
        int count=0;
        while(!pq.empty() || !q.empty())
        {
            count++;
            if(!q.empty())
            {
                if(q.front().second.second<=count)
                {pq.push({q.front().second.first,q.front().first});
                q.pop();}
            }
           if(!pq.empty())
           {
             int freq=pq.top().first;
            char ch=pq.top().second;
            pq.pop();

            freq--;
            if(freq!=0)
            q.push({ch,{freq,count+n+1}});
           }


        }
        return count;
    }
};
