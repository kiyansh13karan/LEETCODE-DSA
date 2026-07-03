class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        const int MOD = 1e9 + 7;

        long long gcd = __gcd((long long)a, (long long)b);
        long long lcm = 1LL * a / gcd * b;

        long long left = min(a, b);
        long long right = 1LL * n * min(a, b);

        while (left < right) {
            long long mid = left + (right - left) / 2;

            long long count = mid / a + mid / b - mid / lcm;

            if (count >= n)
                right = mid;
            else
                left = mid + 1;
        }

        return left % MOD;
    }
};