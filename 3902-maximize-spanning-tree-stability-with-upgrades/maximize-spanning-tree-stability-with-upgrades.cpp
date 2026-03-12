class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // Path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank[rx] < rank[ry]) swap(rx, ry);
        parent[ry] = rx;
        if (rank[rx] == rank[ry]) rank[rx]++;
        return true;
    }
};


    
class Solution {
public:
bool canBuild(int n, vector<vector<int>>& edges, int k, int stability) {
        DSU dsu(n);
        int upgradesUsed = 0;
        vector<tuple<int, int, int, bool>> optionalEdges; // {strength, u, v, usedUpgrade}

        // First, add all must==1 edges. If any of them has strength < stability, return false
        for (auto& e : edges) {
            int u = e[0], v = e[1], s = e[2], must = e[3];
            if (must == 1) {
                if (s < stability) return false; // cannot use, but required
                dsu.unite(u, v);
            }
            else{
                if (s >= stability) {
                    dsu.unite(u, v);
                } else if (2 * s >= stability) {
                    optionalEdges.emplace_back(2 * s, u, v, true); // upgrade needed
                }
            }
        }


        for (auto& [s, u, v, upgraded] : optionalEdges) {
            if (dsu.find(u) != dsu.find(v)) {
                if (upgradesUsed >= k) return false; // can't upgrade more
                    dsu.unite(u, v);
                    upgradesUsed++;
            }
        }

        int root = dsu.find(0);
        for(int i=1;i<n;i++){
            if(dsu.find(i)!=root) return false;
        }
        return true;

    }
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        int low = 1, high = 0;
         DSU dsu(n);

        for (auto& e : edges) {
            int s = e[2];
            int u = e[0];
            int v = e[1];
            if (e[3] == 1) {
                if(!dsu.unite(u, v)) return -1;
                high = max(high, s);
            }
            else high = max(high, s * 2);
        }

        int ans = -1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (canBuild(n, edges, k, mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};