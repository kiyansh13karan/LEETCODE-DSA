class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        vector<int> sa(n), rnk(n), temp(n), pos(n), lcp(n);

        iota(sa.begin(), sa.end(), 0);

        vector<int> vals = nums;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        for (int i = 0; i < n; i++)
            rnk[i] = lower_bound(vals.begin(), vals.end(), nums[i]) - vals.begin();

        // Build Suffix Array
        for (int k = 1; k < n; k *= 2) {
            sort(sa.begin(), sa.end(), [&](int a, int b) {
                if (rnk[a] != rnk[b])
                    return rnk[a] < rnk[b];

                int x = (a + k < n) ? rnk[a + k] : -1;
                int y = (b + k < n) ? rnk[b + k] : -1;

                return x < y;
            });

            temp[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                int a = sa[i - 1];
                int b = sa[i];

                bool diff = rnk[a] != rnk[b] ||
                    (a + k < n ? rnk[a + k] : -1) !=
                    (b + k < n ? rnk[b + k] : -1);

                temp[b] = temp[a] + diff;
            }

            rnk.swap(temp);

            if (rnk[sa[n - 1]] == n - 1)
                break;
        }

        // Calculate LCP
        for (int i = 0; i < n; i++)
            pos[sa[i]] = i;

        int h = 0;

        for (int i = 0; i < n; i++) {
            int r = pos[i];

            if (r == 0) {
                h = 0;
                continue;
            }

            int j = sa[r - 1];

            while (i + h < n && j + h < n &&
                   nums[i + h] == nums[j + h])
                h++;

            lcp[r] = h;

            if (h > 0)
                h--;
        }

        // Find minimum unique subarray length
        int ans = n;

        for (int r = 0; r < n; r++) {
            int mx = lcp[r];

            if (r + 1 < n)
                mx = max(mx, lcp[r + 1]);

            int len = mx + 1;

            if (sa[r] + len <= n)
                ans = min(ans, len);
        }

        return ans;
    }
};