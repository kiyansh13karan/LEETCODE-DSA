#include <vector>
#include <numeric>

class Solution {
public:
    long long findKthSmallest(std::vector<int>& coins, int k) {
        int n = coins.size();
        std::vector<long long> lcms;
        std::vector<int> signs;
        
        for (int i = 1; i < (1 << n); ++i) {
            long long current_lcm = 1;
            int bits = 0;
            for (int j = 0; j < n; ++j) {
                if ((i >> j) & 1) {
                    current_lcm = std::lcm(current_lcm, (long long)coins[j]);
                    bits++;
                }
            }
            lcms.push_back(current_lcm);
            signs.push_back(bits % 2 == 1 ? 1 : -1);
        }
        
        long long left = 1;
        long long min_coin = coins[0];
        for (int c : coins) {
            if (c < min_coin) min_coin = c;
        }
        long long right = min_coin * k;
        long long ans = right;
        
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            long long count = 0;
            
            for (size_t i = 0; i < lcms.size(); ++i) {
                count += signs[i] * (mid / lcms[i]);
            }
            
            if (count >= k) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return ans;
    }
};