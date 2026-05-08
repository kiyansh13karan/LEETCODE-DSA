class Solution {
public:
    int minJumps(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) return 0;

        int mx = *max_element(nums.begin(), nums.end());

        // Smallest Prime Factor Sieve
        vector<int> spf(mx + 1);

        for (int i = 2; i <= mx; i++) {
            if (spf[i] == 0) {
                for (int j = i; j <= mx; j += i) {
                    if (spf[j] == 0)
                        spf[j] = i;
                }
            }
        }

        // bucket[p] = all indices divisible by p
        unordered_map<int, vector<int>> bucket;

        for (int i = 0; i < n; i++) {
            int x = nums[i];

            unordered_set<int> used;

            while (x > 1) {
                int p = spf[x];

                if (!used.count(p)) {
                    bucket[p].push_back(i);
                    used.insert(p);
                }

                while (x % p == 0)
                    x /= p;
            }
        }

        vector<int> vis(n, 0);
        queue<pair<int,int>> q;

        q.push({0, 0});
        vis[0] = 1;

        while (!q.empty()) {
            auto [idx, dist] = q.front();
            q.pop();

            if (idx == n - 1)
                return dist;

            // left
            if (idx - 1 >= 0 && !vis[idx - 1]) {
                vis[idx - 1] = 1;
                q.push({idx - 1, dist + 1});
            }

            // right
            if (idx + 1 < n && !vis[idx + 1]) {
                vis[idx + 1] = 1;
                q.push({idx + 1, dist + 1});
            }

            // teleport if nums[idx] is prime
            int val = nums[idx];

            if (val > 1 && spf[val] == val) {

                for (int nextIdx : bucket[val]) {

                    if (!vis[nextIdx]) {
                        vis[nextIdx] = 1;
                        q.push({nextIdx, dist + 1});
                    }
                }

                // clear to avoid repeated traversal
                bucket[val].clear();
            }
        }

        return -1;
    }
};