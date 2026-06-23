class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        int k = r - l + 1;
        int MOD = 1e9 + 7;
        
        // prev_dp[v] stores the number of valid UP-first alternating sequences
        // of current length ending with mapped value v (from 1 to k).
        vector<int> prev_dp(k + 1, 1);
        prev_dp[0] = 0; // 0 is unused (1-based indexing for values)
        
        for (int i = 2; i <= n; ++i) {
            vector<int> curr_dp(k + 1, 0);
            int sum = 0;
            
            if (i % 2 == 0) {
                // Even index: sequence must go UP (A[i-1] < A[i])
                for (int v = 1; v <= k; ++v) {
                    curr_dp[v] = sum;
                    sum = (sum + prev_dp[v]) % MOD;
                }
            } else {
                // Odd index: sequence must go DOWN (A[i-1] > A[i])
                for (int v = k; v >= 1; --v) {
                    curr_dp[v] = sum;
                    sum = (sum + prev_dp[v]) % MOD;
                }
            }
            prev_dp = curr_dp;
        }
        
        long long total = 0;
        for (int v = 1; v <= k; ++v) {
            total = (total + prev_dp[v]) % MOD;
        }
        
        // Total valid arrays is 2 * (UP-first arrays) because DOWN-first
        // arrays will mirror the exact same count.
        return (total * 2) % MOD;
    }
};