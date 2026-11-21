class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        vector<int> last(26, -1);
        vector<int> order;

        struct Event {
            int node;
            bool exit;
            int prev;
        };

        vector<Event> st;
        st.push_back({0, false, -1});

        // Find the closest ancestor having the same character
        while (!st.empty()) {
            Event e = st.back();
            st.pop_back();

            int u = e.node;
            int c = s[u] - 'a';

            if (e.exit) {
                last[c] = e.prev;
                continue;
            }

            int old = last[c];

            if (old != -1) {
                newParent[u] = old;
            }

            last[c] = u;
            order.push_back(u);

            st.push_back({u, true, old});

            for (int v : adj[u]) {
                st.push_back({v, false, -1});
            }
        }

        // Calculate subtree sizes
        vector<int> ans(n, 1);

        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];

            if (newParent[u] != -1) {
                ans[newParent[u]] += ans[u];
            }
        }

        return ans;
    }
};