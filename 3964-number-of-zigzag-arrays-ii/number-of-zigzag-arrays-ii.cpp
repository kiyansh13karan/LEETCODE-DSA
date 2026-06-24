#pragma GCC optimize("O3")
#include <vector>

using namespace std;

class Solution {
    using ll = long long;
    const int MOD = 1e9 + 7;
    using Matrix = vector<vector<ll>>;

    // Helper function to multiply two matrices
    Matrix multiply(const Matrix& A, const Matrix& B) {
        int n = A.size();
        int m = B[0].size();
        int p = A[0].size();
        Matrix C(n, vector<ll>(m, 0));
        
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < p; k++) {
                if (!A[i][k]) continue; // Skip zero multipliers for optimization
                for (int j = 0; j < m; j++) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    // Helper function for binary matrix exponentiation
    Matrix power(Matrix A, ll p) {
        int n = A.size();
        Matrix res(n, vector<ll>(n, 0));
        
        // Initialize as Identity Matrix
        for (int i = 0; i < n; i++) {
            res[i][i] = 1;
        }
        
        while (p > 0) {
            if (p & 1) res = multiply(res, A);
            A = multiply(A, A);
            p >>= 1;
        }
        return res;
    }

public:
    int zigZagArrays(int n, int l, int r) {
        int K = r - l + 1;

        // Create the optimized Transition Matrix T of size K x K
        Matrix T(K, vector<ll>(K, 0));
        for (int i = 0; i < K; ++i) {
            for (int j = 0; j < K; ++j) {
                // Symmetrical valid transitions
                if (i + j >= K) {
                    T[i][j] = 1;
                }
            }
        }

        // Raise the transition matrix to the power of n - 2
        Matrix Tn_minus_2 = power(T, n - 2);

        // Define the initial state vector V (for sequences of length 2)
        // V[0][u] represents the number of valid pairs ending in value (u + 1) going UP
        Matrix V(1, vector<ll>(K, 0));
        for (int u = 1; u <= K; ++u) {
            V[0][u - 1] = u - 1; 
        }

        // Multiply initial states with the exponentiated transitions
        Matrix V_final = multiply(V, Tn_minus_2);

        // Sum up all valid sequences that end on an "UP" sequence
        ll total_up = 0;
        for (int j = 0; j < K; ++j) {
            total_up = (total_up + V_final[0][j]) % MOD;
        }

        // The total is strictly double the UP sequences because of DOWN sequence symmetry
        ll ans = (total_up * 2) % MOD;
        return ans;
    }
};
