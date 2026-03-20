class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> ans(m - k + 1, vector<int>(n - k + 1));

        for (int i = 0; i <= m - k; i++) {
            for (int j = 0; j <= n - k; j++) {

                vector<int> v;

                for (int x = i; x < i + k; x++) {
                    for (int y = j; y < j + k; y++) {
                        v.push_back(grid[x][y]);
                    }
                }

                sort(v.begin(), v.end());

                // remove duplicates
                v.erase(unique(v.begin(), v.end()), v.end());

                int mn = INT_MAX;

                for (int p = 1; p < v.size(); p++) {
                    mn = min(mn, v[p] - v[p - 1]);
                }

                ans[i][j] = (mn == INT_MAX ? 0 : mn);
            }
        }

        return ans;
    }
};