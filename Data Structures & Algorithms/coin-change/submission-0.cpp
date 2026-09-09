class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        const int INF = 1e9;
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, INF));
        for (int j = 0; j <= amount; j++) {
            if (j % coins[0] == 0)
                dp[0][j] = j / coins[0];
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= amount; j++) {
                int nottake = dp[i - 1][j];
                int take = INF;
                if (coins[i] <= j)
                    take = 1 + dp[i][j - coins[i]];

                dp[i][j] = min(take, nottake);
            }
        }
        if (dp[n - 1][amount] >= INF)
            return -1;

        return dp[n - 1][amount];
    }
};
