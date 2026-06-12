class Solution {
    static const int MOD = 1e9 + 7;
    static const int LOG = 17;

    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> g;
    vector<long long> pow2;

    void dfs(int u, int p) {
        up[u][0] = p;

        for (int j = 1; j < LOG; j++) {
            if (up[u][j - 1] == -1)
                up[u][j] = -1;
            else
                up[u][j] = up[up[u][j - 1]][j - 1];
        }

        for (int v : g[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);

        int diff = depth[a] - depth[b];

        for (int j = LOG - 1; j >= 0; j--) {
            if (diff & (1 << j))
                a = up[a][j];
        }

        if (a == b) return a;

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }

        return up[a][0];
    }

public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges,
                                  vector<vector<int>>& queries) {

        int n = edges.size() + 1;

        g.assign(n + 1, {});
        depth.assign(n + 1, 0);
        up.assign(n + 1, vector<int>(LOG, -1));

        for (auto &e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        dfs(1, -1);

        pow2.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
        }

        vector<int> ans;

        for (auto &q : queries) {
            int u = q[0], v = q[1];

            if (u == v) {
                ans.push_back(0);
                continue;
            }

            int L = lca(u, v);
            int dist = depth[u] + depth[v] - 2 * depth[L];

            ans.push_back(pow2[dist - 1]);
        }

        return ans;
    }
};