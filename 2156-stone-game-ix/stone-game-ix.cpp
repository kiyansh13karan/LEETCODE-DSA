class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        vector<int> cnt(3, 0);

        // Count numbers according to remainder when divided by 3
        for (int x : stones) {
            cnt[x % 3]++;
        }

        // If count of remainder-0 stones is even
        if (cnt[0] % 2 == 0) {
            return min(cnt[1], cnt[2]) > 0;
        }

        // If count of remainder-0 stones is odd
        return abs(cnt[1] - cnt[2]) > 2;
    }
};