class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        int layers = min(m, n) / 2;

        for (int layer = 0; layer < layers; layer++) {
            vector<int> v;

            int top = layer, left = layer;
            int bottom = m - layer - 1;
            int right = n - layer - 1;

            // top row
            for (int j = left; j <= right; j++)
                v.push_back(grid[top][j]);

            // right column
            for (int i = top + 1; i <= bottom - 1; i++)
                v.push_back(grid[i][right]);

            // bottom row
            for (int j = right; j >= left; j--)
                v.push_back(grid[bottom][j]);

            // left column
            for (int i = bottom - 1; i >= top + 1; i--)
                v.push_back(grid[i][left]);

            int sz = v.size();
            int rot = k % sz;

            vector<int> rotated(sz);

            for (int i = 0; i < sz; i++)
                rotated[i] = v[(i + rot) % sz];

            int idx = 0;

            // fill top row
            for (int j = left; j <= right; j++)
                grid[top][j] = rotated[idx++];

            // fill right column
            for (int i = top + 1; i <= bottom - 1; i++)
                grid[i][right] = rotated[idx++];

            // fill bottom row
            for (int j = right; j >= left; j--)
                grid[bottom][j] = rotated[idx++];

            // fill left column
            for (int i = bottom - 1; i >= top + 1; i--)
                grid[i][left] = rotated[idx++];
        }

        return grid;
    }
};