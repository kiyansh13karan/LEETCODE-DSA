class Solution {
public:
    int concatenatedBinary(int n) {
        long ans = 0;
        int bits = 0;
        int mod = 1e9 + 7;

        for(int i = 1; i <= n; i++) {
            if((i & (i - 1)) == 0) bits++;
            ans = ((ans << bits) | i) % mod;
        }

        return ans;
    }
};