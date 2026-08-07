#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Helper to get the minimum digits (sorted ascending) whose product is 'rem'
    vector<int> getMinDigits(long long rem) {
        vector<int> digits;
        for (int d = 9; d >= 2; --d) {
            while (rem % d == 0) {
                digits.push_back(d);
                rem /= d;
            }
        }
        sort(digits.begin(), digits.end());
        return digits;
    }

    // Helper to divide 't' by gcd(t, d)
    long long getRem(long long t, long long d) {
        return t / std::gcd(t, d);
    }

public:
    string smallestNumber(string num, long long t) {
        // Step 1: Check if 't' has prime factors other than 2, 3, 5, 7
        long long temp = t;
        for (int p : {2, 3, 5, 7}) {
            while (temp % p == 0) temp /= p;
        }
        if (temp > 1) return "-1";

        int n = num.size();
        vector<long long> pref_t(n + 1);
        pref_t[0] = t;
        int first_zero = n;

        // Step 2: Precompute remaining 't' for prefixes and locate first '0'
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0' && first_zero == n) {
                first_zero = i;
            }
            pref_t[i + 1] = getRem(pref_t[i], num[i] - '0');
        }

        // If num itself is zero-free and valid, return it
        if (first_zero == n && pref_t[n] == 1) {
            return num;
        }

        // Step 3: Search from right to left for the same length solution
        for (int i = min(n - 1, first_zero); i >= 0; --i) {
            for (int d = (num[i] - '0') + 1; d <= 9; ++d) {
                long long rem = getRem(pref_t[i], d);
                vector<int> req = getMinDigits(rem);
                int rem_len = n - 1 - i;

                // Check if remaining positions can cover the required digits
                if ((int)req.size() <= rem_len) {
                    string ans = num.substr(0, i);
                    ans += (char)('0' + d);
                    ans += string(rem_len - req.size(), '1'); // Pad with '1's
                    for (int x : req) {
                        ans += (char)('0' + x);
                    }
                    return ans;
                }
            }
        }

        // Step 4: If no solution of length N exists, build the smallest of length > N
        vector<int> req = getMinDigits(t);
        int L = max(n + 1, (int)req.size());
        string ans = string(L - req.size(), '1');
        for (int x : req) {
            ans += (char)('0' + x);
        }
        return ans;
    }
};