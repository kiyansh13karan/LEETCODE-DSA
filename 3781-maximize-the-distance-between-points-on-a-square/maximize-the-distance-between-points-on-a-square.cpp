class Solution {
public:
    struct Node {
        int sx, sy, ex, ey, len;
    };

    int maxDistance(int side, vector<vector<int>>& points, int k) {
        vector<pair<int,int>> arr = orderPoints(side, points);

        int low = 0, high = side;

        while (low < high) {
            int mid = (low + high + 1) / 2;
            if (canPick(arr, k, mid))
                low = mid;
            else
                high = mid - 1;
        }

        return low;
    }

private:
    bool canPick(vector<pair<int,int>>& arr, int k, int d) {
        deque<Node> dq;
        dq.push_back({arr[0].first, arr[0].second,
                      arr[0].first, arr[0].second, 1});

        int best = 1;

        for (int i = 1; i < arr.size(); i++) {
            int x = arr[i].first, y = arr[i].second;
            int sx = x, sy = y, len = 1;

            while (!dq.empty() &&
                   abs(x - dq.front().ex) + abs(y - dq.front().ey) >= d) {

                if (abs(x - dq.front().sx) + abs(y - dq.front().sy) >= d &&
                    dq.front().len + 1 >= len) {
                    sx = dq.front().sx;
                    sy = dq.front().sy;
                    len = dq.front().len + 1;
                    best = max(best, len);
                }

                dq.pop_front();
            }

            dq.push_back({sx, sy, x, y, len});
        }

        return best >= k;
    }

    vector<pair<int,int>> orderPoints(int side, vector<vector<int>>& points) {
        vector<pair<int,int>> left, top, right, bottom;

        for (auto &p : points) {
            int x = p[0], y = p[1];

            if (x == 0 && y > 0) left.push_back({x, y});
            else if (x > 0 && y == side) top.push_back({x, y});
            else if (x == side && y < side) right.push_back({x, y});
            else bottom.push_back({x, y});
        }

        sort(left.begin(), left.end());
        sort(top.begin(), top.end());
        sort(right.rbegin(), right.rend());
        sort(bottom.rbegin(), bottom.rend());

        vector<pair<int,int>> res;
        res.insert(res.end(), left.begin(), left.end());
        res.insert(res.end(), top.begin(), top.end());
        res.insert(res.end(), right.begin(), right.end());
        res.insert(res.end(), bottom.begin(), bottom.end());

        return res;
    }
};