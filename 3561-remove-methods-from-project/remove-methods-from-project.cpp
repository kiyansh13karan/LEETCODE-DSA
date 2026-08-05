class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> g(n), ug(n);

        for (auto &e : invocations) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            ug[u].push_back(v);
            ug[v].push_back(u);
        }

        vector<bool> suspicious(n, false);

        function<void(int)> dfs1 = [&](int u) {
            suspicious[u] = true;
            for (int v : g[u]) {
                if (!suspicious[v])
                    dfs1(v);
            }
        };

        dfs1(k);

        vector<bool> vis(n, false);

        function<void(int)> dfs2 = [&](int u) {
            vis[u] = true;
            for (int v : ug[u]) {
                if (!vis[v]) {
                    suspicious[v] = false;
                    dfs2(v);
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (!suspicious[i] && !vis[i])
                dfs2(i);
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i])
                ans.push_back(i);
        }

        return ans;
    }
};