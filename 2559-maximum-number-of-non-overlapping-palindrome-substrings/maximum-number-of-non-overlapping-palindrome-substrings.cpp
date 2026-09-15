class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();

        // pal[i][j] = true if s[i...j] is palindrome
        vector<vector<bool>> pal(n, vector<bool>(n, false));

        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;

                if (len == 1) {
                    pal[i][j] = true;
                }
                else if (len == 2) {
                    pal[i][j] = (s[i] == s[j]);
                }
                else {
                    pal[i][j] = (s[i] == s[j] && pal[i + 1][j - 1]);
                }
            }
        }

        // dp[i] = maximum palindromes in first i characters
        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            // Don't take a palindrome ending at i-1
            dp[i] = dp[i - 1];

            // Try every palindrome of length >= k ending at i-1
            for (int start = 0; start <= i - k; start++) {
                if (pal[start][i - 1]) {
                    dp[i] = max(dp[i], dp[start] + 1);
                }
            }
        }

        return dp[n];
    }
};