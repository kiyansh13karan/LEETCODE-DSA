class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;
        
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0 && !visited[i][j]) {
                    long long total_value = 0;
                    queue<pair<int, int>> q;
                    
                    q.push({i, j});
                    visited[i][j] = true;
                    
                    while (!q.empty()) {
                        auto [r, c] = q.front();
                        q.pop();
                        
                        total_value += grid[r][c];
                        
                        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                        for (auto& dir : dirs) {
                            int nr = r + dir.first;
                            int nc = c + dir.second;
                            
                            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] > 0 && !visited[nr][nc]) {
                                visited[nr][nc] = true;
                                q.push({nr, nc});
                            }
                        }
                    }
                    
                    if (total_value % k == 0) {
                        count++;
                    }
                }
            }
        }
        
        return count;
    }
};