class Solution { 
public: 
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) { 
        int n = gas.size(); 
        vector<int> diff(n); 
        int sum = 0; 

        for(int i = 0; i < n; i++) { 
            diff[i] = gas[i] - cost[i]; 
            sum += diff[i]; 
        } 
        if(sum < 0) 
        return -1; 

        int tank = 0;
        int ans = 0;

        for(int i = 0; i < n; i++) {
            tank += diff[i];
            if(tank < 0) {      
                ans = i + 1;    
                tank = 0;     
            }
        }

        return ans; 
    } 
};


// class Solution {
// public:
//     int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
//     {
//         int n=gas.size(),j;
//         for(int i=0;i<n;i++)
//         {
//             int cap=gas[i];
//             for(j=i;j<n+i-1;j++)
//             {
//                 cap-=cost[j%n];
//                 if(cap<=0)
//                 break;

//                 cap+=gas[(j+1)%n];
//             }
//             if(j==n+i-1)
//             return i;
//         }
//         return -1;
//     }
// };
