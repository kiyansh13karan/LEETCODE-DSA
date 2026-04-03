#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Helper function to count how many open walls fall in the closed interval [L, R]
    int count_walls(long long L, long long R, const vector<long long>& w) {
        if (L > R) return 0;
        auto it1 = lower_bound(w.begin(), w.end(), L);
        auto it2 = upper_bound(w.begin(), w.end(), R);
        if (it1 >= it2) return 0;
        return distance(it1, it2);
    }

    // Helper function to count the total distinct open walls covered by the union of two intervals
    int count_union(long long A1, long long B1, long long A2, long long B2, const vector<long long>& w) {
        if (A1 > B1 && A2 > B2) return 0;
        if (A1 > B1) return count_walls(A2, B2, w);
        if (A2 > B2) return count_walls(A1, B1, w);

        // Sort intervals by their starting points to simplify overlap logic
        if (A1 > A2) {
            swap(A1, A2);
            swap(B1, B2);
        }

        if (B1 < A2) {
            // Disjoint intervals
            return count_walls(A1, B1, w) + count_walls(A2, B2, w);
        } else {
            // Overlapping or touching intervals
            return count_walls(A1, max(B1, B2), w);
        }
    }

    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        int n = robots.size();
        
        // Bundle and sort robots by their positions
        vector<pair<long long, long long>> rob(n);
        for (int i = 0; i < n; ++i) {
            rob[i] = {robots[i], distance[i]};
        }
        sort(rob.begin(), rob.end());

        // Sort walls so we can perform binary searches
        sort(walls.begin(), walls.end());

        vector<long long> open_walls;
        int fixed_walls = 0;
        
        // Extract walls that share a position with any robot (guaranteed to be destroyed)
        for (int w : walls) {
            pair<long long, long long> target = {w, -1LL};
            auto it = lower_bound(rob.begin(), rob.end(), target);
            if (it != rob.end() && it->first == w) {
                fixed_walls++; // Hits a robot directly
            } else {
                open_walls.push_back(w); // Strictly open-space wall
            }
        }

        // dp[i][0] -> Max walls destroyed up to segment i, if robot i shoots LEFT
        // dp[i][1] -> Max walls destroyed up to segment i, if robot i shoots RIGHT
        vector<vector<int>> dp(n, vector<int>(2, 0));

        // Base case: Robot 0
        long long r0 = rob[0].first;
        long long d0 = rob[0].second;
        dp[0][0] = count_walls(r0 - d0, r0 - 1, open_walls);
        dp[0][1] = 0;

        // DP Transitions for the remaining robots
        for (int i = 1; i < n; ++i) {
            long long r_prev = rob[i-1].first;
            long long d_prev = rob[i-1].second;
            long long r_curr = rob[i].first;
            long long d_curr = rob[i].second;

            // Scenario 1: Previous shoots Left (0), Current shoots Left (0)
            int c_00 = count_walls(max(r_prev + 1, r_curr - d_curr), r_curr - 1, open_walls);
            
            // Scenario 2: Previous shoots Left (0), Current shoots Right (1)
            int c_01 = 0; // Neither fires into the intermediate space
            
            // Scenario 3: Previous shoots Right (1), Current shoots Right (1)
            int c_11 = count_walls(r_prev + 1, min(r_curr - 1, r_prev + d_prev), open_walls);
            
            // Scenario 4: Previous shoots Right (1), Current shoots Left (0)
            int c_10 = count_union(r_prev + 1, min(r_curr - 1, r_prev + d_prev),
                                   max(r_prev + 1, r_curr - d_curr), r_curr - 1, open_walls);

            dp[i][0] = max(dp[i-1][0] + c_00, dp[i-1][1] + c_10);
            dp[i][1] = max(dp[i-1][0] + c_01, dp[i-1][1] + c_11);
        }

        // Finalize: Add the open space to the right of the very last robot
        long long rn = rob[n-1].first;
        long long dn = rob[n-1].second;
        
        int end_L = dp[n-1][0]; // Adds no coverage to the right
        int end_R = dp[n-1][1] + count_walls(rn + 1, rn + dn, open_walls); // Extends coverage to the right

        // Global Answer combines dynamically selected maximal open walls + inherently guaranteed robot walls
        return fixed_walls + max(end_L, end_R);
    }
};