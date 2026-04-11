class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        unordered_map<int, vector<int>> mp;
        
        for(int i = 0; i < nums.size(); i++)
            mp[nums[i]].push_back(i);

        int ans = INT_MAX;

        for(auto &it : mp){
            auto &v = it.second;
            for(int i = 0; i + 2 < v.size(); i++){
                ans = min(ans, 2 * (v[i+2] - v[i]));
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};