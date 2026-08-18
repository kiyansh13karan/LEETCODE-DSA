class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();

        // Case 1: Only one subarray -> whole array
        if (k == n) {
            return *max_element(nums.begin(), nums.end());
        }

        // Frequency of every number
        vector<int> freq(51, 0);

        for (int x : nums) {
            freq[x]++;
        }

        // Case 2: Every element itself is a subarray
        if (k == 1) {
            int ans = -1;

            for (int x : nums) {
                if (freq[x] == 1) {
                    ans = max(ans, x);
                }
            }

            return ans;
        }

        // Case 3: 1 < k < n
        int ans = -1;

        if (freq[nums[0]] == 1) {
            ans = max(ans, nums[0]);
        }

        if (freq[nums[n - 1]] == 1) {
            ans = max(ans, nums[n - 1]);
        }

        return ans;
    }
};