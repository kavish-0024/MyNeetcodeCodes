// class Solution {
// public:
//     vector<int> maxSlidingWindow(const vector<int>& nums, int k) 
//     {
//         priority_queue<pair<int,int>>pq;
//         int n=nums.size();
//         for(int i=0;i<k-1;i++)
//         pq.push({nums[i],i});
//         vector<int>ans;
//         for(int i=k-1;i<n;i++)
//         {
//             pq.push({nums[i],i});
//             while(pq.top().second<=i-k)
//             pq.pop();

//             ans.push_back(pq.top().first);
//         }
//         return ans;
//     }
// };

class Solution {
public:
    vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
        deque<int> dq; 
        vector<int> ans;

        for (int i = 0; i < nums.size(); i++) {
            if (!dq.empty() && dq.front() == i - k) {
                dq.pop_front();
            }

            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }

            dq.push_back(i);

            if (i >= k - 1) {
                ans.push_back(nums[dq.front()]);
            }
        }

        return ans;
    }
};
