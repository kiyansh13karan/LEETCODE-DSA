class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        // Directions: up, right, down, left
        vector<int> dx = {-1, 0, 1, 0};
        vector<int> dy = {0, 1, 0, -1};

        // Allowed directions for each street type
        vector<vector<int>> dir = {
            {},             // 0 unused
            {1, 3},         // type 1: left-right
            {0, 2},         // type 2: up-down
            {3, 2},         // type 3: left-down
            {1, 2},         // type 4: right-down
            {0, 3},         // type 5: left-up
            {0, 1}          // type 6: right-up
        };

        queue<pair<int,int>> q;
        vector<vector<bool>> vis(m, vector<bool>(n, false));

        q.push({0,0});
        vis[0][0] = true;

        while(!q.empty()) {
            auto [x,y] = q.front();
            q.pop();

            if(x == m-1 && y == n-1) return true;

            for(int d : dir[grid[x][y]]) {
                int nx = x + dx[d];
                int ny = y + dy[d];

                if(nx < 0 || ny < 0 || nx >= m || ny >= n || vis[nx][ny])
                    continue;

                int opp = (d + 2) % 4; // opposite direction

                for(int nd : dir[grid[nx][ny]]) {
                    if(nd == opp) {
                        vis[nx][ny] = true;
                        q.push({nx, ny});
                        break;
                    }
                }
            }
        }

        return false;
    }
};