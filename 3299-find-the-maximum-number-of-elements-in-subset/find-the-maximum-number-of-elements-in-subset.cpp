class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> cnt;

        int mx = 0;
        for (int x : nums) {
            cnt[x]++;
            mx = max(mx, x);
        }

        int ans = cnt.count(1) ? cnt[1] - (cnt[1] % 2 == 0) : 1;

        for (int num : nums) {
            if (num == 1) continue;

            long long x = num;
            int len = 0;

            while (x <= mx && cnt.count(x) && cnt[x] >= 2) {
                len += 2;
                x = x * x;
            }

            if (cnt.count(x))
                len += 1;
            else
                len -= 1;

            ans = max(ans, len);
        }

        return ans;
    }
};