class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int total = 0;
        int maxSum = nums[0], curMax = 0;
        int minSum = nums[0], curMin = 0;

        for(int n : nums){
            total += n;

            curMax = max(n, curMax + n);
            maxSum = max(maxSum, curMax);

            curMin = min(n, curMin + n);
            minSum = min(minSum, curMin);
        }

        if(maxSum < 0) return maxSum;

        return max(maxSum, total - minSum);
    }
};