class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        int total = 0;
        for (int x : nums) total += x;

        vector<int> ans(nums.size());
        int left = 0;

        for (int i = 0; i < nums.size(); i++) {
            int right = total - left - nums[i];
            ans[i] = abs(left - right);
            left += nums[i];
        }

        return ans;
    }
};