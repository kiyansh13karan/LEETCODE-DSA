class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int, int>> a;
        for (int i = 0; i < n; i++)
            a.push_back({nums[i], i});

        sort(a.begin(), a.end());

        vector<int> pos(n);
        for (int i = 0; i < n; i++)
            pos[a[i].second] = i;

        const int LOG = 18;
        vector<vector<int>> up(LOG, vector<int>(n));

        int j = 0;
        for (int i = 0; i < n; i++) {
            while (j + 1 < n && a[j + 1].first - a[i].first <= maxDiff)
                j++;
            up[0][i] = j;
        }

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = pos[q[0]];
            int r = pos[q[1]];

            if (l > r) swap(l, r);

            if (l == r) {
                ans.push_back(0);
                continue;
            }

            int cur = l;
            int dist = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < r) {
                    cur = up[k][cur];
                    dist += (1 << k);
                }
            }

            if (up[0][cur] < r)
                ans.push_back(-1);
            else
                ans.push_back(dist + 1);
        }

        return ans;
    }
};