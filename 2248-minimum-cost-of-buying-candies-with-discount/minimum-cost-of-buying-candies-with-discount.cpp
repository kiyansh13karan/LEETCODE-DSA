class Solution {
public:
    int minimumCost(vector<int>& cost) {
        sort(cost.rbegin(), cost.rend());

        int ans = 0;
        for (int i = 0; i < cost.size(); i++) {
            if (i % 3 != 2) ans += cost[i];
        }

        return ans;
    }
};