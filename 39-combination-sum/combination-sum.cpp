class Solution {
public:
    void solve(vector<int>& candidates, int target, int index,
               vector<int>& temp, vector<vector<int>>& ans) {
        
        if(target == 0){
            ans.push_back(temp);
            return;
        }

        if(target < 0) return;

        for(int i = index; i < candidates.size(); i++){
            temp.push_back(candidates[i]);
            solve(candidates, target - candidates[i], i, temp, ans);
            temp.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> temp;
        solve(candidates, target, 0, temp, ans);
        return ans;
    }
};