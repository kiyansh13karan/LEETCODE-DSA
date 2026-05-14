class Solution {
public:
    bool isGood(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int n = nums.size();

        // Minimum size should be 2
        if (n < 2)
            return false;

        // Last two elements must be same
        if (nums[n - 1] != nums[n - 2])
            return false;

        // Check sequence 1,2,3...
        for (int i = 0; i < n - 1; i++) {
            if (nums[i] != i + 1)
                return false;
        }

        return true;
    }
};