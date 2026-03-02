class Solution {
public:
    vector<vector<int>> res;

    void solve(int start, int n, int k, vector<int>& temp){
        if(temp.size() == k){
            res.push_back(temp);
            return;
        }

        for(int i = start; i <= n; i++){
            temp.push_back(i);
            solve(i + 1, n, k, temp);
            temp.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        vector<int> temp;
        solve(1, n, k, temp);
        return res;
    }
};