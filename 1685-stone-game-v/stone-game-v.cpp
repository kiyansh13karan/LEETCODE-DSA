#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        
        // Prefix sum array to get subarray sums in O(1)
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }
        
        // Memoization table initialized to -1
        vector<vector<int>> memo(n, vector<int>(n, -1));
        
        return solve(stoneValue, prefix, memo, 0, n - 1);
    }
    
private:
    int solve(const vector<int>& stoneValue, const vector<int>& prefix, vector<vector<int>>& memo, int left, int right) {
        // Base case: Only one stone left, score is 0
        if (left == right) {
            return 0;
        }
        
        // Return precalculated result if it exists
        if (memo[left][right] != -1) {
            return memo[left][right];
        }
        
        int max_score = 0;
        
        // Try partitioning the array at every possible split point `i`
        for (int i = left; i < right; ++i) {
            int left_sum = prefix[i + 1] - prefix[left];
            int right_sum = prefix[right + 1] - prefix[i + 1];
            
            if (left_sum < right_sum) {
                // Bob throws away the right row. Alice keeps the left row.
                max_score = max(max_score, left_sum + solve(stoneValue, prefix, memo, left, i));
            } else if (left_sum > right_sum) {
                // Bob throws away the left row. Alice keeps the right row.
                max_score = max(max_score, right_sum + solve(stoneValue, prefix, memo, i + 1, right));
            } else {
                // Sums are equal, Alice can choose either row. Maximize her choice.
                max_score = max({max_score, 
                                 left_sum + solve(stoneValue, prefix, memo, left, i), 
                                 right_sum + solve(stoneValue, prefix, memo, i + 1, right)});
            }
        }
        
        // Save to memo and return
        return memo[left][right] = max_score;
    }
};