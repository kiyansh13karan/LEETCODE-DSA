class Solution {
public:
    int n;
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(int i, int M) {
        if (i >= n)
            return 0;

        if (dp[i][M] != -1)
            return dp[i][M];

        // Agar remaining stones M ke according saare le sakte hain
        if (i + 2 * M >= n)
            return dp[i][M] = suffix[i];

        int ans = 0;

        // Current player X stones lega
        for (int x = 1; x <= 2 * M; x++) {
            // Opponent ke maximum score ko subtract karenge
            ans = max(ans, suffix[i] - solve(i + x, max(M, x)));
        }

        return dp[i][M] = ans;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        // suffix[i] = piles[i] se end tak total stones
        suffix.resize(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        dp.assign(n, vector<int>(n + 1, -1));

        return solve(0, 1);
    }
};