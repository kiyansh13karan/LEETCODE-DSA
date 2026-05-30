class FenwickTree {
public:
    vector<int> bit;

    FenwickTree(int n) {
        bit.resize(n + 1, 0);
    }

    void update(int idx, int val) {
        while (idx < bit.size()) {
            bit[idx] = max(bit[idx], val);
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int ans = 0;
        while (idx > 0) {
            ans = max(ans, bit[idx]);
            idx -= idx & -idx;
        }
        return ans;
    }
};

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        int mx = 50000;

        set<int> obstacles = {0, mx};
        FenwickTree bit(mx + 1);

        // Add all obstacles
        for (auto& q : queries) {
            if (q[0] == 1)
                obstacles.insert(q[1]);
        }

        // Initialize gaps
        for (auto it = obstacles.begin(); next(it) != obstacles.end(); ++it) {
            int a = *it;
            int b = *next(it);
            bit.update(b, b - a);
        }

        vector<bool> ans;

        // Process in reverse
        for (int i = (int)queries.size() - 1; i >= 0; i--) {
            auto& q = queries[i];

            if (q[0] == 1) {
                int x = q[1];

                auto it = obstacles.find(x);

                int prevPos = *std::prev(it);
                auto nxtIt = std::next(it);

                if (nxtIt != obstacles.end()) {
                    int nxtPos = *nxtIt;
                    bit.update(nxtPos, nxtPos - prevPos);
                }

                obstacles.erase(it);
            }
            else {
                int x = q[1];
                int sz = q[2];

                auto it = obstacles.upper_bound(x);
                int prevObs = *std::prev(it);

                bool canPlace =
                    (bit.query(prevObs) >= sz) ||
                    (x - prevObs >= sz);

                ans.push_back(canPlace);
            }
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};