class Solution {
public:
    vector<vector<int>> ans;
    vector<int> path;

    void solve(int idx, int target, vector<int>& candidates) {
        if (target == 0) {
            ans.push_back(path);
            return;
        }

        if (idx == candidates.size() || target < 0)
            return;

        // Take current element
        path.push_back(candidates[idx]);
        solve(idx, target - candidates[idx], candidates);
        path.pop_back();

        // Skip current element
        solve(idx + 1, target, candidates);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        solve(0, target, candidates);
        return ans;
    }
};