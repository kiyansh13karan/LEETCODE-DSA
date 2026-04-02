class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int n = coins.size(), m = coins[0].size();
        
        vector dp(n, vector(m, vector<int>(3, INT_MIN)));
        
        dp[0][0][0] = coins[0][0];
        if (coins[0][0] < 0) dp[0][0][1] = 0;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                for(int k=0;k<3;k++){
                    if(dp[i][j][k] == INT_MIN) continue;
                    
                    // Move Right
                    if(j+1<m){
                        int val = coins[i][j+1];
                        dp[i][j+1][k] = max(dp[i][j+1][k], dp[i][j][k] + val);
                        if(val < 0 && k < 2)
                            dp[i][j+1][k+1] = max(dp[i][j+1][k+1], dp[i][j][k]);
                    }

                    // Move Down
                    if(i+1<n){
                        int val = coins[i+1][j];
                        dp[i+1][j][k] = max(dp[i+1][j][k], dp[i][j][k] + val);
                        if(val < 0 && k < 2)
                            dp[i+1][j][k+1] = max(dp[i+1][j][k+1], dp[i][j][k]);
                    }
                }
            }
        }

        return max({dp[n-1][m-1][0], dp[n-1][m-1][1], dp[n-1][m-1][2]});
    }
};