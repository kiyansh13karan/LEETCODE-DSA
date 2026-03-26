#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        const int MAX_VAL = 100005;
        vector<int> min_row(MAX_VAL, 1e9);
        vector<int> max_row(MAX_VAL, -1e9);
        vector<int> min_col(MAX_VAL, 1e9);
        vector<int> max_col(MAX_VAL, -1e9);
        
        long long total_sum = 0;
        vector<long long> row_sum(m, 0);
        vector<long long> col_sum(n, 0);
        
        // Precompute bounds of every value & sums for efficient 1-pass lookups
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                int v = grid[i][j];
                if(v < MAX_VAL) {
                    min_row[v] = min(min_row[v], i);
                    max_row[v] = max(max_row[v], i);
                    min_col[v] = min(min_col[v], j);
                    max_col[v] = max(max_col[v], j);
                }
                row_sum[i] += v;
                col_sum[j] += v;
                total_sum += v;
            }
        }
        
        // Evaluate all possible Horizontal cuts
        long long current_sum = 0;
        for(int i = 0; i < m - 1; ++i) {
            current_sum += row_sum[i];
            long long top_sum = current_sum;
            long long bot_sum = total_sum - current_sum;
            
            if(top_sum == bot_sum) return true;
            
            if(top_sum > bot_sum) {
                long long diff = top_sum - bot_sum;
                if(diff < MAX_VAL) {
                    bool valid = false;
                    if(n >= 2) {
                        if(i == 0) { // Top is a 1D horizontal strip
                            if(grid[0][0] == diff || grid[0][n-1] == diff) valid = true;
                        } else {
                            if(min_row[diff] <= i) valid = true;
                        }
                    } else { // Top is a 1D vertical strip
                        if(grid[0][0] == diff || grid[i][0] == diff) valid = true;
                    }
                    if(valid) return true;
                }
            } else {
                long long diff = bot_sum - top_sum;
                if(diff < MAX_VAL) {
                    bool valid = false;
                    if(n >= 2) {
                        if(i == m - 2) { // Bottom is a 1D horizontal strip
                            if(grid[m-1][0] == diff || grid[m-1][n-1] == diff) valid = true;
                        } else {
                            if(max_row[diff] >= i + 1) valid = true;
                        }
                    } else { // Bottom is a 1D vertical strip
                        if(grid[i+1][0] == diff || grid[m-1][0] == diff) valid = true;
                    }
                    if(valid) return true;
                }
            }
        }
        
        // Evaluate all possible Vertical cuts
        current_sum = 0;
        for(int j = 0; j < n - 1; ++j) {
            current_sum += col_sum[j];
            long long left_sum = current_sum;
            long long right_sum = total_sum - current_sum;
            
            if(left_sum == right_sum) return true;
            
            if(left_sum > right_sum) {
                long long diff = left_sum - right_sum;
                if(diff < MAX_VAL) {
                    bool valid = false;
                    if(m >= 2) {
                        if(j == 0) { // Left is a 1D vertical strip
                            if(grid[0][0] == diff || grid[m-1][0] == diff) valid = true;
                        } else {
                            if(min_col[diff] <= j) valid = true;
                        }
                    } else { // Left is a 1D horizontal strip
                        if(grid[0][0] == diff || grid[0][j] == diff) valid = true;
                    }
                    if(valid) return true;
                }
            } else {
                long long diff = right_sum - left_sum;
                if(diff < MAX_VAL) {
                    bool valid = false;
                    if(m >= 2) {
                        if(j == n - 2) { // Right is a 1D vertical strip
                            if(grid[0][n-1] == diff || grid[m-1][n-1] == diff) valid = true;
                        } else {
                            if(max_col[diff] >= j + 1) valid = true;
                        }
                    } else { // Right is a 1D horizontal strip
                        if(grid[0][j+1] == diff || grid[0][n-1] == diff) valid = true;
                    }
                    if(valid) return true;
                }
            }
        }
        
        return false;
    }
};
