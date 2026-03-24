class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        
        const int MOD = 12345;
        
        int m = grid.size();
        int n = grid[0].size();
        
        vector<long long> arr;
        
        // flatten matrix
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                arr.push_back(grid[i][j] % MOD);
            }
        }
        
        int size = arr.size();
        
        vector<long long> prefix(size, 1), suffix(size, 1);
        
        // prefix
        for(int i = 1; i < size; i++) {
            prefix[i] = (prefix[i-1] * arr[i-1]) % MOD;
        }
        
        // suffix
        for(int i = size-2; i >= 0; i--) {
            suffix[i] = (suffix[i+1] * arr[i+1]) % MOD;
        }
        
        vector<vector<int>> result(m, vector<int>(n));
        
        for(int i = 0; i < size; i++) {
            long long val = (prefix[i] * suffix[i]) % MOD;
            result[i/n][i%n] = val;
        }
        
        return result;
    }
};