#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <array>

using namespace std;

class Solution {
    vector<vector<int>> stMax, stMin;
    vector<int> log2Arr;

    void buildSparseTable(const vector<int>& nums, int n) {
        log2Arr.assign(n + 1, 0);

        for (int i = 2; i <= n; i++) {
            log2Arr[i] = log2Arr[i / 2] + 1;
        }

        int K = log2Arr[n] + 1;

        stMax.assign(n, vector<int>(K));
        stMin.assign(n, vector<int>(K));

        for (int i = 0; i < n; i++) {
            stMax[i][0] = nums[i];
            stMin[i][0] = nums[i];
        }

        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                stMax[i][j] = max(
                    stMax[i][j - 1],
                    stMax[i + (1 << (j - 1))][j - 1]
                );

                stMin[i][j] = min(
                    stMin[i][j - 1],
                    stMin[i + (1 << (j - 1))][j - 1]
                );
            }
        }
    }

    int queryMax(int L, int R) {
        int j = log2Arr[R - L + 1];

        return max(
            stMax[L][j],
            stMax[R - (1 << j) + 1][j]
        );
    }

    int queryMin(int L, int R) {
        int j = log2Arr[R - L + 1];

        return min(
            stMin[L][j],
            stMin[R - (1 << j) + 1][j]
        );
    }

public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();

        buildSparseTable(nums, n);

        priority_queue<array<long long, 3>> pq;

        for (int L = 0; L < n; L++) {
            long long score =
                (long long)queryMax(L, n - 1) -
                (long long)queryMin(L, n - 1);

            pq.push({score, L, n - 1});
        }

        long long totalSum = 0;

        for (int i = 0; i < k; i++) {
            auto top = pq.top();
            pq.pop();

            totalSum += top[0];

            int L = top[1];
            int R = top[2];

            if (R > L) {
                int newR = R - 1;

                long long newScore =
                    (long long)queryMax(L, newR) -
                    (long long)queryMin(L, newR);

                pq.push({newScore, L, newR});
            }
        }

        return totalSum;
    }
};