class Fenwick {
public:
    vector<int> bit;
    int n;

    Fenwick(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    void update(int idx, int val) {
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
};

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        bool found = false;
        int n = nums.size();

        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; i++) {
            if (nums[i] == target) {
                pref[i + 1] = pref[i] + 1;
                found = true;
            } else {
                pref[i + 1] = pref[i] - 1;
            }
        }

        if (!found) return 0;

        vector<int> vals = pref;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        Fenwick bit(vals.size());

        long long ans = 0;

        for (int x : pref) {
            int idx = lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
            ans += bit.query(idx - 1);
            bit.update(idx, 1);
        }

        return ans;
    }
};