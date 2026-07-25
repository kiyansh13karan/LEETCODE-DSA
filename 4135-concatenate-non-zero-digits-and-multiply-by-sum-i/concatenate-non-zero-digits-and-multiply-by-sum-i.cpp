class Solution {
public:
    long long sumAndMultiply(int n) {
        int place = 1;
        long long x = 0;
        int sum = 0;

        while (n > 0) {
            int digit = n % 10;

            if (digit != 0) {
                x += 1LL * digit * place;
                sum += digit;
                place *= 10;
            }

            n /= 10;
        }

        return x * sum;
    }
};