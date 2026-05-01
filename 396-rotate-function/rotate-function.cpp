#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size();
        long long totalSum = 0;
        long long f = 0;
        
        // Calculate total sum and F(0)
        for (int i = 0; i < n; i++) {
            totalSum += nums[i];
            f += (long long)i * nums[i];
        }
        
        long long result = f;
        
        // Calculate F(k) using relation
        for (int k = 1; k < n; k++) {
            f = f + totalSum - (long long)n * nums[n - k];
            result = max(result, f);
        }
        
        return result;
    }
};