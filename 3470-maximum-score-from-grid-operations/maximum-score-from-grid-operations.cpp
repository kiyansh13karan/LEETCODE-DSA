class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();

        // prefix[col][i] = sum of first i elements in column col
        vector<vector<long long>> prefix(n, vector<long long>(n + 1, 0));

        for (int col = 0; col < n; col++) {
            for (int row = 0; row < n; row++) {
                prefix[col][row + 1] = prefix[col][row] + grid[row][col];
            }
        }

        vector<long long> prevPick(n + 1, 0), prevSkip(n + 1, 0);

        for (int col = 1; col < n; col++) {
            vector<long long> currPick(n + 1, 0), currSkip(n + 1, 0);

            for (int curr = 0; curr <= n; curr++) {
                for (int prev = 0; prev <= n; prev++) {

                    if (curr > prev) {
                        // Current column deeper than previous
                        long long score =
                            prefix[col - 1][curr] - prefix[col - 1][prev];

                        currPick[curr] =
                            max(currPick[curr], prevSkip[prev] + score);

                        currSkip[curr] =
                            max(currSkip[curr], prevSkip[prev] + score);
                    } 
                    else {
                        // Previous deeper than current
                        long long score =
                            prefix[col][prev] - prefix[col][curr];

                        currPick[curr] =
                            max(currPick[curr], prevPick[prev] + score);

                        currSkip[curr] =
                            max(currSkip[curr], prevPick[prev]);
                    }
                }
            }

            prevPick = currPick;
            prevSkip = currSkip;
        }

        return *max_element(prevPick.begin(), prevPick.end());
    }
};