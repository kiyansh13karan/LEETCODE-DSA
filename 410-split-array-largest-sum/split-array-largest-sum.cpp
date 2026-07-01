class Solution {
public:
    bool canSplit(vector<int>& nums, int k, int maxSum) {
        int groups = 1;
        int currentSum = 0;

        for (int num : nums) {
            if (currentSum + num <= maxSum) {
                currentSum += num;
            } else {
                groups++;
                currentSum = num;
            }
        }

        return groups <= k;
    }

    int splitArray(vector<int>& nums, int k) {

        int start = *max_element(nums.begin(), nums.end());

        int end = accumulate(nums.begin(), nums.end(), 0);

        while (start < end) {

            int mid = start + (end - start) / 2;

            if (canSplit(nums, k, mid))
                end = mid;
            else
                start = mid + 1;
        }

        return start;
    }
};